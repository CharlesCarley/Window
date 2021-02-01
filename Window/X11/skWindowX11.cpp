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

#include "skWindowX11.h"
#include <X11/Xatom.h>
#include <cstring>
#include "Utils/skLogger.h"
#include "Window/X11/skWindowContextX11.h"
#include "Window/skMouse.h"
#include "Window/skWindowManager.h"
#include "Window/skWindowTypes.h"

extern void skLoadOpenGL();

const SKuint32 SK_eventMask = ExposureMask | StructureNotifyMask |
                              PointerMotionMask | VisibilityChangeMask | ButtonPressMask |
                              ButtonReleaseMask | KeyPressMask | KeyReleaseMask;


skWindowX11::skWindowX11(skWindowManager* creator) :
    skWindow(creator),
    m_display(nullptr),
    m_visual(nullptr),
    m_window(XNullWindow),
    m_glContext(nullptr),
    m_dirty(false),
    m_flags(0)
{
}

skWindowX11::~skWindowX11()
{
    if (m_display != nullptr && m_window != XNullWindow)
        XDestroyWindow(m_display, m_window);
}

void skWindowX11::create(const char* title, SKuint32 width, SKuint32 height, SKuint32 flags)
{
    skWindowContextX11* ctx = (skWindowContextX11*)getContext();
    if (ctx == nullptr)
    {
        skLogd(LD_ERROR, "Failed to get internal context\n");
        return;
    }

    m_display = ctx->getXDisplay();
    if (m_display == nullptr)
    {
        skLogd(LD_ERROR, "Failed to get X display\n");
        return;
    }

    m_flags = flags;
    m_title = title;

    const Window desktop = XDefaultRootWindow(m_display);

    int attributes[] = {
        GLX_RGBA,
        GLX_DEPTH_SIZE,
        24,
        GLX_DOUBLEBUFFER,
        None,
    };

    m_width  = width;
    m_height = height;

    m_visual = glXChooseVisual(m_display, 0, attributes);

    if (!m_visual)
    {
        skLogd(LD_ERROR, "glXChooseVisual failed\n");
        return;
    }

    const Colormap colorMap = XCreateColormap(m_display,
                                              desktop,
                                              m_visual->visual,
                                              AllocNone);

    XSetWindowAttributes windowAttributes;
    skMemset(&windowAttributes, 0, sizeof(XSetWindowAttributes));

    windowAttributes.colormap   = colorMap;
    windowAttributes.event_mask = SK_eventMask;

    SKint32 xPos = 0, yPos = 0;
    if (flags & WM_WF_CENTER)
    {
        SKint32 dw, dh;
        dw = XDisplayWidth(m_display, DefaultScreen(m_display));
        dh = XDisplayHeight(m_display, DefaultScreen(m_display));

        const SKint32 lft = (int)dw - (int)width >> 1;
        const SKint32 top = (int)dh - (int)height >> 1;

        xPos = (SKint32)skClamp<int>(lft, 0, dw - 10);
        yPos = (SKint32)skClamp<int>(top, 0, dh - 10);
    }

    m_window = XCreateWindow(m_display,                 // display
                             desktop,                   // parent
                             xPos,                      // x
                             yPos,                      // y
                             m_width,                   // width
                             m_height,                  // height
                             10,                        // border
                             m_visual->depth,           // depth
                             InputOutput,               // class
                             m_visual->visual,          // visual
                             CWColormap | CWEventMask,  // value mask
                             &windowAttributes          // attributes
    );

    XSizeHints hints = {};

    if (flags & WM_WF_CENTER)
        hints.flags = PPosition | PSize;

    if (flags & WM_WF_DIALOG)
    {
        hints.width      = m_width;
        hints.height     = m_height;
        hints.max_width  = m_width;
        hints.max_height = m_height;
        hints.min_width  = m_width;
        hints.min_height = m_height;
        hints.flags |= PMinSize | PMaxSize;
    }
    XSetNormalHints(m_display, m_window, &hints);

    notifyTitle();

    if (m_flags & WM_WF_MAXIMIZE)
        notifyMaximized();

    if (m_flags & WM_WF_SHOWN)
        show(true);

    setupOpenGL();
}

void skWindowX11::notifyMaximized(void) const
{
    if (!m_display || !m_window)
        return;

    XEvent     baseEvt = {};
    const Atom wmState = XInternAtom(m_display, "_NET_WM_STATE", False);

    // horizontal & vertical to match the standard behavior
    const Atom horizontal = XInternAtom(m_display, "_NET_WM_STATE_MAXIMIZED_HORZ", False);
    const Atom vertical   = XInternAtom(m_display, "_NET_WM_STATE_MAXIMIZED_VERT", False);

    baseEvt.xclient = XClientMessageEvent{
        ClientMessage,      // type
        0,                  // serial
        False,              // send_event
        m_display,          // display
        m_window,           // window
        wmState,            // message_type
        MessageFormatLong,  // format
    };

    baseEvt.xclient.data.l[0] = 1;
    baseEvt.xclient.data.l[1] = horizontal;
    baseEvt.xclient.data.l[2] = vertical;

    if (XSendEvent(m_display,
                   XDefaultRootWindow(m_display),
                   False,
                   StructureNotifyMask,
                   &baseEvt) == 0)
    {
        skLogd(LD_ERROR, "XSendEvent StructureNotifyMask failed\n");
    }
}

void skWindowX11::notifyTitle(void) const
{
    if (!m_display || !m_window || m_title.empty())
        return;

    XTextProperty prop = {
        (unsigned char*)m_title.c_str(),
        XA_STRING,
        MessageFormatByte,
        m_title.size()};

    XSetWMName(m_display, m_window, &prop);
}

void skWindowX11::notifyShow(void) const
{
    skWindowContextX11* ctx = (skWindowContextX11*)getContext();
    if (ctx)
    {
        if (XSetWMProtocols(m_display, m_window, &ctx->m_deleteAtom, 1) == 0)
        {
            skLogd(LD_ERROR, "XSetWMProtocols failed\n");
        }
    }
}

void skWindowX11::setupOpenGL(void)
{
    m_glContext = glXCreateContext(m_display, m_visual, nullptr, GL_TRUE);
    if (m_glContext == nullptr)
        skLogd(LD_ERROR, "glXCreateContext failed\n");
    else
    {
        if (glXMakeCurrent(m_display, m_window, m_glContext) == False)
            skLogd(LD_ERROR, "Failed to make the gl context current.\n");
        else
            skLoadOpenGL();
    }
}

void skWindowX11::refresh(void)
{
    if (m_dirty)
        return;

    if (m_display && m_window)
    {
        XEvent e = {};

        e.type           = Expose;
        e.xexpose.count  = 0;
        e.xexpose.window = m_window;

        if (XSendEvent(m_display, m_window, 0, ExposureMask, &e) == 0)
            skLogd(LD_ERROR, "XSendEvent failed\n");

        m_dirty = true;
    }
}

void skWindowX11::show(bool v)
{
    if (m_display && m_window)
    {
        if (v)
        {
            XMapWindow(m_display, m_window);

            if (m_flags & WM_WF_MAXIMIZE)
                notifyMaximized();

            XFlush(m_display);
            notifyShow();

            if (getContext()->shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_WIN_SHOWN, this);
        }
        else
        {
            XWithdrawWindow(m_display, m_window, 0);
            XFlush(m_display);

            if (getContext()->shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_WIN_HIDDEN, this);
        }
    }
}

void skWindowX11::flush(void)
{
    if (m_display && m_window)
    {
        glXSwapBuffers(m_display,
                       m_window);
    }
    m_dirty = false;
}


void skWindowX11::notifySize(SKuint32 w, SKuint32 h)
{
    m_width  = w;
    m_height = h;
}

void skWindowX11::handleMotion(const XMotionEvent& event) const
{
    __notifyMotion(event.x, event.y);
}

void skWindowX11::handleButton(const XButtonEvent& event) const
{
    __notifyMotion(event.x, event.y);

    SKint32 button = MBT_None;
    if (event.button == 1)
        button = MBT_L;
    else if (event.button == 2)
        button = MBT_M;
    else if (event.button == 3)
        button = MBT_R;

    __notifyButton(button, event.type == ButtonPress ? WM_PRESSED : WM_RELEASED);
}

void skWindowX11::handleWheel(const XButtonEvent& event) const
{
    if (event.button == 4 || event.button == 5)
        __notifyWheel(event.button == 4 ? 1 : -1);
}


void skWindowX11::handleKey(XEvent& event) const
{
    const SKint32 code = getScanCode(XLookupKeysym(&event.xkey, 0));

    __notifyKey(code, event.xkey.type == KeyPress ? WM_PRESSED : WM_RELEASED);
}

SKint32 skWindowX11::getScanCode(const SKint32& code)
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
        return KC_MAX;
    }
}
