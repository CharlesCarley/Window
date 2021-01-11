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
#include "Window/skMouse.h"
#include "Utils/skPlatformHeaders.h"

skMouse::skMouse() :
    m_table(),
    m_states{}
{
    m_states[0] = SK_NPOS32H;
    m_states[1] = SK_NPOS32H;
    skMemset(m_table, WM_RELEASED, sizeof(SKmouseTable));
}

bool skMouse::isButtonDown(const SKint32& code) const
{
    if (code > MBT_None && code < MBT_Max)
        return m_table[code] == WM_PRESSED;
    return false;
}


void skMouse::notifyMotion(const SKint32& xPos, const SKint32& yPos)
{
    if (m_states[0] == SK_NPOS32H)
    {
        m_states[0] = xPos;
        m_states[1] = yPos;
    }

    x.abs = xPos;
    y.abs = yPos;
    x.rel = x.abs - m_states[0];
    y.rel = y.abs - m_states[1];

    m_states[0] = xPos;
    m_states[1] = yPos;
}


void skMouse::notifyWheel(const SKint32& zPos)
{
    z.abs = zPos > 0 ? skWheelDelta : -skWheelDelta;
    z.rel = zPos > 0 ? 1 : -1;
}


void skMouse::notifyButton(const SKint32& button, const SKuint8& state)
{
    if (button > MBT_None && button < MBT_Max)
        m_table[button] = state;

}
