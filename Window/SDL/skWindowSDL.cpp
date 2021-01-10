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
#include "Window/SDL/skWindowSDL.h"
#include <SDL.h>
#include "OpenGL/skOpenGL.h"
#include "Utils/skLogger.h"
#include "Window/skWindowManager.h"
#include "Window/skWindowTypes.h"

skWindowSDL::skWindowSDL(skWindowManager* creator) :
    skWindow(creator),
    m_id(SK_NPOS32),
    m_window(nullptr),
    m_glc(nullptr)
{
}

skWindowSDL::~skWindowSDL()
{
    if (m_glc)
        SDL_GL_DeleteContext(m_glc);

    if (m_window)
        SDL_DestroyWindow(m_window);
}

void skWindowSDL::create(const char* title, SKuint32 w, SKuint32 h, SKuint32 flags)
{
    if (m_window != nullptr)
        return;

    SKuint32 xPos = SDL_WINDOWPOS_UNDEFINED, yPos = SDL_WINDOWPOS_UNDEFINED;

    SKuint32 windowFlags = SDL_WINDOW_OPENGL;
    if (flags & WM_WF_CENTER)
    {
        xPos = SDL_WINDOWPOS_CENTERED;
        yPos = SDL_WINDOWPOS_CENTERED;
    }


    if (!(flags & WM_WF_DIALOG))
        windowFlags |= SDL_WINDOW_RESIZABLE;

    if (flags & WM_WF_MAXIMIZE)
        windowFlags |= SDL_WINDOW_MAXIMIZED;

    m_width  = w;
    m_height = h;


    m_window = SDL_CreateWindow(title,
                                xPos,
                                yPos,
                                w,
                                h,
                                windowFlags);

    if (!m_window)
    {
        skLogd(LD_ERROR, SDL_GetError());
        return;
    }

    m_id = SDL_GetWindowID(m_window);

    m_glc = SDL_GL_CreateContext(m_window);
    if (!m_glc)
    {
        skLogd(LD_ERROR, SDL_GetError());
        return;
    }

    skLoadOpenGL();
}

void skWindowSDL::refresh(void)
{
    SDL_Event evt{};
    evt.type            = SDL_WINDOWEVENT;
    evt.window.event    = SDL_WINDOWEVENT_EXPOSED;
    evt.window.windowID = m_id;
    SDL_PushEvent(&evt);
}

void skWindowSDL::show(bool v)
{
    if (m_window)
    {
        if (v)
            SDL_ShowWindow(m_window);
        else
            SDL_HideWindow(m_window);
    }
}

void skWindowSDL::flush(void)
{
    if (m_glc && m_window)
        SDL_GL_SwapWindow(m_window);
}

void skWindowSDL::capture(void)
{
}

void skWindowSDL::notifySizeChange(SKuint32 w, SKuint32 h)
{
    m_width  = w;
    m_height = h;
}
