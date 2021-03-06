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
#ifndef _skMouse_h_
#define _skMouse_h_

#include "Window/skWindowTypes.h"

/// <summary>
/// Value pair for mouse motion values.
/// </summary>
class skMouseAxis
{
public:
    skMouseAxis() :
        abs(0),
        rel(0)
    {
    }

    /// <summary>
    /// Holds the actual value acquired from
    /// the event system.
    /// </summary>
    SKint32 abs;

    /// <summary>
    /// Holds the relative amount of change from one
    /// event to the next.
    /// </summary>
    SKint32 rel;
};

/// <summary>
/// Provides access to the current mouse.
///
/// Access to the instance of this class can be found in the skWindow class.
/// </summary>
class skMouse
{
private:
    SKmouseTable m_table;
    friend class skWindow;

    SKint32 m_states[4];

    void notifyMotion(const SKint32& xPos, const SKint32& yPos);
    void notifyWheel(const SKint32& zPos);
    void notifyButton(const SKint32& code, const SKuint8& state);

public:
    skMouse();
    ~skMouse() = default;

    /// <summary>
    /// Tests a specific button state.
    /// </summary>
    /// <param name="code">The mouse button code to test</param>
    /// <returns>returns true if the button is pressed, false otherwise.</returns>
    /// <seealso cref="skMouseCode"/>
    bool isButtonDown(const SKint32& code) const;

    /// <returns>Access to table of input states</returns>
    SKmouseTable& getTable()
    {
        return m_table;
    }

    /// <summary>
    /// The last button code modified
    /// </summary>
    SKint32 button;

    /// <summary>
    /// The axis is split into two values absolute and relative.
    /// X and Y is the cursor position, and Z is the wheel rotation.
    /// The absolute values for the x and y mouse coordinates are
    /// relative to the window's left top corner.
    /// The absolute z value is a fixed value of +- skWheelDelta.
    /// The relative x, y, and z values are between [-1, 1].
    /// </summary>
    skMouseAxis x, y, z;

    /// <summary>
    /// Utility to get a string for the button code.
    /// </summary>
    /// <param name="code">A skMouseCode value</param>
    /// <returns>a string representation of skMouseCode</returns>
    /// <seealso cref="skMouseCode"/>
    static const char* toString(const SKint32& code);
};

#endif  //_skMouse_h_
