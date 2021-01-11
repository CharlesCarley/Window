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


void skWindowSDL::handleKey(const SDL_KeyboardEvent& evt) const
{
    const SKuint32 code = getScanCode(evt.keysym.sym);
    if (code <= KC_NONE || code >= KC_MAX)
        return;

    __notifyKey(code, evt.type == SDL_KEYDOWN ? WM_PRESSED : WM_RELEASED);
}

void skWindowSDL::handleMouseButton(const SDL_MouseButtonEvent& evt) const
{
    __notifyMotion(evt.x, evt.y);

    SKuint32 btn = MBT_None;
    if (evt.button == SDL_BUTTON_LEFT)
        btn = MBT_L;
    else if (evt.button == SDL_BUTTON_MIDDLE)
        btn = MBT_M;
    else if (evt.button == SDL_BUTTON_RIGHT)
        btn = MBT_R;


    if (btn != MBT_None)
        __notifyButton(btn, evt.type == SDL_MOUSEBUTTONDOWN ? WM_PRESSED : WM_RELEASED);
}


void skWindowSDL::handleMouseMotion(const SDL_MouseMotionEvent& evt) const
{
    __notifyMotion(evt.x, evt.y);
}

void skWindowSDL::handleMouseWheel(const SDL_MouseWheelEvent& evt) const
{
    __notifyWheel(evt.y);
}


SKint32 skWindowSDL::getScanCode(const SKint32& keySym)
{
    switch (keySym)
    {
    case SDLK_RETURN:
        return KC_RET;
    case SDLK_ESCAPE:
        return KC_ESC;
    case SDLK_a:
        return KC_A;
    case SDLK_b:
        return KC_B;
    case SDLK_c:
        return KC_C;
    case SDLK_d:
        return KC_D;
    case SDLK_e:
        return KC_E;
    case SDLK_f:
        return KC_F;
    case SDLK_g:
        return KC_G;
    case SDLK_h:
        return KC_H;
    case SDLK_i:
        return KC_I;
    case SDLK_j:
        return KC_J;
    case SDLK_k:
        return KC_K;
    case SDLK_l:
        return KC_L;
    case SDLK_m:
        return KC_M;
    case SDLK_n:
        return KC_N;
    case SDLK_o:
        return KC_O;
    case SDLK_p:
        return KC_P;
    case SDLK_q:
        return KC_Q;
    case SDLK_r:
        return KC_R;
    case SDLK_s:
        return KC_S;
    case SDLK_t:
        return KC_T;
    case SDLK_u:
        return KC_U;
    case SDLK_v:
        return KC_V;
    case SDLK_w:
        return KC_W;
    case SDLK_x:
        return KC_X;
    case SDLK_y:
        return KC_Y;
    case SDLK_z:
        return KC_Z;
    case SDLK_0:
        return KC_0;
    case SDLK_1:
        return KC_1;
    case SDLK_2:
        return KC_2;
    case SDLK_3:
        return KC_3;
    case SDLK_4:
        return KC_4;
    case SDLK_5:
        return KC_5;
    case SDLK_6:
        return KC_6;
    case SDLK_7:
        return KC_7;
    case SDLK_8:
        return KC_8;
    case SDLK_9:
        return KC_9;
    case SDLK_KP_PERIOD:
        return KC_PAD_PERIOD;
    case SDLK_KP_DIVIDE:
        return KC_PAD_DIV;
    case SDLK_KP_MULTIPLY:
        return KC_PAD_MUL;
    case SDLK_KP_MINUS:
        return KC_PAD_SUB;
    case SDLK_KP_PLUS:
        return KC_PAD_ADD;
    case SDLK_KP_ENTER:
        return KC_PAD_RET;
    case SDLK_KP_0:
        return KC_PAD0;
    case SDLK_KP_1:
        return KC_PAD1;
    case SDLK_KP_2:
        return KC_PAD2;
    case SDLK_KP_3:
        return KC_PAD3;
    case SDLK_KP_4:
        return KC_PAD4;
    case SDLK_KP_5:
        return KC_PAD5;
    case SDLK_KP_6:
        return KC_PAD6;
    case SDLK_KP_7:
        return KC_PAD7;
    case SDLK_KP_8:
        return KC_PAD8;
    case SDLK_KP_9:
        return KC_PAD9;
    case SDLK_F1:
        return KC_F1;
    case SDLK_F2:
        return KC_F2;
    case SDLK_F3:
        return KC_F3;
    case SDLK_F4:
        return KC_F4;
    case SDLK_F5:
        return KC_F5;
    case SDLK_F6:
        return KC_F6;
    case SDLK_F7:
        return KC_F7;
    case SDLK_F8:
        return KC_F8;
    case SDLK_F9:
        return KC_F9;
    case SDLK_F10:
        return KC_F10;
    case SDLK_F11:
        return KC_F11;
    case SDLK_F12:
        return KC_F12;
    case SDLK_RIGHT:
        return KC_RIGHT;
    case SDLK_LEFT:
        return KC_LEFT;
    case SDLK_DOWN:
        return KC_DOWN;
    case SDLK_UP:
        return KC_UP;
    case SDLK_BACKSPACE:
        return KC_BACKSPACE;
    case SDLK_TAB:
        return KC_TAB;
    case SDLK_SPACE:
        return KC_SPACE;
    case SDLK_CAPSLOCK:
        return KC_CAPSLOCK;
    case SDLK_DELETE:
        return KC_DEL;
    case SDLK_MINUS:
        return KC_MINUS;
    case SDLK_COMMA:
        return KC_COMMA;
    case SDLK_PERIOD:
        return KC_PERIOD;
    case SDLK_SLASH:
        return KC_SLASH;
    case SDLK_SEMICOLON:
        return KC_SEMICOLON;
    case SDLK_PAUSE:
        return KC_PAUSE;
    case SDLK_INSERT:
        return KC_INSERT;
    case SDLK_HOME:
        return KC_HOME;
    case SDLK_PAGEUP:
        return KC_PAGEDOWN;
    case SDLK_END:
        return KC_END;
    case SDLK_PAGEDOWN:
        return KC_PAGEUP;
    case SDLK_EQUALS:
        return KC_EQUAL;
    case SDLK_QUOTE:
        return KC_QUOTE;
    case SDLK_BACKSLASH:
        return KC_BACKSLASH;
    case SDLK_BACKQUOTE:
        return KC_ACCENTGRAVE;
    case SDLK_LCTRL:
        return KC_LCTRL;
    case SDLK_LSHIFT:
        return KC_LSHIFT;
    case SDLK_LALT:
        return KC_LALT;
    case SDLK_RCTRL:
        return KC_RCTRL;
    case SDLK_RSHIFT:
        return KC_RSHIFT;
    case SDLK_RALT:
        return KC_RALT;
    default:
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
        break;
    }
    return KC_MAX;
}
