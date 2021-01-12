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
#ifndef _skWindow_h_
#define _skWindow_h_

#include "Window/skWindowTypes.h"
#include "skWindowManager.h"

/// <summary>
/// Is the base class for all windows.
///
/// Windows do not get instanced directly.Instead, it's the job of the window
/// manager to issue instances based on the desired backend context.
/// The backend context is supplied when the
/// <see cref="skWindowManager::skWindowManager">window manager</see> is created.
///
/// <seealso cref="skContextType"/>
/// </summary>
class skWindow
{
protected:
    skWindowManager* m_creator;
    skWindowContext* m_context;
    skKeyboard*      m_keyboard;
    skMouse*         m_mouse;
    SKuint32         m_width;
    SKuint32         m_height;

    friend class skWindowManager;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="xPos"></param>
    /// <param name="yPos"></param>
    void __notifyMotion(const SKint32& xPos, const SKint32& yPos) const;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="zDelta"></param>
    void __notifyWheel(const SKint32& zDelta) const;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="button"></param>
    /// <param name="state"></param>
    void __notifyButton(const SKint32& button, const SKuint8& state) const;

    /// <summary>
    /// 
    /// </summary>
    /// <param name="key"></param>
    /// <param name="state"></param>
    void __notifyKey(const SKint32& key, const SKuint8& state) const;

    /// <summary>
    /// 
    /// </summary>
    void __clearRelativeStates() const;

    /// <summary>
    /// Actually creates the window.
    /// </summary>
    /// <param name="title">The window title</param>
    /// <param name="width">the desired window's width in pixels</param>
    /// <param name="height">the desired window's height in pixels</param>
    /// <param name="flags">Extra creation flags</param>
    virtual void create(const char* title, SKuint32 width, SKuint32 height, SKuint32 flags) = 0;

    /// <summary>
    /// \brief Default Constructor.
    /// Do not call directly, use \ref skWindowManager::create
    /// </summary>
    /// <param name="creator">Manager that created the window.</param>
    skWindow(skWindowManager* creator);

private:
    void initialize();

public:
    virtual ~skWindow();

    /// <summary>
    /// Invalidates the window so that a redraw event will take place.
    /// </summary>
    virtual void refresh(void) = 0;

    /// <summary>
    /// Shows or hides the window.
    /// </summary>
    /// <param name="showIt"></param>
    virtual void show(bool showIt) = 0;

    /// <summary>
    /// Swaps internal window buffers.
    /// </summary>
    virtual void flush(void) = 0;

    /// <summary>
    /// Provides access to the underlying window handle.
    /// 
    /// The win32 backend returns HWND pointer, the SDL and X11 backend return 
    /// an integer id value.
    /// </summary>
    /// <returns>Returns the underlying window system window handle.</returns>
    virtual SKsize getWindowHandle(void) = 0;



    /// <returns>Returns the manager that created this window.</returns>
    skWindowManager* getCreator(void) const
    {
        return m_creator;
    }

    /// <returns>Returns the base class of the internal platform context.</returns>
    skWindowContext* getContext() const
    {
        return m_context;
    }

    /// <returns>Returns a pointer to the keyboard device</returns>
    skKeyboard* getKeyboard(void) const
    {
        return m_keyboard;
    }

    /// <returns>Returns a reference to the keyboard device</returns>
    skKeyboard& getKeyboardRef() const
    {
        SK_ASSERT(m_keyboard);
        return *m_keyboard;
    }

    /// <returns>Returns a pointer to the mouse device</returns>
    skMouse* getMouse(void) const
    {
        return m_mouse;
    }

    /// <returns>Returns a reference to the mouse device</returns>
    skMouse& getMouseRef() const
    {
        SK_ASSERT(m_mouse);
        return *m_mouse;
    }

    /// <returns>Returns the width of the window in pixels</returns>
    SKuint32 getWidth(void) const
    {
        return m_width;
    }

    /// <returns>Returns the height of the window in pixels</returns>
    SKuint32 getHeight(void) const
    {
        return m_height;
    }

    /// <summary>
    /// Closes this window. 
    /// 
    /// The window will not close immediately. Instead, it is pushed to a 
    /// list in the manager, then the next call to 
    /// <see cref="skWindowManager::process">process</see> or 
    /// <see cref="skWindowManager::process">processInteractive</see> will remove and 
    /// destroy the window.
    void close()
    {
        SK_ASSERT(m_creator);
        m_creator->destroy(this);
    }
};

#endif  //_skWindow_h_
