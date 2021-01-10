/*
-------------------------------------------------------------------------------
    Copyright (c) Charles Carley.

  This software is provided 'as-is', without any express or implied
  warranty. In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
-------------------------------------------------------------------------------
*/
#include "Window/X11/skWindowContextX11.h"
#include <X11/keysym.h>
#include <unistd.h>
#include "Utils/skLogger.h"
#include "Window/X11/skWindowX11.h"
#include "Window/skMouse.h"
#include "Window/skWindowManager.h"
#include "skKeyboard.h"

skWindowContextX11::skWindowContextX11(skWindowManager* owner) :
    skWindowContext(owner),
    m_creator(owner),
    m_deleteAtom(0)
{
}

skWindowContextX11::~skWindowContextX11()
{
    if (m_display != nullptr)
        XCloseDisplay(m_display);
}

void skWindowContextX11::initialize(void)
{
    m_display = XOpenDisplay(nullptr);
    if (m_display == nullptr)
    {
        skLogd(LD_ERROR, "Failed to open the X display\n");
        return;
    }

    m_deleteAtom = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
    if (m_deleteAtom == None)
        skLogd(LD_ERROR, "Failed to create the WM_DELETE_WINDOW Atom\n");
}

skWindow* skWindowContextX11::extractWindowFromEvent(XEvent& evt) const
{
    switch (evt.type)
    {
    case Expose:
        return find((SKsize)evt.xexpose.window);
    case ConfigureNotify:
        return find((SKsize)evt.xconfigure.window);
    case DestroyNotify:
        return find((SKsize)evt.xdestroywindow.window);
    case MotionNotify:
        return find((SKsize)evt.xmotion.window);
    case ClientMessage:
        return find((SKsize)evt.xclient.window);
    case ButtonPress:
    case ButtonRelease:
        return find((SKsize)evt.xbutton.window);
    case KeyPress:
    case KeyRelease:
        return find((SKsize)evt.xkey.window);
    default:
        return nullptr;
    }
}

void skWindowContextX11::processInteractive(bool dispatch)
{
    if (!m_display)
        return;

    m_shouldDispatch = true;
    XEvent evt       = {};
    do
    {
        XNextEvent(m_display, &evt);

        skWindow* win = extractWindowFromEvent(evt);
        if (win != nullptr)
            processMessage(win, evt);

    } while (XPending(m_display));
}

void skWindowContextX11::process()
{
    bool waitForMessage = true;
    m_shouldDispatch    = true;
    XEvent evt          = {};

    do
    {
        while (XPending(m_display))
        {
            XNextEvent(m_display, &evt);

            skWindow* win = extractWindowFromEvent(evt);
            if (win != nullptr)
            {
                waitForMessage = false;
                processMessage(win, evt);
            }
        }
        if (waitForMessage)
            usleep(1);
    } while (waitForMessage);

    m_shouldDispatch = false;
}

void skWindowContextX11::handleConfigure(XEvent& evt, skWindowX11* win) const
{
    SK_ASSERT(win);

    if (win->getWidth() != evt.xconfigure.width &&
        win->getHeight() != evt.xconfigure.height)
    {
        win->notifySize(evt.xconfigure.width, evt.xconfigure.height);

        if (shouldDispatch())
            m_creator->dispatchEvent(skEventType::SK_WIN_SIZE, win);
    }
}

void skWindowContextX11::handleExpose(XEvent& evt, skWindowX11* win) const
{
    SK_ASSERT(win);

    // Count determines the number of expose events in the queue.
    // Here, only the last one is needed. For now this just needs to know
    // that something needs redrawn.
    if (evt.xexpose.count == 0)
    {
        if (shouldDispatch())
            m_creator->dispatchEvent(skEventType::SK_WIN_PAINT, win);

        win->flush();
    }
}

void skWindowContextX11::handleDestroy(XEvent&, skWindowX11* win) const
{
    SK_ASSERT(win);

    if (shouldDispatch())
        m_creator->dispatchEvent(skEventType::SK_WIN_DESTROY, win);

    m_creator->destroy(win);
}

void skWindowContextX11::handleMotion(XEvent& evt, skWindowX11* win) const
{
    SK_ASSERT(win);

    win->notifyMotion(evt.xmotion.x, evt.xmotion.y);

    if (shouldDispatch())
        m_creator->dispatchEvent(skEventType::SK_MOUSE_MOVED, win);
}

void skWindowContextX11::handleButton(XEvent& evt, skWindowX11* win) const
{
    SK_ASSERT(win);
    const XButtonEvent& bEvent = evt.xbutton;

    skMouse& mouse = win->getMouseRef();

    if (bEvent.button >= 1 && bEvent.button <= 3)
    {
        SKmouseTable& table = mouse.getTable();

        if (bEvent.button == 1)  // left
            table[MBT_L] = evt.type == ButtonPress ? WM_PRESSED : WM_RELEASED;
        if (bEvent.button == 2)  // middle
            table[MBT_M] = evt.type == ButtonPress ? WM_PRESSED : WM_RELEASED;
        if (bEvent.button == 3)  // right
            table[MBT_R] = evt.type == ButtonPress ? WM_PRESSED : WM_RELEASED;

        if (shouldDispatch())
        {
            m_creator->dispatchEvent(
                evt.type == ButtonPress ? skEventType::SK_MOUSE_PRESSED : skEventType::SK_MOUSE_RELEASED,
                win);
        }
    }
    else
    {
        if (bEvent.type == ButtonPress)
        {
            if (bEvent.button == 4)
            {
                mouse.z.abs = skWheelDelta;
                mouse.z.rel = 1;
            }
            else if (bEvent.button == 5)
            {
                mouse.z.abs = -skWheelDelta;
                mouse.z.rel = -1;
            }

            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_MOUSE_WHEEL, win);
        }
        else
        {
            mouse.z.abs = 0;
            mouse.z.rel = 0;
        }
    }
}

void skWindowContextX11::handleMetaModifier(SKkeyTable& table, SKint32 scanCode, SKuint8 state)
{
    switch (scanCode)
    {
    case KC_LCTRL:
    case KC_RCTRL:
        table[KC_CTRL] = state;
        break;
    case KC_LSHIFT:
    case KC_RSHIFT:
        table[KC_SHIFT] = state;
        break;
    case KC_LALT:
    case KC_RALT:
        table[KC_ALT] = state;
        break;
    default:
        break;
    }
}

void skWindowContextX11::handleKey(XEvent& evt, skWindowX11* win) const
{
    SK_ASSERT(win);
    XKeyEvent& kEvent = evt.xkey;

    const SKint32 keyCode  = XLookupKeysym(&kEvent, 0);
    const SKint32 scanCode = getScanCode(keyCode);
    if (scanCode > KC_NONE && scanCode < KC_MAX)
    {
        SKkeyTable& table = win->getKeyboardRef().getTable();

        const SKuint8 keyState = kEvent.type == KeyPress ? WM_PRESSED : WM_RELEASED;
        if (shouldDispatch())
        {
            // always pressed for the dispatch
            table[scanCode] = WM_PRESSED;
            if (scanCode >= KC_LCTRL && scanCode <= KC_RSHIFT)
                handleMetaModifier(table, scanCode, WM_PRESSED);

            if (keyState != 0)
                m_creator->dispatchEvent(skEventType::SK_KEY_PRESSED, win);
            else
                m_creator->dispatchEvent(skEventType::SK_KEY_RELEASED, win);
        }
        table[scanCode] = keyState;

        if (scanCode >= KC_LCTRL && scanCode <= KC_RSHIFT)
            handleMetaModifier(table, scanCode, keyState);
    }
}

void skWindowContextX11::handleClient(XEvent& evt, skWindowX11* win) const
{
    XClientMessageEvent& cme = evt.xclient;
    if (cme.data.l[0] == m_deleteAtom)
        handleDestroy(evt, win);
}

void skWindowContextX11::processMessage(skWindow* win, XEvent& evt) const
{
    skWindowX11* xWindow = (skWindowX11*)win;

    switch (evt.type)
    {
    case ConfigureNotify:
        handleConfigure(evt, xWindow);
        break;
    case Expose:
        handleExpose(evt, xWindow);
        break;
    case DestroyNotify:
        handleDestroy(evt, xWindow);
        break;
    case MotionNotify:
        handleMotion(evt, xWindow);
        break;
    case ButtonPress:
    case ButtonRelease:
        handleButton(evt, xWindow);
        break;
    case ClientMessage:
        handleClient(evt, xWindow);
        break;
    case KeyPress:
    case KeyRelease:
        handleKey(evt, xWindow);
        break;
    default:
        break;
    }
}

SKint32 skWindowContextX11::getScanCode(SKuint32 code)
{
    if (code >= XK_0 && code <= XK_9)
        return (SKint32)KC_0 + (code - XK_0);
    if (code >= XK_A && code <= XK_Z)
        return (SKint32)KC_A + (code - XK_A);
    if (code >= XK_a && code <= XK_z)
        return (SKint32)KC_A + (code - XK_a);
    if (code >= XK_F1 && code <= XK_F12)
        return (SKint32)KC_F1 + (code - XK_F1);
    if (code >= XK_KP_0 && code <= XK_KP_9)
        return (SKint32)KC_PAD0 + (code - XK_KP_0);

    // all key codes are mapped to the first unmodified
    // code: 1,2,3,4,5 == !,@,#,$,%
    switch (code)
    {
    case XK_KP_Insert:  // comes in ! (as XK_KP_0)
        return KC_PAD0;
    case XK_KP_Delete:
        return KC_PAD_PERIOD;
    case XK_KP_End:
        return KC_PAD1;
    case XK_KP_Down:
        return KC_PAD2;
    case XK_KP_Page_Down:
        return KC_PAD3;
    case XK_KP_Left:
        return KC_PAD4;
    case XK_KP_Begin:
        return KC_PAD5;
    case XK_KP_Right:
        return KC_PAD6;
    case XK_KP_Home:
        return KC_PAD7;
    case XK_KP_Up:
        return KC_PAD8;
    case XK_KP_Page_Up:
        return KC_PAD9;
    case XK_apostrophe:
        return KC_QUOTE;
    case XK_Page_Up:
        return KC_PAGEUP;
    case XK_Page_Down:
        return KC_PAGEDOWN;
    case XK_Linefeed:
        return KC_LINEFEED;
    case XK_BackSpace:
        return KC_BACKSPACE;
    case XK_Tab:
        return KC_TAB;
    case XK_Return:
        return KC_RET;
    case XK_Pause:
        return KC_PAUSE;
    case XK_Escape:
        return KC_ESC;
    case XK_Delete:
        return KC_DEL;
    case XK_Home:
        return KC_HOME;
    case XK_Left:
        return KC_LEFT;
    case XK_Up:
        return KC_UP;
    case XK_Right:
        return KC_RIGHT;
    case XK_Down:
        return KC_DOWN;
    case XK_End:
        return KC_END;
    case XK_Insert:
        return KC_INSERT;
    case XK_KP_Enter:
        return KC_PAD_RET;
    case XK_KP_Multiply:
        return KC_PAD_MUL;
    case XK_KP_Add:
        return KC_PAD_ADD;
    case XK_KP_Subtract:
        return KC_PAD_SUB;
    case XK_KP_Divide:
        return KC_PAD_DIV;
    case XK_KP_Decimal:
        return KC_PAD_PERIOD;
    case XK_Shift_L:
        return KC_LSHIFT;
    case XK_Shift_R:
        return KC_RSHIFT;
    case XK_Control_L:
        return KC_LCTRL;
    case XK_Control_R:
        return KC_RCTRL;
    case XK_Caps_Lock:
        return KC_CAPSLOCK;
    case XK_Alt_L:
        return KC_LALT;
    case XK_Alt_R:
        return KC_RALT;
    case XK_space:
        return KC_SPACE;
    case XK_comma:
        return KC_COMMA;
    case XK_minus:
        return KC_MINUS;
    case XK_period:
        return KC_PERIOD;
    case XK_slash:
        return KC_SLASH;
    case XK_semicolon:
        return KC_SEMICOLON;
    case XK_equal:
        return KC_EQUAL;
    case XK_bracketleft:
        return KC_LEFTBRACKET;
    case XK_backslash:
        return KC_BACKSLASH;
    case XK_bracketright:
        return KC_RIGHTBRACKET;
    case XK_grave:
        return KC_ACCENTGRAVE;
    default:
    case XK_asciicircum:
    case XK_underscore:
    case XK_braceleft:
    case XK_bar:
    case XK_braceright:
    case XK_asciitilde:
    case XK_at:
    case XK_question:
    case XK_greater:
    case XK_less:
    case XK_colon:
    case XK_exclam:
    case XK_quotedbl:
    case XK_numbersign:
    case XK_dollar:
    case XK_percent:
    case XK_ampersand:
    case XK_parenleft:
    case XK_parenright:
    case XK_asterisk:
    case XK_plus:
        // 2nd

    case XK_Meta_L:
    case XK_Meta_R:
    case XK_Super_L:
    case XK_Super_R:
    case XK_Hyper_L:
    case XK_Hyper_R:
    case XK_Shift_Lock:
    case XK_KP_Separator:
    case XK_KP_Equal:
    case XK_Mode_switch:
    case XK_Num_Lock:
    case XK_KP_Space:
    case XK_KP_Tab:
    case XK_Execute:
    case XK_Print:
    case XK_Select:
    case XK_Begin:
    case XK_Sys_Req:
    case XK_Scroll_Lock:
    case XK_Clear:
    case XK_Undo:
    case XK_Redo:
    case XK_Menu:
    case XK_Find:
    case XK_Cancel:
    case XK_Help:
    case XK_Break:
        return KC_UNKNOWN;
    }
}
