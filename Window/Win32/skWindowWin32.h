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
#ifndef _skWindowWin32_h_
#define _skWindowWin32_h_

#include "Utils/skPlatformHeaders.h"
#include "Window/skWindow.h"
#include "Window/skWindowTypes.h"

class skWindowWin32 final : public skWindow
{
private:
    friend class skWindowContextWin32;

    SKint32  m_pz, m_lz;
    SKuint32 m_lx, m_ly;
    bool     m_init;
    HWND     m_hWnd;
    HDC      m_dc;
    HGLRC    m_glRC;

    static int getScanCode(SKuintPtr wParam);
    void       setupOpenGL(void);

    void invalidate() const;
    void validate() const;
    void makeCurrent() const;

public:
    skWindowWin32(skWindowManager* creator);

    ~skWindowWin32() override;

    void create(const char* title, SKuint32 width, SKuint32 height, SKuint32 flags) override;

    void refresh(void) override;

    void show(bool doShow) override;
    void flush(void) override;
    void capture(void) override;

    SKsize getWindowHandle(void) override
    {
        return m_hWnd ? (SKsize)(void*)m_hWnd : SK_NPOS;
    }

    void sizedChanged(SKuintPtr lParam);
    void handleKey(SKuint32 msg, SKuintPtr wParam);
    void handleMouse(SKuint32 msg, SKuintPtr wParam, SKuintPtr lParam);
};

#endif  //_skWindowWin32_h_
