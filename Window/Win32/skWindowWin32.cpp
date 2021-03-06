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
#include "Window/Win32/skWindowWin32.h"
#include "OpenGL/skOpenGL.h"
#include "Utils/skDisableWarnings.h"
#include "Utils/skLogger.h"
#include "Utils/skPlatformHeaders.h"
#include "Window/skWindowContext.h"
#include "Window/skWindowManager.h"
#include "Window/skWindowTypes.h"
#include "skWindowContextWin32.h"

#define MOUSE_STATE(m) ((m) == WM_LBUTTONDOWN || (m) == WM_MBUTTONDOWN || \
                        (m) == WM_RBUTTONDOWN)                            \
                           ? WM_PRESSED                                   \
                           : WM_RELEASED

#define KEY_STATE(m) ((m) == WM_SYSKEYDOWN || (m) == WM_KEYDOWN) \
                         ? WM_PRESSED                            \
                         : WM_RELEASED

skWindowWin32::skWindowWin32(skWindowManager* creator) :
    skWindow(creator),
    m_hWnd(nullptr),
    m_dc(nullptr),
    m_glRC(nullptr)
{
}

skWindowWin32::~skWindowWin32()
{
    if (m_hWnd)
        SetWindowLongPtr(m_hWnd, GWL_USER, NULL);

    if (m_glRC)
        wglDeleteContext(m_glRC);

    if (m_hWnd)
        DestroyWindow(m_hWnd);
}

void skWindowWin32::create(const char* title, SKuint32 width, SKuint32 height, SKuint32 flags)
{
    if (m_hWnd != nullptr)
        return;

    DWORD winStyle = WS_OVERLAPPEDWINDOW;
    if (flags & WM_WF_DIALOG)
        winStyle = WS_CAPTION | WS_SYSMENU;
    if (flags & WM_WF_MAXIMIZE)
        winStyle |= WS_MAXIMIZE;

    SKuint32 xPos = 0, yPos = 0;

    if (flags & WM_WF_CENTER)
    {
        const int scx = GetSystemMetrics(SM_CXSCREEN);
        const int scy = GetSystemMetrics(SM_CYSCREEN);
        const int lft = (scx - (int)width) >> 1;
        const int top = (scy - (int)height) >> 1;

        xPos = skClamp(lft, 0, scx - 10);
        yPos = skClamp(top, 0, scy - 10);
    }

    m_width  = width;
    m_height = height;

    m_hWnd = ::CreateWindow(SK_WINDOW_CLASS_NAME,
                            title,
                            winStyle,
                            xPos,
                            yPos,
                            width,
                            height,
                            nullptr,
                            nullptr,
                            ::GetModuleHandle(NULL),
                            nullptr);

    if (m_hWnd != nullptr)
    {
        ::SetWindowLongPtr(m_hWnd, GWL_USER, (SKuintPtr)this);

        UpdateWindow(m_hWnd);

        m_dc = GetDC(m_hWnd);
        if (!m_dc)
            skLogd(LD_ERROR, "Failed to get the device context\n");

        setupOpenGL();

        // Disabled, this use to capture the mouse
        // and center it in the screen.
        //
        // if (flags & WM_WF_CAPTURE)
        //    ShowCursor(FALSE);

        if (flags & WM_WF_SHOWN)
            show(true);
    }
}

void skWindowWin32::refresh(void)
{
    if (m_hWnd && m_dc)
    {
        skWindowContextWin32* context = (skWindowContextWin32*)getContext();
        if (context)
            context->queueRefreshWindow(this);
    }
}

void skWindowWin32::invalidate() const
{
    if (m_hWnd && m_dc)
        InvalidateRect(m_hWnd, nullptr, FALSE);
}

void skWindowWin32::validate() const
{
    if (m_hWnd)
        ValidateRect(m_hWnd, nullptr);
}

void skWindowWin32::show(bool doShow)
{
    if (m_hWnd)
    {
        ShowWindow(m_hWnd, doShow ? SW_SHOW : SW_HIDE);

        if (getContext()->shouldDispatch())
        {
            if (doShow)
                m_creator->dispatchEvent(SK_WIN_SHOWN, this);
            else
                m_creator->dispatchEvent(SK_WIN_HIDDEN, this);
        }
    }
}

void skWindowWin32::flush(void)
{
    if (m_hWnd && m_dc)
        SwapBuffers(m_dc);
}

void skWindowWin32::setupOpenGL(void)
{
    if (!m_dc)
    {
        skLogd(LD_ERROR, "Invalid device context\n");
        return;
    }

    PIXELFORMATDESCRIPTOR pixelFormat = {};

    const int bpp = GetDeviceCaps(m_dc, BITSPIXEL);

    pixelFormat.nSize        = sizeof(PIXELFORMATDESCRIPTOR);
    pixelFormat.nVersion     = 1;
    pixelFormat.dwFlags      = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER;
    pixelFormat.iPixelType   = PFD_TYPE_RGBA;
    pixelFormat.cColorBits   = bpp > 16 ? 24 : (BYTE)bpp;
    pixelFormat.cAlphaBits   = bpp > 16 ? 8 : 0;
    pixelFormat.cDepthBits   = 24;
    pixelFormat.cStencilBits = 8;

    const int iPixelFormat = ChoosePixelFormat(m_dc, &pixelFormat);
    if (!iPixelFormat)
        return;

    if (!SetPixelFormat(m_dc, iPixelFormat, &pixelFormat))
        return;

    DescribePixelFormat(m_dc, iPixelFormat, sizeof pixelFormat, &pixelFormat);
    m_glRC = wglCreateContext(m_dc);

    makeCurrent();
    skLoadOpenGL();
}

void skWindowWin32::makeCurrent() const
{
    if (m_glRC && m_dc)
        wglMakeCurrent(m_dc, m_glRC);
}

void skWindowWin32::handleMouse(const SKuint32&  message,
                                const SKuintPtr& wParam,
                                const SKuintPtr& lParam) const
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    {
        __notifyMotion(LOWORD(lParam), HIWORD(lParam));

        SKint32 button;
        if (message == WM_LBUTTONDOWN || message == WM_LBUTTONUP)
            button = MBT_L;
        else if (message == WM_MBUTTONDOWN || message == WM_MBUTTONUP)
            button = MBT_M;
        else
            button = MBT_R;

        __notifyButton(button, MOUSE_STATE(message));
        break;
    }
    case WM_MOUSEMOVE:
        __notifyMotion(LOWORD(lParam), HIWORD(lParam));
        break;
    case WM_MOUSEWHEEL:
        __notifyWheel(GET_WHEEL_DELTA_WPARAM(wParam));
        break;
    default:
        break;
    }
}

void skWindowWin32::handleKey(const SKuint32& message, const SKuintPtr& wParam) const
{
    const SKint32 key = (int)getScanCode(wParam);
    __notifyKey(key, KEY_STATE(message));
}

void skWindowWin32::sizedChanged(SKuintPtr lParam)
{
    m_width  = LOWORD(lParam);
    m_height = HIWORD(lParam);
}

SKint32 skWindowWin32::getScanCode(const SKuintPtr& wParam)
{
    if (wParam >= 'A' && wParam <= 'Z')
        return KC_A + ((int)wParam - 'A');
    if (wParam >= '0' && wParam <= '9')
        return KC_0 + ((int)wParam - '0');
    if (wParam >= VK_F1 && wParam <= VK_F12)
        return KC_F1 + ((int)wParam - VK_F1);
    if (wParam >= VK_NUMPAD0 && wParam <= VK_NUMPAD9)
        return KC_PAD0 + ((int)wParam - VK_NUMPAD0);

    switch (wParam)
    {
    case VK_RCONTROL:
        return KC_RCTRL;
    case VK_LCONTROL:
        return KC_LCTRL;
    case VK_RMENU:
        return KC_RALT;
    case VK_LMENU:
        return KC_LALT;
    case VK_SHIFT:
        return KC_SHIFT;
    case VK_CONTROL:
        return KC_CTRL;
    case VK_MENU:
        return KC_ALT;
    case VK_RSHIFT:
        return KC_RSHIFT;
    case VK_LSHIFT:
        return KC_LSHIFT;
    case VK_ESCAPE:
        return KC_ESC;
    case VK_CAPITAL:
        return KC_CAPSLOCK;
    case VK_TAB:
        return KC_TAB;
    case VK_RETURN:
        return KC_RET;
    case VK_SPACE:
        return KC_SPACE;
    case VK_BACK:
        return KC_BACKSPACE;
    case VK_DELETE:
        return KC_DEL;
    case VK_LEFT:
        return KC_LEFT;
    case VK_UP:
        return KC_UP;
    case VK_RIGHT:
        return KC_RIGHT;
    case VK_DOWN:
        return KC_DOWN;
    case VK_DIVIDE:
        return KC_PAD_DIV;
    case VK_MULTIPLY:
        return KC_PAD_MUL;
    case VK_ADD:
        return KC_PAD_ADD;
    case VK_SUBTRACT:
        return KC_PAD_SUB;
    case VK_OEM_PERIOD:
        return KC_PERIOD;
    case VK_DECIMAL:
        return KC_PAD_PERIOD;
    default:
        break;
    }
    return KC_MAX;
}
