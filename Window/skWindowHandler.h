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
#ifndef _skWindowHandler_h_
#define _skWindowHandler_h_

#include "Window/skWindowTypes.h"

/// <summary>
/// Window event handler.
/// Use with skWindowManager::addHandler to get
/// event callbacks through this class.
/// </summary>
class skWindowHandler
{
public:
    virtual ~skWindowHandler() = default;

    /// <summary>
    /// Handle a specific event
    /// </summary>
    /// <param name="event">The specific event type.</param>
    /// <param name="window">The window in which the event took place.</param>
    virtual void handle(const skEventType& event, skWindow* window) = 0;
};

#endif  //_skWindowHandler_h_
