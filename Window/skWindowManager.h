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
#ifndef _skWindowManager_h_
#define _skWindowManager_h_

#include "Utils/skMap.h"
#include "skWindowTypes.h"

/// <summary>
/// Manages event handling, creation and deletion
/// for windows in this system.
/// </summary>
class skWindowManager final
{
public:
    typedef skHashTable<SKsize, skWindow*> WindowHash;
    typedef skArray<skWindow*>             WindowArray;
    typedef skArray<skWindowHandler*>      HandlerArray;

protected:
    bool             m_winDirty;
    skContextType    m_contextType;
    skWindowContext* m_context;
    WindowHash       m_windows;
    WindowArray      m_destroyWindows;
    HandlerArray     m_handlers;

private:
    friend class skWindowContext;

    bool handleDirty(void);

    skWindowContext* createContextInstance();

    skWindow* createWindowInstance();

    void handleLoopStart();

public:

    /// <summary>
    /// Main constructor for a window manager.
    /// </summary>
    /// <param name="type">
    /// Specifies the backend platform to use. If this is SDL and
    ///  SDL support is not enabled, then it will default to the native 
    ///  platform backend
    /// </param>
    /// <param name="handler">
    /// Provides an option to add a window message 
    /// handler on construction. 
    /// </param>
    explicit skWindowManager(skContextType    type    = skContextType::WM_CTX_PLATFORM,
                             skWindowHandler* handler = nullptr);

    ~skWindowManager();

    /// <summary>
    /// Creates a managed window.
    /// </summary>
    ///
    /// <param name="title">The window title.</param>
    /// <param name="width">The desired window's width in pixels.</param>
    /// <param name="height">The desired window's height in pixels.</param>
    /// <param name="flags">Extra creation <see cref="skWindowFlags">flags</see>. </param>
    /// <returns>A window instance.</returns>
    skWindow* create(const char* title, SKuint32 width, SKuint32 height, SKuint32 flags);

    /// <summary>
    /// Schedules a window for deletion.
    /// </summary>
    /// <param name="window">The window to destroy.</param>
    void destroy(skWindow* window);

    /// <summary>
    /// Schedules all windows for deletion.
    /// </summary>
    void destroyAll();

    /// <summary>
    /// Preforms one event poling loop.
    ///
    /// The main idea of this method is to populate input classes from
    /// events and access their state later without using event handlers.
    /// </summary>
    /// <param name="dispatch">
    /// If dispatch is set to true, then event callbacks will be issued.
    ///</param>
    bool processInteractive(bool dispatch = false);

    /// <summary>
    /// Preforms a continuous loop and sleeps if there are no events
    /// to process.
    ///
    /// A callback handler should be set in the manager to access events.
    /// </summary>
    void process();

    void dispatchInitialEvents();

    /// <returns>Returns the internal context.</returns>
    skWindowContext* getContext() const;

    /// <summary>
    /// Sends the event and window to all registered handlers.
    /// </summary>
    /// <param name="event">The type of event.</param>
    /// <param name="window">The window where the event took place.</param>
    void dispatchEvent(const skEventType& event, skWindow* window);

    /// <summary>
    /// Dispatches the event to all windows.
    /// </summary>
    /// <param name="event">The type of event</param>
    void broadcastEvent(const skEventType& event);

    /// <summary>
    /// Registers the supplied callback listener.
    /// </summary>
    void addHandler(skWindowHandler* handler);

    /// <summary>
    /// Removes the supplied callback listener.
    /// </summary>
    void removeHandler(skWindowHandler* handler);

    /// <summary>
    /// Deletes all handlers attached to the manager.
    /// </summary>
    void deleteAllHandlers();

    /// <returns>Returns true if any handlers are registered.</returns>
    bool hasHandlers() const
    {
        return !m_handlers.empty();
    }

    /// <returns>Returns an iterator for all active windows.</returns>
    WindowHash::Iterator getWindowIterator()
    {
        return m_windows.iterator();
    }
};

#endif  //_skWindowManager_h_
