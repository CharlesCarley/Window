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
#include "Utils/skPlatformHeaders.h"
#include "Window/skKeyboard.h"
#include "Window/skMouse.h"
#include "Window/skWindowContext.h"
#include "Window/skWindowManager.h"
#include "Window/skWindowTypes.h"
#include "skWindowContextWin32.h"

HGLRC _wglCreateContext(HDC dc);
void  _wglDeleteContext(HGLRC rc);
void  _wglMakeCurrent(HDC dc, HGLRC rc);

skWindowWin32::skWindowWin32(skWindowManager* creator) :
    skWindow(creator),
    m_pz(0),
    m_lz(0),
    m_lx(0),
    m_ly(0),
    m_init(false),
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
        _wglDeleteContext(m_glRC);

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
        if (flags & WM_WF_CAPTURE)
            ShowCursor(FALSE);

        setupOpenGL();

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
                m_creator->dispatchEvent(skEventType::SK_WIN_SHOWN, this);
            else
                m_creator->dispatchEvent(skEventType::SK_WIN_HIDDEN, this);
        }
    }
}

void skWindowWin32::flush(void)
{
    if (m_hWnd && m_dc)
        SwapBuffers(m_dc);
}

void skWindowWin32::capture(void)
{
    RECT  rect;
    POINT pos;
    GetCursorPos(&pos);
    GetWindowRect(m_hWnd, &rect);

    pos.x -= rect.left;
    pos.y -= rect.top;
    m_mouse->x.abs = pos.x;
    m_mouse->y.abs = pos.y;

    if (!m_init)
    {
        m_init = true;
        m_lx   = pos.x;
        m_ly   = pos.y;
        m_lz   = 0;
    }

    m_mouse->x.rel = pos.x - m_lx;
    m_mouse->y.rel = pos.y - m_ly;

    m_mouse->z.rel = 0;
    if (m_pz != 0)
    {
        if (m_pz > 0)
            m_lz += 1;
        else
            m_lz -= 1;
        m_mouse->z.rel = m_pz > 0 ? 1 : -1;
        m_mouse->z.abs = m_lz;

        m_pz = 0;
    }
    m_lx = (rect.left + rect.right) / 2;
    m_ly = (rect.top + rect.bottom) / 2;
    SetCursorPos(m_lx, m_ly);
    m_lx -= rect.left;
    m_ly -= rect.top;
}

void skWindowWin32::setupOpenGL(void)
{
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
    m_glRC = _wglCreateContext(m_dc);

    makeCurrent();
    skLoadOpenGL();
}


void skWindowWin32::makeCurrent() const
{
    if (m_glRC)
        _wglMakeCurrent(m_dc, m_glRC);
}


void skWindowWin32::handleMouse(SKuint32 msg, SKuintPtr wParam, SKuintPtr lParam)
{
    switch (msg)
    {
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    {
        const bool down = msg == WM_LBUTTONDOWN ||
                          msg == WM_MBUTTONDOWN ||
                          msg == WM_RBUTTONDOWN;
        SKmouseTable &table = m_mouse->getTable();


        if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP)
            table[MBT_L] = down;
        else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP)
            table[MBT_M] = down;
        else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP)
            table[MBT_R] = down;

        if (getContext()->shouldDispatch())
        {
            if (down)
                m_creator->dispatchEvent(skEventType::SK_MOUSE_PRESSED, this);
            else
                m_creator->dispatchEvent(skEventType::SK_MOUSE_RELEASED, this);
        }
        break;
    }
    case WM_MOUSEMOVE:
        m_mouse->x.abs = LOWORD(lParam);
        m_mouse->y.abs = HIWORD(lParam);

        if (!m_init)
        {
            m_init = true;
            m_lx   = m_mouse->x.abs;
            m_ly   = m_mouse->y.abs;
        }
        m_mouse->x.rel = m_mouse->x.abs - m_lx;
        m_mouse->y.rel = m_mouse->y.abs - m_ly;

        m_lx = m_mouse->x.abs;
        m_ly = m_mouse->y.abs;

        if (m_creator->getContext()->shouldDispatch())
            m_creator->dispatchEvent(skEventType::SK_MOUSE_MOVED, this);

        break;
    case WM_MOUSEWHEEL:

        m_pz = GET_WHEEL_DELTA_WPARAM(wParam) > 0 ? 120 : -120;

        m_mouse->z.abs = m_pz;
        m_mouse->z.rel = m_pz > 0 ? 1 : -1;

        if (m_creator->getContext()->shouldDispatch())
            m_creator->dispatchEvent(skEventType::SK_MOUSE_WHEEL, this);
        break;
    default:
        break;
    }
}

void skWindowWin32::handleKey(SKuint32 msg, SKuintPtr wParam)
{
    const SKint32 sc = (int)getScanCode(wParam);
    if (sc <= KC_NONE || sc >= KC_MAX)
        return;

    const bool keyRel = msg == WM_SYSKEYUP || msg == WM_KEYUP;

    SKkeyTable& keys = m_keyboard->getTable();

    if (getContext()->shouldDispatch())
    {
        if (keyRel)
        {
            // indicate that it was pressed
            keys[sc] = WM_PRESSED;
            m_creator->dispatchEvent(skEventType::SK_KEY_RELEASED, this);

            keys[sc] = WM_RELEASED;
        }
        else
        {
            keys[sc] = WM_PRESSED;
            m_creator->dispatchEvent(skEventType::SK_KEY_PRESSED, this);
        }
    }
    else
        keys[sc] = keyRel ? WM_RELEASED : WM_PRESSED;
}

void skWindowWin32::sizedChanged(SKuintPtr lParam)
{
    m_width  = LOWORD(lParam);
    m_height = HIWORD(lParam);
}

int skWindowWin32::getScanCode(SKuintPtr wParam)
{
    if (wParam >= 'A' && wParam <= 'Z')
    {
        wParam -= 'A';
        return KC_A + (int)wParam;
    }

    if (wParam >= '0' && wParam <= '9')
    {
        wParam -= '0';
        return KC_0 + (int)wParam;
    }

    switch (wParam)
    {
    case VK_NUMPAD0:
        return KC_PAD0;
    case VK_NUMPAD1:
        return KC_PAD1;
    case VK_NUMPAD2:
        return KC_PAD2;
    case VK_NUMPAD3:
        return KC_PAD3;
    case VK_NUMPAD4:
        return KC_PAD4;
    case VK_NUMPAD5:
        return KC_PAD5;
    case VK_NUMPAD6:
        return KC_PAD6;
    case VK_NUMPAD7:
        return KC_PAD7;
    case VK_NUMPAD8:
        return KC_PAD8;
    case VK_NUMPAD9:
        return KC_PAD9;
    case VK_F1:
        return KC_F1;
    case VK_F2:
        return KC_F2;
    case VK_F3:
        return KC_F3;
    case VK_F4:
        return KC_F4;
    case VK_F5:
        return KC_F5;
    case VK_F6:
        return KC_F6;
    case VK_F7:
        return KC_F7;
    case VK_F8:
        return KC_F8;
    case VK_F9:
        return KC_F9;
    case VK_F10:
        return KC_F10;
    case VK_F11:
        return KC_F11;
    case VK_F12:
        return KC_F12;
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
    return KC_NONE;
}

#ifndef SID_GLES
HGLRC _wglCreateContext(HDC dc)
{
    return wglCreateContext(dc);
}

void _wglDeleteContext(HGLRC rc)
{
    wglDeleteContext(rc);
}

void _wglMakeCurrent(HDC dc, HGLRC rc)
{
    wglMakeCurrent(dc, rc);
}

#else

HGLRC _wglCreateContext(HDC dc)
{
    return NULL;
}

void _wglDeleteContext(HGLRC rc)
{
}

void _wglMakeCurrent(HDC dc, HGLRC rc)
{
}
#endif
