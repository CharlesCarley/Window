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
#include "Window/Win32/skWindowContextWin32.h"
#include "Utils/skDebugger.h"
#include "Utils/skLogger.h"
#include "Utils/skPlatformHeaders.h"
#include "Window/Win32/skWindowWin32.h"
#include "Window/skWindowManager.h"

// Define this in a resource file to use a custom icon
#define DEFAULT_ICON MAKEINTRESOURCE(1001)

class WindowProcStaticWrappers
{
public:
    static LRESULT WINAPI systemProc(HWND hWnd, const UINT message, const WPARAM wParam, const LPARAM lParam)
    {
        skWindowWin32* window = windowFromHwnd(hWnd);
        if (!window)
            return DefWindowProc(hWnd, message, wParam, lParam);

        skWindowContextWin32* ctx = (skWindowContextWin32*)window->getContext();
        if (!ctx)
        {
            skLogd(LD_ERROR, "Failed to get the window context\n");
            return DefWindowProc(hWnd, message, wParam, lParam);
        }

        // call into the wrapper
        return ctx->handleProcedure(window, message, wParam, lParam);
    }

    static skWindowWin32* windowFromHwnd(HWND hWnd)
    {
        // watch it, this value may be null until it is set
        // after creation. SystemProc gets event callbacks after
        // registration happens below.
        const LONG_PTR pointer = ::GetWindowLongPtr(hWnd, GWL_USER);
        if (pointer)
            return (skWindowWin32*)pointer;
        return nullptr;
    }
};

skWindowContextWin32::skWindowContextWin32(skWindowManager* owner) :
    skWindowContext(owner),
    m_module(0)
{
    m_refresh.reserve(2);
}

skWindowContextWin32::~skWindowContextWin32()
{
    if (m_module)
        UnregisterClass(SK_WINDOW_CLASS_NAME, (HMODULE)m_module);
}

void skWindowContextWin32::initialize(void)
{
    m_module = (SKuintPtr)GetModuleHandle(nullptr);
    if (!m_module)
    {
        skLogd(LD_ERROR, "Failed to get module handle\n");
        return;
    }

    WNDCLASS wc      = {};
    wc.hCursor       = LoadCursor(nullptr, IDC_ARROW);
    wc.hIcon         = LoadIcon((HMODULE)m_module, DEFAULT_ICON);
    wc.hInstance     = (HMODULE)m_module;
    wc.lpszClassName = SK_WINDOW_CLASS_NAME;
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WindowProcStaticWrappers::systemProc;

    if (RegisterClass(&wc) == 0)
        skLogd(LD_ERROR, "Register class failed\n");
}

void skWindowContextWin32::process(void)
{
    bool waitForMessage = true;
    MSG  message;

    m_shouldDispatch = true;

    do
    {
        while (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE) != 0)
        {
            TranslateMessage(&message);
            DispatchMessage(&message);
            waitForMessage = false;
        }

        if (waitForMessage)
            Sleep(1);

    } while (waitForMessage);

    m_shouldDispatch = false;

    if (!m_refresh.empty())
        invalidateWindows();
}

void skWindowContextWin32::processInteractive(bool dispatch)
{
    MSG msg;
    m_shouldDispatch = dispatch;

    while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) != 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    if (!m_refresh.empty())
        invalidateWindows();
}

void skWindowContextWin32::queueRefreshWindow(skWindowWin32* win)
{
    if (m_refresh.find(win) == m_refresh.npos)
        m_refresh.push_back(win);
}

void skWindowContextWin32::invalidateWindows()
{
    if (!m_refresh.empty())
    {
        WindowArray::Iterator it = m_refresh.iterator();
        while (it.hasMoreElements())
            it.getNext()->invalidate();

        m_refresh.resizeFast(0);
    }
}

void skWindowContextWin32::handleSize(skWindowWin32* window, SKuintPtr lParam) const
{
    window->sizedChanged(lParam);

    if (shouldDispatch())
        m_creator->dispatchEvent(SK_WIN_SIZE, window);
}

void skWindowContextWin32::handlePaint(skWindowWin32* window) const
{
    if (shouldDispatch())
    {
        window->validate();
        m_creator->dispatchEvent(SK_WIN_PAINT, window);
    }
    else
        window->validate();
}

void skWindowContextWin32::handleClose(skWindowWin32* window) const
{
    if (shouldDispatch())
        m_creator->dispatchEvent(SK_WIN_DESTROY, window);

    m_creator->destroy(window);
}

void skWindowContextWin32::handleMouse(skWindowWin32* window,
                                       SKuint32       message,
                                       SKuintPtr      wParam,
                                       SKuintPtr      lParam) const
{
    window->handleMouse(message, wParam, lParam);

    if (shouldDispatch())
    {
        switch (message)
        {
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_RBUTTONDOWN:
            m_creator->dispatchEvent(SK_MOUSE_PRESSED, window);
            break;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP:
        case WM_RBUTTONUP:
            m_creator->dispatchEvent(SK_MOUSE_RELEASED, window);
            break;
        case WM_MOUSEWHEEL:
            m_creator->dispatchEvent(SK_MOUSE_WHEEL, window);
            break;
        case WM_MOUSEMOVE:
            m_creator->dispatchEvent(SK_MOUSE_MOVED, window);
            break;
        default:
            break;
        }
    }
}

void skWindowContextWin32::handleKey(skWindowWin32* window,
                                     SKuint32       message,
                                     SKuintPtr      wParam) const
{
    window->handleKey(message, wParam);

    if (shouldDispatch())
    {
        switch (message)
        {
        case WM_SYSKEYUP:
        case WM_KEYUP:
            m_creator->dispatchEvent(SK_KEY_RELEASED, window);
            break;
        case WM_SYSKEYDOWN:
        case WM_KEYDOWN:
            m_creator->dispatchEvent(SK_KEY_PRESSED, window);
            break;
        default:
            break;
        }        
    }
}

SKintPtr skWindowContextWin32::handleProcedure(skWindowWin32*  window,
                                               const SKuint32  message,
                                               const SKuintPtr wParam,
                                               const SKuintPtr lParam) const
{
    switch (message)
    {
    case WM_ACTIVATE:
        if (wParam == TRUE)
            window->makeCurrent();
        return 0;
    case WM_SIZE:
        handleSize(window, lParam);
        return 0;
    case WM_SYSKEYUP:
    case WM_KEYUP:
    case WM_SYSKEYDOWN:
    case WM_KEYDOWN:
        handleKey(window, message, wParam);
        return 0;
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    case WM_MOUSEMOVE:
    case WM_MOUSEWHEEL:
        handleMouse(window, message, wParam, lParam);
        return 0;
    case WM_PAINT:
        handlePaint(window);
        return 0;
    case WM_CLOSE:
        handleClose(window);
        return 0;
    default:
        return ::DefWindowProc(window->m_hWnd, message, wParam, lParam);
    }
}
