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
#include "skWindow.h"
#include "skKeyboard.h"
#include "skMouse.h"

skWindow::skWindow(skWindowManager* creator) :
    m_creator(creator),
    m_context(nullptr),
    m_keyboard(nullptr),
    m_mouse(nullptr),
    m_width(0),
    m_height(0)
{
    initialize();
}

skWindow::~skWindow()
{
    delete m_keyboard;
    m_keyboard = nullptr;

    delete m_mouse;
    m_mouse = nullptr;
}

void skWindow::initialize()
{
    if (!m_keyboard)
        m_keyboard = new skKeyboard();

    if (!m_mouse)
        m_mouse = new skMouse();

    if (m_creator)
    {
        if (!m_context)
            m_context = m_creator->getContext();
    }
}

void skWindow::__notifyMotion(const SKint32& xPos, const SKint32& yPos) const
{
    if (m_mouse)
        m_mouse->notifyMotion(xPos, yPos);
}

void skWindow::__notifyWheel(const SKint32& zDelta) const
{
    if (m_mouse)
        m_mouse->notifyWheel(zDelta);
}

void skWindow::__notifyButton(const SKint32& button, const SKuint8& state) const
{
    if (m_mouse)
        m_mouse->notifyButton(button, state);
}

void skWindow::__notifyKey(const SKint32& key, const SKuint8& state) const
{
    if (m_keyboard)
        m_keyboard->notifyKey(key, state);
}

void skWindow::__clearRelativeStates() const
{
    if (m_mouse)
    {
        m_mouse->x.rel = 0;
        m_mouse->y.rel = 0;
        m_mouse->z.rel = 0;
    }
}
