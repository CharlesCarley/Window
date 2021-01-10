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

    setupOpenGL();

    if (m_flags & WM_WF_SHOWN)
        show(true);
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

void skWindowX11::capture(void)
{
}

void skWindowX11::notifySize(SKuint32 w, SKuint32 h)
{
    m_width  = w;
    m_height = h;
}

void skWindowX11::notifyMotion(SKint32 x, SKint32 y) const
{
    m_mouse->x.abs = x;
    m_mouse->y.abs = y;
}
