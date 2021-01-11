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
#ifndef _skWindowContext_h_
#define _skWindowContext_h_

#include "skWindowManager.h"

class skWindowContext
{
protected:
    skWindowManager* m_creator;
    bool             m_shouldDispatch;

    skWindow* find(const SKsize win) const
    {
        // The search key needs to be a unique identifier.
        // For a window in windows its the integer representation
        // of the HWND structure. On SDL/X11 its the Window ID handle.
        const SKsize loc = m_creator->m_windows.find(win);
        if (loc != SK_NPOS)
            return m_creator->m_windows.at(loc);
        return nullptr;
    }

public:
    explicit skWindowContext(skWindowManager* owner) :
        m_creator(owner),
        m_shouldDispatch(false)
    {
    }

    virtual ~skWindowContext() = default;

    /// <summary>
    /// Called before the manager destroys this class.
    /// Preforms any platform specific tear down.
    /// </summary>
    virtual void finalize(void)
    {
    }

    /// <summary>
    /// Called when the manager instances the derived class.
    /// Preforms any platform specific initialization.
    /// </summary>
    virtual void initialize() = 0;

    /// <summary>
    /// Preforms one event poling loop.
    /// The main idea is to populate classes from events
    /// and then access their state later.
    /// </summary>
    /// <param name="dispatch">
    /// A value of true means populate the event classes
    /// and dispatch callbacks to any listeners.
    /// </param>
    virtual void processInteractive(bool dispatch = false) = 0;

    /// <summary>
    /// Preforms a continuous loop and sleeps if there are no events
    /// to process. A callback handler should be set in the manager
    /// to access events.
    /// </summary>
    virtual void process(void) = 0;

    /// <returns>Returns true if event callbacks should be issued.</returns>
    bool shouldDispatch() const
    {
        return m_shouldDispatch;
    }
};

#endif  //_skWindowContext_h_
