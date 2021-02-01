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
#ifndef _skWindowEnums_h_
#define _skWindowEnums_h_
#include "Utils/Config/skConfig.h"

SK_ST_C;

/// <summary>
///  Window creation flags.
/// </summary>
typedef enum skWindowFlags
{
    /// <summary>
    /// Default re-sizable window.
    /// </summary>
    WM_WF_DEFAULT = 0x0001,
    /// <summary>
    /// Non re-sizable window.
    /// </summary>
    WM_WF_DIALOG = 0x0002,
    /// <summary>
    /// Show maximized initially.
    /// </summary>
    WM_WF_MAXIMIZE = 0x0004,

    /// <summary>
    /// Center the window in the screen.
    /// </summary>
    WM_WF_CENTER = 0x0008,

    /// <summary>
    /// Show full screen. (not implemented at the moment)
    /// </summary>
    WM_WF_FULLSCREEN = 0x0010,

    /// <summary>
    /// Create an injection window. (deprecated).
    /// </summary>
    WM_WF_INJECTION = 0x0020,

    /// <summary>
    /// Capture the mouse indefinitely. (deprecated).
    /// </summary>
    WM_WF_CAPTURE = 0x0040,

    /// <summary>
    /// Create a window that is initially shown.
    /// </summary>
    WM_WF_SHOWN = 0x0080,
} skWindowFlags;

/// <summary>
/// Indicates which context the window manager should use.
/// </summary>
typedef enum skContextType
{
    /// <summary>
    /// Unused at the moment.
    /// It is meant to be used to embed into another system to manually inject input events.
    /// </summary>
    WM_CTX_INJECT,
    /// <summary>
    /// Use the native platform backend. Windows/X11
    /// </summary>
    WM_CTX_PLATFORM,
    /// <summary>
    /// Use the SDL backend.
    /// </summary>
    WM_CTX_SDL,
} skContextType;

/// <summary>
/// Unordered list of key code identifiers.
/// </summary>
typedef enum skScanCode
{
    KC_NONE,
    KC_A,
    KC_B,
    KC_C,
    KC_D,
    KC_E,
    KC_F,
    KC_G,
    KC_H,
    KC_I,
    KC_J,
    KC_K,
    KC_L,
    KC_M,
    KC_N,
    KC_O,
    KC_P,
    KC_Q,
    KC_R,
    KC_S,
    KC_T,
    KC_U,
    KC_V,
    KC_W,
    KC_X,
    KC_Y,
    KC_Z,
    KC_0,
    KC_1,
    KC_2,
    KC_3,
    KC_4,
    KC_5,
    KC_6,
    KC_7,
    KC_8,
    KC_9,
    KC_CAPSLOCK,
    KC_ESC,
    KC_TAB,
    KC_RET,
    KC_SPACE,
    KC_LINEFEED,
    KC_BACKSPACE,
    KC_DEL,
    KC_SEMICOLON,
    KC_PERIOD,
    KC_COMMA,
    KC_QUOTE,
    KC_ACCENTGRAVE,
    KC_MINUS,
    KC_SLASH,
    KC_BACKSLASH,
    KC_EQUAL,
    KC_LEFTBRACKET,
    KC_RIGHTBRACKET,
    KC_PAD0,
    KC_PAD1,
    KC_PAD2,
    KC_PAD3,
    KC_PAD4,
    KC_PAD5,
    KC_PAD6,
    KC_PAD7,
    KC_PAD8,
    KC_PAD9,
    KC_PAD_PERIOD,
    KC_PAD_DIV,
    KC_PAD_MUL,
    KC_PAD_ADD,
    KC_PAD_SUB,
    KC_PAD_RET,
    KC_LEFT,
    KC_DOWN,
    KC_RIGHT,
    KC_UP,
    KC_F1,
    KC_F2,
    KC_F3,
    KC_F4,
    KC_F5,
    KC_F6,
    KC_F7,
    KC_F8,
    KC_F9,
    KC_F10,
    KC_F11,
    KC_F12,
    KC_PAUSE,
    KC_INSERT,
    KC_HOME,
    KC_PAGEUP,
    KC_PAGEDOWN,
    KC_END,
    KC_UNKNOWN,
    KC_COMMAND,
    KC_GRLESS,
    KC_LCTRL,
    KC_LALT,
    KC_LSHIFT,
    KC_RCTRL,
    KC_RALT,
    KC_RSHIFT,
    KC_CTRL,
    KC_ALT,
    KC_SHIFT,
    KC_MAX
} skScanCode;

/// <summary>
/// Mouse button identifiers.
/// </summary>
typedef enum skMouseCode
{
    MBT_None,
    /// <summary>
    /// Left mouse button.
    /// </summary>
    MBT_L,
    /// <summary>
    /// Middle mouse button.
    /// </summary>
    MBT_M,
    /// <summary>
    /// Right mouse button.
    /// </summary>
    MBT_R,
    MBT_Max
} skMouseCode;

/// <summary>
/// The released state value for key and button tables.
/// </summary>
#define WM_RELEASED 0

/// <summary>
/// The pressed state value for key and button tables.
/// </summary>
#define WM_PRESSED 1

/// <summary>
/// Enumeration of window system events.
/// </summary>
typedef enum skEventType
{
    SK_WIN_EVT_UNKNOWN,

    /// <summary>
    /// The window needs painted.
    /// </summary>
    SK_WIN_PAINT,

    /// <summary>
    /// Called when the window's size changed.
    /// </summary>
    SK_WIN_SIZE,

    /// <summary>
    /// Called when the window is shown.
    /// </summary>
    SK_WIN_SHOWN,

    /// <summary>
    /// Called when the window is hidden.
    /// </summary>
    SK_WIN_HIDDEN,

    /// <summary>
    /// Called when the close button was clicked.
    /// </summary>
    SK_WIN_DESTROY,

    /// <summary>
    /// Called after a key press.
    /// </summary>
    SK_KEY_PRESSED,

    /// <summary>
    /// Called after a key release.
    /// </summary>
    SK_KEY_RELEASED,

    /// <summary>
    /// Called after the mouse was moved.
    /// </summary>
    SK_MOUSE_MOVED,

    /// <summary>
    /// Called after a mouse button was pressed.
    /// </summary>
    SK_MOUSE_PRESSED,

    /// <summary>
    /// Called after a mouse button was released.
    /// </summary>
    SK_MOUSE_RELEASED,

    /// <summary>
    /// Called after a wheel state change.
    /// </summary>
    SK_MOUSE_WHEEL,
} skEventType;

/// <summary>
/// Arbitrary scroll unit for the mouse wheel.
/// </summary>
const SKint32 skWheelDelta = 120;

#define SWITCH_TO_STRING_BEGIN(code, def) \
    switch (code)                         \
    {                                     \
    default:                              \
        return #def

#define SWITCH_TO_STRING_END() }

#define CASE_TO_STRING(v) \
    case v:               \
        return #v

SK_EN_C;
#endif  //_skWindowEnums_h_
