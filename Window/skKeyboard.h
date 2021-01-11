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
#ifndef _skKeyboard_h_
#define _skKeyboard_h_

#include "Window/skWindowTypes.h"

/// <summary>
/// Provides access to the current keyboard.
///
/// States are stored in a table that holds a boolean
/// value of its current state.
/// Access to the instance of skKeyboard can be found in the skWindow class.
/// </summary>
class skKeyboard
{
private:
    SKkeyTable m_table;

    friend class skWindow;

    void notifyKey(const SKint32& code, const SKuint8& state);

public:
    skKeyboard();
    ~skKeyboard() = default;

    /// <summary>
    /// Tests a specific key state.
    /// </summary>
    /// <param name="code">The scan code to test</param>
    /// <returns>returns true if the key is pressed, false otherwise.</returns>
    bool isKeyDown(const SKuint32& code) const;

    /// <returns>The table of keyboard input states</returns>
    SKkeyTable& getTable()
    {
        return m_table;
    }

    /// <summary>
    /// The last key code modified
    /// </summary>
    SKint32 key;

    /// <summary>
    /// Utility to get a string for the key code.
    /// </summary>
    /// <param name="code">A skScanCode value</param>
    /// <returns></returns>
    static const char* toString(const SKint32& code);
};

#endif  //_skKeyboard_h_
