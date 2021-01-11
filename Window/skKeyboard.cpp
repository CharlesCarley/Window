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
#include "Utils/skPlatformHeaders.h"

skKeyboard::skKeyboard() :
    m_table()
//key(KC_NONE)
{
    skMemset(m_table, WM_RELEASED, sizeof(SKkeyTable));
}


bool skKeyboard::isKeyDown(const SKuint32& code) const
{
    if (code > KC_NONE && code < KC_MAX)
        return m_table[code] == WM_PRESSED;
    return false;
}


void skKeyboard::notifyKey(const SKint32& key, const SKuint8& state)
{
    if (key > KC_NONE && key < KC_MAX)
    {
        m_table[key] = state;

        if (key >= KC_LCTRL && key <= KC_RSHIFT)
        {
            switch (key)
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
