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

#include "skWindowTypes.h"

/// <summary>
/// Manages event handling, creation and deletion
/// for windows in this system.
/// </summary>
class skWindowManager
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
    bool             m_postShow;

private:
    skWindowContext* createContextInstance();
    skWindow*        createWindowInstance();

public:
    explicit skWindowManager(skContextType type = skContextType::WM_CTX_PLATFORM);
    ~skWindowManager();

    /// <summary>
    /// Creates a managed window.
    /// </summary>
    ///
    /// <param name="title">The window title</param>
    /// <param name="width">the desired window's width in pixels</param>
    /// <param name="height">the desired window's height in pixels</param>
    /// <param name="flags">Extra creation flags <see cref="skWindowFlags">skWindowFlags</see> </param>
    /// <returns>A window instance</returns>
    skWindow* create(const char* title, SKuint32 width, SKuint32 height, SKuint32 flags);

    /// <summary>
    /// Schedule a window for deletion.
    /// </summary>
    /// <param name="window">The window to destroy</param>
    void destroy(skWindow* window);

    /// <summary>
    ///
    /// </summary>
    void destroyAll();

    /// <summary>
    /// Preforms one event poling loop.
    /// The main idea is to populate classes from events
    /// and then access their state later.
    /// </summary>
    /// <param name="dispatch">
    /// A value of true means populate the event classes
    /// and dispatch callbacks to any listeners.
    /// </param>
    bool processInteractive(bool dispatch = false);

    /// <summary>
    /// Preforms a continuous loop and sleeps if there are no events
    /// to process. A callback handler should be set in the manager
    /// to access events.
    /// </summary>
    void process(void);

    void dispatchInitialEvents(void);


    skWindowContext* getContext(void) const;

    void addHandler(skWindowHandler* handler);
    void removeHandler(skWindowHandler* handler);



    /// <summary>
    /// Sends the event and window to all registered handlers
    /// </summary>
    /// <param name="event">The type of event</param>
    /// <param name="window">The window where the event took place</param>
    void dispatchEvent(const skEventType& event, skWindow* window);

    /// <summary>
    /// Dispatches the event to all windows. 
    /// </summary>
    /// <param name="event">The type of event</param>
    void broadcastEvent(const skEventType& event);


    void captureWindows(void);

    SK_INLINE bool hasHandlers(void) const
    {
        return !m_handlers.empty();
    }

    SK_INLINE WindowHash::Iterator getWindowIterator()
    {
        return m_windows.iterator();
    }

    void reserve(const SKuint32 cap)
    {
        m_windows.reserve((SKsize)cap);
        m_destroyWindows.reserve(cap);
        m_handlers.reserve(cap);
    }

    bool hasDirtyWindows() const
    {
        return !m_destroyWindows.empty();
    }

private:
    friend class skWindowContext;
    bool handleDirty(void);
};

#endif  //_skWindowManager_h_
