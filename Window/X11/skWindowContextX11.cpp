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
#include "Window/skWindowManager.h"

skWindowContextX11::skWindowContextX11(skWindowManager* owner) :
    skWindowContext(owner),
    m_display(nullptr),
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

    win->handleMotion(evt.xmotion);

    if (shouldDispatch())
        m_creator->dispatchEvent(skEventType::SK_MOUSE_MOVED, win);
}

void skWindowContextX11::handleButton(XEvent& evt, skWindowX11* win) const
{
    SK_ASSERT(win);
    if (evt.xbutton.button >= 1 && evt.xbutton.button <= 3)
    {
        win->handleButton(evt.xbutton);

        if (shouldDispatch())
        {
            if (evt.type == ButtonPress)
                m_creator->dispatchEvent(skEventType::SK_MOUSE_PRESSED, win);
            else
                m_creator->dispatchEvent(skEventType::SK_MOUSE_RELEASED, win);
        }
    }
    else
    {
        if (evt.xbutton.type == ButtonPress)
        {
            win->handleWheel(evt.xbutton);

            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_MOUSE_WHEEL, win);
        }
    }
}

void skWindowContextX11::handleKey(XEvent& evt, skWindowX11* win) const
{
    win->handleKey(evt);

    if (shouldDispatch())
    {
        if (evt.xkey.type == KeyPress)
            m_creator->dispatchEvent(skEventType::SK_KEY_PRESSED, win);
        else
            m_creator->dispatchEvent(skEventType::SK_KEY_RELEASED, win);
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
