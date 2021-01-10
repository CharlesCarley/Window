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
#include "Utils/skDebugger.h"
#include "Utils/skLogger.h"
#include "Window/SDL/skWindowSDL.h"
#include "Window/skKeyboard.h"
#include "Window/skMouse.h"
#include "Window/skWindowManager.h"

skWindowManagerContextSDL::skWindowManagerContextSDL(skWindowManager* owner) :
    skWindowContext(owner)
{
    m_capture = false;
}

void skWindowManagerContextSDL::finalize(void)
{
    SDL_Quit();
}

void skWindowManagerContextSDL::initialize(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        skLogd(LD_ERROR, SDL_GetError());
}

void skWindowManagerContextSDL::process(void)
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

            // exit on the first occurrence
            // of a dirty window
            if (m_creator->hasDirtyWindows())
                break;
        }
        if (waitForNext)
            SDL_Delay(1);

    } while (waitForNext);

    m_shouldDispatch = false;
}

void skWindowManagerContextSDL::processInteractive(bool dispatch)
{
    m_shouldDispatch = dispatch;

    SDL_Event msg;
    while (SDL_PollEvent(&msg))
        handleEvent(msg);
}

void skWindowManagerContextSDL::handleEvent(SDL_Event& evt)
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

void skWindowManagerContextSDL::handleWindowEvent(SDL_Event& evt)
{
    skWindowSDL* win = (skWindowSDL*)find(evt.window.windowID);
    if (win != nullptr)
    {
        if (evt.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
        {
            win->notifySizeChange(evt.window.data1, evt.window.data2);

            if (shouldDispatch())
                m_creator->broadcastEvent(skEventType::SK_WIN_SIZE);
        }
        else if (evt.window.event == SDL_WINDOWEVENT_EXPOSED)
        {
            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_WIN_PAINT, win);
        }
        else if (evt.window.event == SDL_WINDOWEVENT_CLOSE)
        {
            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_WIN_DESTROY, win);

            m_creator->destroy(win);
            m_shouldDispatch = false;
        }
    }
}

void skWindowManagerContextSDL::handleKeyEvent(SDL_Event& evt) const
{
    const SKuint8 mode = evt.type == SDL_KEYDOWN ? WM_PRESSED : WM_RELEASED;

    skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
    if (win)
    {
        skKeyboard* key = win->getKeyboard();
        setKeyTable(key->getTable(), evt.key.keysym.sym, mode);

        if (shouldDispatch())
        {
            m_creator->dispatchEvent(
                mode == WM_PRESSED ? skEventType::SK_KEY_PRESSED : skEventType::SK_KEY_RELEASED,
                win);
        }
    }
}

void skWindowManagerContextSDL::handleMouseEvent(SDL_Event& evt) const
{
    if (evt.type == SDL_MOUSEWHEEL)
    {
        skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
        if (win)
        {
            skMouse* mouse = win->getMouse();
            mouse->z.abs   = evt.wheel.y > 0 ? skWheelDelta : -skWheelDelta;
            mouse->z.rel   = evt.wheel.y;

            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_MOUSE_WHEEL, win);
        }
    }
    else if (evt.type == SDL_MOUSEBUTTONDOWN)
    {
        skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
        if (win)
        {
            SKmouseTable& mouse = win->getMouseRef().getTable();
            if (evt.button.button == SDL_BUTTON_LEFT)
                mouse[MBT_L] = WM_PRESSED;
            else if (evt.button.button == SDL_BUTTON_MIDDLE)
                mouse[MBT_M] = WM_PRESSED;
            else if (evt.button.button == SDL_BUTTON_RIGHT)
                mouse[MBT_R] = WM_PRESSED;

            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_MOUSE_PRESSED, win);
        }
    }
    else if (evt.type == SDL_MOUSEBUTTONUP)
    {
        skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
        if (win)
        {
            SKmouseTable& mouse = win->getMouseRef().getTable();

            if (evt.button.button == SDL_BUTTON_LEFT)
                mouse[MBT_L] = WM_RELEASED;
            else if (evt.button.button == SDL_BUTTON_MIDDLE)
                mouse[MBT_M] = WM_RELEASED;
            else if (evt.button.button == SDL_BUTTON_RIGHT)
                mouse[MBT_R] = WM_RELEASED;

            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_MOUSE_RELEASED, win);
        }
    }
    else if (evt.type == SDL_MOUSEMOTION)
    {
        skWindowSDL* win = (skWindowSDL*)find(evt.wheel.windowID);
        if (win)
        {
            skMouse* mouse = win->getMouse();
            mouse->x.abs   = evt.motion.x;
            mouse->y.abs   = evt.motion.y;
            mouse->x.rel   = evt.motion.xrel;
            mouse->y.rel   = evt.motion.yrel;

            if (shouldDispatch())
                m_creator->dispatchEvent(skEventType::SK_MOUSE_MOVED, win);
        }
    }
}


void skWindowManagerContextSDL::setKeyTable(SKkeyTable& table, const SKint32 code, SKuint8 pressed)
{
    switch (code)
    {
    case SDLK_RETURN:
        table[KC_RET] = pressed;
        break;
    case SDLK_ESCAPE:
        table[KC_ESC] = pressed;
        break;
    case SDLK_a:
        table[KC_A] = pressed;
        break;
    case SDLK_b:
        table[KC_B] = pressed;
        break;
    case SDLK_c:
        table[KC_C] = pressed;
        break;
    case SDLK_d:
        table[KC_D] = pressed;
        break;
    case SDLK_e:
        table[KC_E] = pressed;
        break;
    case SDLK_f:
        table[KC_F] = pressed;
        break;
    case SDLK_g:
        table[KC_G] = pressed;
        break;
    case SDLK_h:
        table[KC_H] = pressed;
        break;
    case SDLK_i:
        table[KC_I] = pressed;
        break;
    case SDLK_j:
        table[KC_J] = pressed;
        break;
    case SDLK_k:
        table[KC_K] = pressed;
        break;
    case SDLK_l:
        table[KC_L] = pressed;
        break;
    case SDLK_m:
        table[KC_M] = pressed;
        break;
    case SDLK_n:
        table[KC_N] = pressed;
        break;
    case SDLK_o:
        table[KC_O] = pressed;
        break;
    case SDLK_p:
        table[KC_P] = pressed;
        break;
    case SDLK_q:
        table[KC_Q] = pressed;
        break;
    case SDLK_r:
        table[KC_R] = pressed;
        break;
    case SDLK_s:
        table[KC_S] = pressed;
        break;
    case SDLK_t:
        table[KC_T] = pressed;
        break;
    case SDLK_u:
        table[KC_U] = pressed;
        break;
    case SDLK_v:
        table[KC_V] = pressed;
        break;
    case SDLK_w:
        table[KC_W] = pressed;
        break;
    case SDLK_x:
        table[KC_X] = pressed;
        break;
    case SDLK_y:
        table[KC_Y] = pressed;
        break;
    case SDLK_z:
        table[KC_Z] = pressed;
        break;
    case SDLK_0:
        table[KC_0] = pressed;
        break;
    case SDLK_1:
        table[KC_1] = pressed;
        break;
    case SDLK_2:
        table[KC_2] = pressed;
        break;
    case SDLK_3:
        table[KC_3] = pressed;
        break;
    case SDLK_4:
        table[KC_4] = pressed;
        break;
    case SDLK_5:
        table[KC_5] = pressed;
        break;
    case SDLK_6:
        table[KC_6] = pressed;
        break;
    case SDLK_7:
        table[KC_7] = pressed;
        break;
    case SDLK_8:
        table[KC_8] = pressed;
        break;
    case SDLK_9:
        table[KC_9] = pressed;
        break;
    case SDLK_KP_PERIOD:
        table[KC_PAD_PERIOD] = pressed;
    case SDLK_KP_DIVIDE:
        table[KC_PAD_DIV] = pressed;
        break;
    case SDLK_KP_MULTIPLY:
        table[KC_PAD_MUL] = pressed;
        break;
    case SDLK_KP_MINUS:
        table[KC_PAD_SUB] = pressed;
        break;
    case SDLK_KP_PLUS:
        table[KC_PAD_ADD] = pressed;
        break;
    case SDLK_KP_ENTER:
        table[KC_PAD_RET] = pressed;
        break;
    case SDLK_KP_0:
        table[KC_PAD0] = pressed;
        break;
    case SDLK_KP_1:
        table[KC_PAD1] = pressed;
        break;
    case SDLK_KP_2:
        table[KC_PAD2] = pressed;
        break;
    case SDLK_KP_3:
        table[KC_PAD3] = pressed;
        break;
    case SDLK_KP_4:
        table[KC_PAD4] = pressed;
        break;
    case SDLK_KP_5:
        table[KC_PAD5] = pressed;
        break;
    case SDLK_KP_6:
        table[KC_PAD6] = pressed;
        break;
    case SDLK_KP_7:
        table[KC_PAD7] = pressed;
        break;
    case SDLK_KP_8:
        table[KC_PAD8] = pressed;
        break;
    case SDLK_KP_9:
        table[KC_PAD9] = pressed;
        break;
    case SDLK_F1:
        table[KC_F1] = pressed;
        break;
    case SDLK_F2:
        table[KC_F2] = pressed;
        break;
    case SDLK_F3:
        table[KC_F3] = pressed;
        break;
    case SDLK_F4:
        table[KC_F4] = pressed;
        break;
    case SDLK_F5:
        table[KC_F5] = pressed;
        break;
    case SDLK_F6:
        table[KC_F6] = pressed;
        break;
    case SDLK_F7:
        table[KC_F7] = pressed;
        break;
    case SDLK_F8:
        table[KC_F8] = pressed;
        break;
    case SDLK_F9:
        table[KC_F9] = pressed;
        break;
    case SDLK_F10:
        table[KC_F10] = pressed;
        break;
    case SDLK_F11:
        table[KC_F11] = pressed;
        break;
    case SDLK_F12:
        table[KC_F12] = pressed;
        break;
    case SDLK_RIGHT:
        table[KC_RIGHT] = pressed;
        break;
    case SDLK_LEFT:
        table[KC_LEFT] = pressed;
        break;
    case SDLK_DOWN:
        table[KC_DOWN] = pressed;
        break;
    case SDLK_UP:
        table[KC_UP] = pressed;
        break;
    case SDLK_BACKSPACE:
        table[KC_BACKSPACE] = pressed;
        break;
    case SDLK_TAB:
        table[KC_TAB] = pressed;
        break;
    case SDLK_SPACE:
        table[KC_SPACE] = pressed;
        break;
    case SDLK_CAPSLOCK:
        table[KC_CAPSLOCK] = pressed;
        break;
    case SDLK_DELETE:
        table[KC_DEL] = pressed;
        break;
    case SDLK_MINUS:
        table[KC_MINUS] = pressed;
        break;
    case SDLK_COMMA:
        table[KC_COMMA] = pressed;
        break;
    case SDLK_PERIOD:
        table[KC_PERIOD] = pressed;
        break;
    case SDLK_SLASH:
        table[KC_SLASH] = pressed;
        break;
    case SDLK_SEMICOLON:
        table[KC_SEMICOLON] = pressed;
        break;
    case SDLK_PAUSE:
        table[KC_PAUSE] = pressed;
        break;
    case SDLK_INSERT:
        table[KC_INSERT] = pressed;
        break;
    case SDLK_HOME:
        table[KC_HOME] = pressed;
        break;
    case SDLK_PAGEUP:
        table[KC_PAGEDOWN] = pressed;
        break;
    case SDLK_END:
        table[KC_END] = pressed;
        break;
    case SDLK_PAGEDOWN:
        table[KC_PAGEUP] = pressed;
        break;
    case SDLK_EQUALS:
        table[KC_EQUAL] = pressed;
        break;
    case SDLK_QUOTE:
        table[KC_QUOTE] = pressed;
        break;
    case SDLK_BACKSLASH:
        table[KC_BACKSLASH] = pressed;
        break;
    case SDLK_BACKQUOTE:
        table[KC_ACCENTGRAVE] = pressed;
        break;
    case SDLK_LCTRL:
        table[KC_LCTRL] = pressed;
        table[KC_CTRL]  = pressed;
        break;
    case SDLK_LSHIFT:
        table[KC_LSHIFT] = pressed;
        table[KC_SHIFT]  = pressed;
        break;
    case SDLK_LALT:
        table[KC_LALT] = pressed;
        table[KC_ALT]  = pressed;
        break;
    case SDLK_RCTRL:
        table[KC_RCTRL] = pressed;
        table[KC_CTRL]  = pressed;
        break;
    case SDLK_RSHIFT:
        table[KC_RSHIFT] = pressed;
        table[KC_SHIFT]  = pressed;
        break;
    case SDLK_RALT:
        table[KC_RALT] = pressed;
        table[KC_ALT]  = pressed;
        break;
    default:
        /* Not Converted | As needed....
        case SDLK_APPLICATION:
        case SDLK_POWER:
        case SDLK_KP_EQUALS:
        case SDLK_F13:
        case SDLK_F14:
        case SDLK_F15:
        case SDLK_F16:
        case SDLK_F17:
        case SDLK_F18:
        case SDLK_F19:
        case SDLK_F20:
        case SDLK_F21:
        case SDLK_F22:
        case SDLK_F23:
        case SDLK_F24:
        case SDLK_EXECUTE:
        case SDLK_HELP:
        case SDLK_MENU:
        case SDLK_SELECT:
        case SDLK_STOP:
        case SDLK_AGAIN:
        case SDLK_UNDO:
        case SDLK_CUT:
        case SDLK_COPY:
        case SDLK_PASTE:
        case SDLK_FIND:
        case SDLK_MUTE:
        case SDLK_VOLUMEUP:
        case SDLK_VOLUMEDOWN:
        case SDLK_KP_COMMA:
        case SDLK_KP_EQUALSAS400:
        case SDLK_ALTERASE:
        case SDLK_SYSREQ:
        case SDLK_CANCEL:
        case SDLK_CLEAR:
        case SDLK_PRIOR:
        case SDLK_RETURN2:
        case SDLK_SEPARATOR:
        case SDLK_OUT:
        case SDLK_OPER:
        case SDLK_CLEARAGAIN:
        case SDLK_CRSEL:
        case SDLK_EXSEL:
        case SDLK_KP_00:
        case SDLK_KP_000:
        case SDLK_THOUSANDSSEPARATOR:
        case SDLK_DECIMALSEPARATOR:
        case SDLK_CURRENCYUNIT:
        case SDLK_CURRENCYSUBUNIT:
        case SDLK_KP_LEFTPAREN:
        case SDLK_KP_RIGHTPAREN:
        case SDLK_KP_LEFTBRACE:
        case SDLK_KP_RIGHTBRACE:
        case SDLK_KP_TAB:
        case SDLK_KP_BACKSPACE:
        case SDLK_KP_A:
        case SDLK_KP_B:
        case SDLK_KP_C:
        case SDLK_KP_D:
        case SDLK_KP_E:
        case SDLK_KP_F:
        case SDLK_KP_XOR:
        case SDLK_KP_POWER:
        case SDLK_KP_PERCENT:
        case SDLK_KP_LESS:
        case SDLK_KP_GREATER:
        case SDLK_KP_AMPERSAND:
        case SDLK_KP_DBLAMPERSAND:
        case SDLK_KP_VERTICALBAR:
        case SDLK_KP_DBLVERTICALBAR:
        case SDLK_KP_COLON:
        case SDLK_KP_HASH:
        case SDLK_KP_SPACE:
        case SDLK_KP_AT:
        case SDLK_KP_EXCLAM:
        case SDLK_KP_MEMSTORE:
        case SDLK_KP_MEMRECALL:
        case SDLK_KP_MEMCLEAR:
        case SDLK_KP_MEMADD:
        case SDLK_KP_MEMSUBTRACT:
        case SDLK_KP_MEMMULTIPLY:
        case SDLK_KP_MEMDIVIDE:
        case SDLK_KP_PLUSMINUS:
        case SDLK_KP_CLEAR:
        case SDLK_KP_CLEARENTRY:
        case SDLK_KP_BINARY:
        case SDLK_KP_OCTAL:
        case SDLK_KP_DECIMAL:
        case SDLK_KP_HEXADECIMAL:
        case SDLK_LGUI:
        case SDLK_RGUI:
        case SDLK_MODE:
        case SDLK_AUDIONEXT:
        case SDLK_AUDIOPREV:
        case SDLK_AUDIOSTOP:
        case SDLK_AUDIOPLAY:
        case SDLK_AUDIOMUTE:
        case SDLK_MEDIASELECT:
        case SDLK_WWW:
        case SDLK_MAIL:
        case SDLK_CALCULATOR:
        case SDLK_COMPUTER:
        case SDLK_AC_SEARCH:
        case SDLK_AC_HOME:
        case SDLK_AC_BACK:
        case SDLK_AC_FORWARD:
        case SDLK_AC_STOP:
        case SDLK_AC_REFRESH:
        case SDLK_AC_BOOKMARKS:
        case SDLK_BRIGHTNESSDOWN:
        case SDLK_BRIGHTNESSUP:
        case SDLK_DISPLAYSWITCH:
        case SDLK_KBDILLUMTOGGLE:
        case SDLK_KBDILLUMDOWN:
        case SDLK_KBDILLUMUP:
        case SDLK_EJECT:
        case SDLK_SLEEP:
        case SDLK_APP1:
        case SDLK_APP2:
        case SDLK_AUDIOREWIND:

        // 2nd - based
        case SDLK_PLUS:
        case SDLK_UNDERSCORE:
        case SDLK_RIGHTPAREN:
        case SDLK_LEFTPAREN:
        case SDLK_ASTERISK:
        case SDLK_AMPERSAND:
        case SDLK_CARET:
        case SDLK_PERCENT:
        case SDLK_DOLLAR:
        case SDLK_HASH:
        case SDLK_AT:
        case SDLK_EXCLAIM:
        case SDLK_COLON:
        case SDLK_QUOTEDBL:
        case SDLK_LESS:
        case SDLK_GREATER:
        case SDLK_QUESTION:
        case SDLK_LEFTBRACKET:
        case SDLK_RIGHTBRACKET:
        case SDLK_PRINTSCREEN:
        case SDLK_SCROLLLOCK:
        case SDLK_NUMLOCKCLEAR:
    */
        break;
    }
}
