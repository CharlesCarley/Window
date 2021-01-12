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
#include "skWindowManager.h"
#include "SDL/skWindowContextSDL.h"
#include "SDL/skWindowSDL.h"
#include "Utils/skLogger.h"
#include "Window/Inject/skWindowContextInject.h"
#include "Window/Inject/skWindowInject.h"
#include "skWindow.h"
#include "skWindowHandler.h"

#if SK_PLATFORM == SK_PLATFORM_WIN32

#include "Win32/skWindowContextWin32.h"
#include "Win32/skWindowWin32.h"

// Conditional backend classes
#define skPlatformWindow skWindowWin32
#define skWindowContextPlat skWindowContextWin32

#ifdef WITH_SDL
#define skPlatformWindowSDL skWindowSDL
#define skPlatformContextSDL skWindowContextSDL
#else

#define skPlatformWindowSDL skWindowWin32
#define skPlatformContextSDL skWindowContextWin32
#endif

#elif SK_PLATFORM == SK_PLATFORM_LINUX
#include "X11/skWindowContextX11.h"
#include "X11/skWindowX11.h"

#define skPlatformWindow skWindowX11
#define skWindowContextPlat skWindowContextX11

#ifdef WITH_SDL
#define skPlatformWindowSDL skWindowSDL
#define skPlatformContextSDL skWindowContextSDL
#else

#define skPlatformWindowSDL skWindowX11
#define skPlatformContextSDL skWindowContextX11
#endif

#else

#ifdef WITH_SDL
#define skPlatformWindow skWindowSDL
#define skWindowContextPlat skWindowContextSDL
#define skPlatformWindowSDL skWindowSDL
#define skPlatformContextSDL skWindowContextSDL
#else
#error "Backend not supported"
#endif

#endif

skWindowManager::skWindowManager(skContextType type) :
    m_winDirty(true),
    m_contextType(type),
    m_postShow(true)
{
    m_context = createContextInstance();
}

skWindowManager::~skWindowManager()
{
    WindowHash::Iterator it = m_windows.iterator();

    while (it.hasMoreElements())
        delete it.getNext().second;

    HandlerArray::Iterator hit = m_handlers.iterator();
    while (it.hasMoreElements())
        delete hit.getNext();

    if (m_context)
    {
        m_context->finalize();
        delete m_context;
    }
}

skWindowContext* skWindowManager::createContextInstance()
{
    skWindowContext* context;

    if (m_contextType == skContextType::WM_CTX_INJECT)
    {
        context = new skWindowManagerContextInject(this);
        context->initialize();
    }
    else if (m_contextType == skContextType::WM_CTX_PLATFORM)
    {
        context = new skWindowContextPlat(this);
        context->initialize();
    }
    else
    {
        context = new skPlatformContextSDL(this);
        context->initialize();
    }
    return context;
}

skWindow* skWindowManager::createWindowInstance()
{
    skWindow* window;

    if (m_contextType == skContextType::WM_CTX_INJECT)
        window = new skWindowInject(this);
    else if (m_contextType == skContextType::WM_CTX_PLATFORM)
        window = new skPlatformWindow(this);
    else
        window = new skPlatformWindowSDL(this);
    return window;
}

void skWindowManager::dispatchInitialEvents(void)
{
    if (m_postShow)
    {
        m_postShow = false;
        this->broadcastEvent(skEventType::SK_WIN_SIZE);
        this->broadcastEvent(skEventType::SK_WIN_PAINT);
    }
}

bool skWindowManager::processInteractive(bool dispatch)
{
    SK_ASSERT(m_context);
    handleLoopStart();
    m_context->processInteractive(dispatch);
    return handleDirty();
}

void skWindowManager::process(void)
{
    SK_ASSERT(m_context);
    while (!m_windows.empty())
    {
        m_context->process();
        handleDirty();
    }
}

void skWindowManager::handleLoopStart()
{
    WindowHash::Iterator it = m_windows.iterator();
    while (it.hasMoreElements())
        it.getNext().second->__clearRelativeStates();
}

bool skWindowManager::handleDirty(void)
{
    if (m_winDirty)
    {
        if (!m_destroyWindows.empty())
        {
            const SKsize s = m_destroyWindows.size();

            const WindowArray::PointerType p = m_destroyWindows.ptr();

            SKsize i = 0;
            while (i < s)
            {
                skWindow* win = p[i++];
                m_windows.erase(win->getWindowHandle());
                delete win;
            }
            m_destroyWindows.clear();
        }

        m_winDirty = false;
        return !m_windows.empty();
    }

    return true;
}

void skWindowManager::addHandler(skWindowHandler* handler)
{
    m_handlers.push_back(handler);
}

void skWindowManager::removeHandler(skWindowHandler* handler)
{
    const SKuint32 loc = m_handlers.find(handler);

    if (loc != SK_NPOS32)
        m_handlers.remove(loc);
}

void skWindowManager::destroy(skWindow* window)
{
    m_destroyWindows.push_back(window);
    m_winDirty = true;
}

void skWindowManager::destroyAll()
{
    WindowHash::Iterator it = m_windows.iterator();
    while (it.hasMoreElements())
        destroy(it.getNext().second);
    m_winDirty = true;
}

skWindow* skWindowManager::create(const char*    title,
                                  const SKuint32 width,
                                  const SKuint32 height,
                                  const SKuint32 flags)
{
    skWindow* window = createWindowInstance();
    window->create(title, width, height, flags);

    const SKsize handle = window->getWindowHandle();
    if (handle == SK_NPOS)
    {
        skLogd(LD_ERROR, "Create returned an invalid window handle\n");

        delete window;
        window = nullptr;
    }
    else
        m_windows.insert(handle, window);

    return window;
}

skWindowContext* skWindowManager::getContext(void) const
{
    return m_context;
}

void skWindowManager::dispatchEvent(const skEventType& event, skWindow* window)
{
    if (m_handlers.empty())
        return;

    HandlerArray::Iterator it = m_handlers.iterator();
    while (it.hasMoreElements())
        it.getNext()->handle(event, window);
}

void skWindowManager::broadcastEvent(const skEventType& event)
{
    if (m_handlers.empty())
        return;

    HandlerArray::Iterator it = m_handlers.iterator();
    while (it.hasMoreElements())
    {
        skWindowHandler* hand = it.getNext();

        WindowHash::Iterator wit = m_windows.iterator();
        while (wit.hasMoreElements())
            hand->handle(event, wit.getNext().second);
    }
}
