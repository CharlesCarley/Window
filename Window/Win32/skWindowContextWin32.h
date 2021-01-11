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
#ifndef _skWindowContextWin32_h_
#define _skWindowContextWin32_h_

#include "Utils/skArray.h"
#include "Window/skWindowContext.h"
#include "Window/skWindowTypes.h"
class skWindowWin32;

#define SK_WINDOW_CLASS_NAME "skWindowContextWin32"

class skWindowContextWin32 final : public skWindowContext
{
private:
    friend class skWindowWin32;

    typedef skArray<skWindowWin32*> WindowArray;

    WindowArray m_refresh;
    SKuintPtr   m_module;

    void queueRefreshWindow(skWindowWin32*);

    void invalidateWindows();

    void handlePaint(skWindowWin32* window) const;

    void handleSize(skWindowWin32* window, SKuintPtr lParam) const;

    void handleClose(skWindowWin32* window) const;

    void handleMouse(skWindowWin32* window,
                     SKuint32       message,
                     SKuintPtr      wParam,
                     SKuintPtr      lParam) const;

    void handleKey(skWindowWin32* window,
                   SKuint32       message,
                   SKuintPtr      wParam) const;

public:
    explicit skWindowContextWin32(skWindowManager* owner);

    ~skWindowContextWin32() override;

    void initialize(void) override;

    void processInteractive(bool dispatch = false) override;

    void process(void) override;

    SKintPtr handleProcedure(skWindowWin32* window,
                             SKuint32       message,
                             SKuintPtr      wParam,
                             SKuintPtr      lParam) const;
};

#endif  //_skWindowContextWin32_h_
