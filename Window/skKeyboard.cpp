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
#include "Window/skKeyboard.h"
#include "Utils/skAllocator.h"
#include "Utils/skPlatformHeaders.h"

skKeyboard::skKeyboard() :
    m_table(),
    key(KC_NONE)
{
    skMemset(m_table, WM_RELEASED, sizeof(SKkeyTable));
}

bool skKeyboard::isKeyDown(const SKuint32& code) const
{
    if (code > KC_NONE && code < KC_MAX)
        return m_table[code] == WM_PRESSED;
    return false;
}

void skKeyboard::notifyKey(const SKint32& code, const SKuint8& state)
{
    key = code;

    if (code > KC_NONE && code < KC_MAX)
    {
        m_table[code] = state;
        if (code >= KC_LCTRL && code <= KC_RSHIFT)
        {
            switch (code)
            {
            case KC_LCTRL:
            case KC_RCTRL:
                m_table[KC_CTRL] = state;
                break;
            case KC_LSHIFT:
            case KC_RSHIFT:
                m_table[KC_SHIFT] = state;
                break;
            case KC_LALT:
            case KC_RALT:
                m_table[KC_ALT] = state;
                break;
            default:
                break;
            }
        }
    }
}

const char* skKeyboard::toString(const SKint32& code)
{
    SWITCH_TO_STRING_BEGIN(code, KC_NONE);
    CASE_TO_STRING(KC_NONE);
    CASE_TO_STRING(KC_A);
    CASE_TO_STRING(KC_B);
    CASE_TO_STRING(KC_C);
    CASE_TO_STRING(KC_D);
    CASE_TO_STRING(KC_E);
    CASE_TO_STRING(KC_F);
    CASE_TO_STRING(KC_G);
    CASE_TO_STRING(KC_H);
    CASE_TO_STRING(KC_I);
    CASE_TO_STRING(KC_J);
    CASE_TO_STRING(KC_K);
    CASE_TO_STRING(KC_L);
    CASE_TO_STRING(KC_M);
    CASE_TO_STRING(KC_N);
    CASE_TO_STRING(KC_O);
    CASE_TO_STRING(KC_P);
    CASE_TO_STRING(KC_Q);
    CASE_TO_STRING(KC_R);
    CASE_TO_STRING(KC_S);
    CASE_TO_STRING(KC_T);
    CASE_TO_STRING(KC_U);
    CASE_TO_STRING(KC_V);
    CASE_TO_STRING(KC_W);
    CASE_TO_STRING(KC_X);
    CASE_TO_STRING(KC_Y);
    CASE_TO_STRING(KC_Z);
    CASE_TO_STRING(KC_0);
    CASE_TO_STRING(KC_1);
    CASE_TO_STRING(KC_2);
    CASE_TO_STRING(KC_3);
    CASE_TO_STRING(KC_4);
    CASE_TO_STRING(KC_5);
    CASE_TO_STRING(KC_6);
    CASE_TO_STRING(KC_7);
    CASE_TO_STRING(KC_8);
    CASE_TO_STRING(KC_9);
    CASE_TO_STRING(KC_CAPSLOCK);
    CASE_TO_STRING(KC_ESC);
    CASE_TO_STRING(KC_TAB);
    CASE_TO_STRING(KC_RET);
    CASE_TO_STRING(KC_SPACE);
    CASE_TO_STRING(KC_LINEFEED);
    CASE_TO_STRING(KC_BACKSPACE);
    CASE_TO_STRING(KC_DEL);
    CASE_TO_STRING(KC_SEMICOLON);
    CASE_TO_STRING(KC_PERIOD);
    CASE_TO_STRING(KC_COMMA);
    CASE_TO_STRING(KC_QUOTE);
    CASE_TO_STRING(KC_ACCENTGRAVE);
    CASE_TO_STRING(KC_MINUS);
    CASE_TO_STRING(KC_SLASH);
    CASE_TO_STRING(KC_BACKSLASH);
    CASE_TO_STRING(KC_EQUAL);
    CASE_TO_STRING(KC_LEFTBRACKET);
    CASE_TO_STRING(KC_RIGHTBRACKET);
    CASE_TO_STRING(KC_PAD0);
    CASE_TO_STRING(KC_PAD1);
    CASE_TO_STRING(KC_PAD2);
    CASE_TO_STRING(KC_PAD3);
    CASE_TO_STRING(KC_PAD4);
    CASE_TO_STRING(KC_PAD5);
    CASE_TO_STRING(KC_PAD6);
    CASE_TO_STRING(KC_PAD7);
    CASE_TO_STRING(KC_PAD8);
    CASE_TO_STRING(KC_PAD9);
    CASE_TO_STRING(KC_PAD_PERIOD);
    CASE_TO_STRING(KC_PAD_DIV);
    CASE_TO_STRING(KC_PAD_MUL);
    CASE_TO_STRING(KC_PAD_ADD);
    CASE_TO_STRING(KC_PAD_SUB);
    CASE_TO_STRING(KC_PAD_RET);
    CASE_TO_STRING(KC_LEFT);
    CASE_TO_STRING(KC_DOWN);
    CASE_TO_STRING(KC_RIGHT);
    CASE_TO_STRING(KC_UP);
    CASE_TO_STRING(KC_F1);
    CASE_TO_STRING(KC_F2);
    CASE_TO_STRING(KC_F3);
    CASE_TO_STRING(KC_F4);
    CASE_TO_STRING(KC_F5);
    CASE_TO_STRING(KC_F6);
    CASE_TO_STRING(KC_F7);
    CASE_TO_STRING(KC_F8);
    CASE_TO_STRING(KC_F9);
    CASE_TO_STRING(KC_F10);
    CASE_TO_STRING(KC_F11);
    CASE_TO_STRING(KC_F12);
    CASE_TO_STRING(KC_PAUSE);
    CASE_TO_STRING(KC_INSERT);
    CASE_TO_STRING(KC_HOME);
    CASE_TO_STRING(KC_PAGEUP);
    CASE_TO_STRING(KC_PAGEDOWN);
    CASE_TO_STRING(KC_END);
    CASE_TO_STRING(KC_UNKNOWN);
    CASE_TO_STRING(KC_COMMAND);
    CASE_TO_STRING(KC_GRLESS);
    CASE_TO_STRING(KC_LCTRL);
    CASE_TO_STRING(KC_LALT);
    CASE_TO_STRING(KC_LSHIFT);
    CASE_TO_STRING(KC_RCTRL);
    CASE_TO_STRING(KC_RALT);
    CASE_TO_STRING(KC_RSHIFT);
    CASE_TO_STRING(KC_CTRL);
    CASE_TO_STRING(KC_ALT);
    CASE_TO_STRING(KC_SHIFT);
    SWITCH_TO_STRING_END()
}
