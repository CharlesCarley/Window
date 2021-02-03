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
#include "Window/SDL/skWindowContextSDL.h"
#include <SDL.h>
#include "Utils/skDisableWarnings.h"
#include "Utils/skLogger.h"
#include "Window/SDL/skWindowSDL.h"
#include "Window/skWindowManager.h"

skWindowContextSDL::skWindowContextSDL(skWindowManager* owner) :
    skWindowContext(owner)
{
}

void skWindowContextSDL::finalize(void)
{
    SDL_Quit();
}

void skWindowContextSDL::initialize(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        skLogd(LD_ERROR, SDL_GetError());
}

void skWindowContextSDL::process(void)
{
    bool waitForNext = true;

    m_shouldDispatch = true;
    SDL_Event msg;

    do
    {
        while (SDL_PollEvent(&msg))
        {
            handleEvent(msg);
            waitForNext = false;
        }
        if (waitForNext)
            SDL_Delay(1);

    } while (waitForNext);

    m_shouldDispatch = false;
}

void skWindowContextSDL::processInteractive(bool dispatch)
{
    m_shouldDispatch = dispatch;

    SDL_Event msg;
    while (SDL_PollEvent(&msg))
        handleEvent(msg);
}

void skWindowContextSDL::handleEvent(SDL_Event& evt)
{
    switch (evt.type)
    {
    case SDL_WINDOWEVENT:
        handleWindowEvent(evt);
        break;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        handleKeyEvent(evt);
        break;

    case SDL_MOUSEMOTION:
    case SDL_MOUSEWHEEL:
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        handleMouseEvent(evt);
        break;
    default:
        break;
    }
}

void skWindowContextSDL::handleWindowEvent(SDL_Event& evt)
{
    skWindowSDL* win = (skWindowSDL*)find(evt.window.windowID);
    if (win != nullptr)
    {
        if (evt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            win->notifySizeChange(evt.window.data1, evt.window.data2);

            if (shouldDispatch())
                m_creator->dispatchEvent(SK_WIN_SIZE, win);
        }
        else if (evt.window.event == SDL_WINDOWEVENT_EXPOSED)
        {
            if (shouldDispatch())
                m_creator->dispatchEvent(SK_WIN_PAINT, win);
        }
        else if (evt.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            if (shouldDispatch())
                m_creator->dispatchEvent(SK_WIN_DESTROY, win);

            m_creator->destroy(win);
            m_shouldDispatch = false;
        }
    }
}

void skWindowContextSDL::handleKeyEvent(SDL_Event& evt) const
{
    skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
    if (win)
    {
        win->handleKey(evt.key);

        if (shouldDispatch())
        {
            if (evt.key.type == SDL_KEYDOWN)
                m_creator->dispatchEvent(SK_KEY_PRESSED, win);
            else
                m_creator->dispatchEvent(SK_KEY_RELEASED, win);
        }
    }
}

void skWindowContextSDL::handleMouseEvent(SDL_Event& evt) const
{
    if (evt.type == SDL_MOUSEWHEEL)
    {
        skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
        if (win)
        {
            win->handleMouseWheel(evt.wheel);

            if (shouldDispatch())
                m_creator->dispatchEvent(SK_MOUSE_WHEEL, win);
        }
    }
    else if (evt.type == SDL_MOUSEBUTTONDOWN || evt.type == SDL_MOUSEBUTTONUP)
    {
        skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
        if (win)
        {
            win->handleMouseButton(evt.button);

            if (shouldDispatch())
            {
                if (evt.type == SDL_MOUSEBUTTONDOWN)
                    m_creator->dispatchEvent(SK_MOUSE_PRESSED, win);
                else
                    m_creator->dispatchEvent(SK_MOUSE_RELEASED, win);
            }
        }
    }
    else if (evt.type == SDL_MOUSEMOTION)
    {
        skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
        if (win)
        {
            win->handleMouseMotion(evt.motion);

            if (shouldDispatch())
                m_creator->dispatchEvent(SK_MOUSE_MOVED, win);
        }
    }
}
