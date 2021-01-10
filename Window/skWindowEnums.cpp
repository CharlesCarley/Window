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
#include "Window/skWindowEnums.h"

#define KC_ToString(k) \
    case k:            \
        return #k

const char* skGetScanCodeString(SKint32 kc)
{
    switch (kc)
    {
        KC_ToString(KC_NONE);
        KC_ToString(KC_A);
        KC_ToString(KC_B);
        KC_ToString(KC_C);
        KC_ToString(KC_D);
        KC_ToString(KC_E);
        KC_ToString(KC_F);
        KC_ToString(KC_G);
        KC_ToString(KC_H);
        KC_ToString(KC_I);
        KC_ToString(KC_J);
        KC_ToString(KC_K);
        KC_ToString(KC_L);
        KC_ToString(KC_M);
        KC_ToString(KC_N);
        KC_ToString(KC_O);
        KC_ToString(KC_P);
        KC_ToString(KC_Q);
        KC_ToString(KC_R);
        KC_ToString(KC_S);
        KC_ToString(KC_T);
        KC_ToString(KC_U);
        KC_ToString(KC_V);
        KC_ToString(KC_W);
        KC_ToString(KC_X);
        KC_ToString(KC_Y);
        KC_ToString(KC_Z);
        KC_ToString(KC_0);
        KC_ToString(KC_1);
        KC_ToString(KC_2);
        KC_ToString(KC_3);
        KC_ToString(KC_4);
        KC_ToString(KC_5);
        KC_ToString(KC_6);
        KC_ToString(KC_7);
        KC_ToString(KC_8);
        KC_ToString(KC_9);
        KC_ToString(KC_CAPSLOCK);
        KC_ToString(KC_ESC);
        KC_ToString(KC_TAB);
        KC_ToString(KC_RET);
        KC_ToString(KC_SPACE);
        KC_ToString(KC_LINEFEED);
        KC_ToString(KC_BACKSPACE);
        KC_ToString(KC_DEL);
        KC_ToString(KC_SEMICOLON);
        KC_ToString(KC_PERIOD);
        KC_ToString(KC_COMMA);
        KC_ToString(KC_QUOTE);
        KC_ToString(KC_ACCENTGRAVE);
        KC_ToString(KC_MINUS);
        KC_ToString(KC_SLASH);
        KC_ToString(KC_BACKSLASH);
        KC_ToString(KC_EQUAL);
        KC_ToString(KC_LEFTBRACKET);
        KC_ToString(KC_RIGHTBRACKET);
        KC_ToString(KC_PAD0);
        KC_ToString(KC_PAD1);
        KC_ToString(KC_PAD2);
        KC_ToString(KC_PAD3);
        KC_ToString(KC_PAD4);
        KC_ToString(KC_PAD5);
        KC_ToString(KC_PAD6);
        KC_ToString(KC_PAD7);
        KC_ToString(KC_PAD8);
        KC_ToString(KC_PAD9);
        KC_ToString(KC_PAD_PERIOD);
        KC_ToString(KC_PAD_DIV);
        KC_ToString(KC_PAD_MUL);
        KC_ToString(KC_PAD_ADD);
        KC_ToString(KC_PAD_SUB);
        KC_ToString(KC_PAD_RET);
        KC_ToString(KC_LEFT);
        KC_ToString(KC_DOWN);
        KC_ToString(KC_RIGHT);
        KC_ToString(KC_UP);
        KC_ToString(KC_F1);
        KC_ToString(KC_F2);
        KC_ToString(KC_F3);
        KC_ToString(KC_F4);
        KC_ToString(KC_F5);
        KC_ToString(KC_F6);
        KC_ToString(KC_F7);
        KC_ToString(KC_F8);
        KC_ToString(KC_F9);
        KC_ToString(KC_F10);
        KC_ToString(KC_F11);
        KC_ToString(KC_F12);
        KC_ToString(KC_PAUSE);
        KC_ToString(KC_INSERT);
        KC_ToString(KC_HOME);
        KC_ToString(KC_PAGEUP);
        KC_ToString(KC_PAGEDOWN);
        KC_ToString(KC_END);
        KC_ToString(KC_UNKNOWN);
        KC_ToString(KC_COMMAND);
        KC_ToString(KC_GRLESS);
        KC_ToString(KC_LCTRL);
        KC_ToString(KC_LALT);
        KC_ToString(KC_LSHIFT);
        KC_ToString(KC_RCTRL);
        KC_ToString(KC_RALT);
        KC_ToString(KC_RSHIFT);
        KC_ToString(KC_CTRL);
        KC_ToString(KC_ALT);
        KC_ToString(KC_SHIFT);
    default:
        KC_ToString(KC_MAX);
    }
}
