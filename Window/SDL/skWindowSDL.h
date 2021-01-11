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
#ifdef WITH_SDL
#ifndef _skWindowSDL_h_
#define _skWindowSDL_h_

#include <SDL.h>
#include "Window/skWindow.h"
#include "Window/skWindowTypes.h"

class skWindowSDL final : public skWindow
{
private:
    SKuint32      m_id;
    SDL_Window*   m_window;
    SDL_GLContext m_glc;

    friend class skWindowContextSDL;

    static SKint32 getScanCode(const SKint32& keySym);

    void handleKey(const SDL_KeyboardEvent& evt) const;

    void handleMouseButton(const SDL_MouseButtonEvent& evt) const;

    void handleMouseMotion(const SDL_MouseMotionEvent& evt) const;

    void handleMouseWheel(const SDL_MouseWheelEvent& evt) const;

    void notifySizeChange(SKuint32 w, SKuint32 h);

public:
    skWindowSDL(skWindowManager* creator);
    ~skWindowSDL() override;

    void create(const char* title, SKuint32 w, SKuint32 h, SKuint32 flags) override;

    void refresh(void) override;

    void show(bool v) override;

    void flush(void) override;

    SKsize getWindowHandle(void) override
    {
        return m_id;
    }
};

#endif  //WITH_SDL
#endif  //_skWindowSDL_h_
