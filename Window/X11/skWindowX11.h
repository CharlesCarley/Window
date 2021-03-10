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
#ifndef _skWindowX11_h_
#define _skWindowX11_h_

#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "Utils/skString.h"
#include "Window/skWindow.h"
#include "Window/skWindowTypes.h"
class skWindowContextX11;

class skWindowX11 final : public skWindow
{
private:
    skString         m_title;
    Display*         m_display;
    XVisualInfo*     m_visual;
    Window           m_window;
    GLXContext       m_glContext;
    bool             m_dirty;
    SKuint32         m_flags;

    friend class skWindowContextX11;

    void setupOpenGL(void);

    void notifyMaximized(void) const;

    void notifyTitle(void) const;

    void notifyShow(void) const;

    void notifySize(SKuint32 w, SKuint32 h);

    static SKint32 getScanCode(const SKint32& code);

    void handleKey(XEvent& event) const;

    void handleMotion(const XMotionEvent& event) const;

    void handleButton(const XButtonEvent& event) const;

    void handleWheel(const XButtonEvent& event) const;

    void _validate();

public:
    skWindowX11(skWindowManager* creator);

    virtual ~skWindowX11();

    void create(const char* title, SKuint32 width, SKuint32 height, SKuint32 flags) override;

    void refresh(void) override;

    void show(bool v) override;

    void flush(void) override;

    SKsize getWindowHandle(void) override
    {
        return m_window ? (SKsize)m_window : SK_NPOS;
    }
};

#endif  //_skWindowX11_h_
