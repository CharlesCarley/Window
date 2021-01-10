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
#ifndef _skWindowTypes_h_
#define _skWindowTypes_h_

#include "Utils/skAllocator.h"
#include "Utils/skArray.h"
#include "Utils/skMap.h"
#include "skWindowEnums.h"

class skWindow;
class skWindowManager;
class skWindowHandler;
class skWindowContext;
class skKeyboard;
class skMouse;


/// <summary>
/// Array of boolean values, one per each scan code. 
/// </summary>
typedef SKuint8 SKkeyTable[KC_MAX];

/// <summary>
/// Array of boolean values, one per each scan code.
/// </summary>
typedef SKuint8 SKmouseTable[MBT_Max];


#endif  //_skWindowTypes_h_
