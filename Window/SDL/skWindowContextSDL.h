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
#ifndef _skWindowManagerContextSDL_h_
#define _skWindowManagerContextSDL_h_

#include <SDL.h>
#include "Window/skWindowContext.h"
#include "Window/skWindowTypes.h"

class skWindowManagerContextSDL final : public skWindowContext
{
private:
    bool m_capture;

    void handleEvent(SDL_Event& evt);
    void handleWindowEvent(SDL_Event& evt);
    void handleKeyEvent(SDL_Event& evt) const;
    void handleMouseEvent(SDL_Event& evt) const;

    static void setKeyTable(SKkeyTable& table, SKint32 code, SKuint8 pressed);

public:
    explicit skWindowManagerContextSDL(skWindowManager* owner);

    void finalize(void) override;
    void initialize(void) override;

    void processInteractive(bool dispatch = false) override;
    void process(void) override;
};

#endif  //_skWindowManagerContextSDL_h_
