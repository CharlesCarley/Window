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
#include "Utils/skLogger.h"
#include "Window/OpenGL/skOpenGL.h"
#include "Window/skKeyboard.h"
#include "Window/skMouse.h"
#include "Window/skWindow.h"
#include "Window/skWindowHandler.h"
#include "Window/skWindowManager.h"

class Application : public skWindowHandler
{
private:
    skWindowManager* m_manager;
    skWindow*        m_window;
    float            m_val;

public:
    Application() :
        m_manager(nullptr),
        m_window(nullptr),
        m_val(0)
    {
    }

    ~Application() override
    {
        delete m_manager;
        m_manager = nullptr;
    }

    static void logEvent(const skEventType& event, skWindow* window)
    {
        switch (event)
        {
        case skEventType::SK_WIN_DESTROY:
            skLogf(LD_INFO, "SK_WIN_DESTROY\n");
            break;
        case skEventType::SK_WIN_PAINT:
            skLogf(LD_INFO, "SK_WIN_PAINT\n");
            break;
        case skEventType::SK_MOUSE_MOVED:
            skLogf(LD_INFO, "SK_MOUSE_MOVED\n");
            skLogf(LD_WARN, " Absolute (%d, %d)\n", (int)window->getMouseRef().x.abs, (int)window->getMouseRef().y.abs);
            skLogf(LD_WARN, " Relative (%d, %d)\n", (int)window->getMouseRef().x.rel, (int)window->getMouseRef().y.rel);
            break;
        case skEventType::SK_WIN_SIZE:
            skLogf(LD_INFO, "SK_WIN_SIZE (%d, %d)\n", (int)window->getWidth(), (int)window->getHeight());
            break;
        case skEventType::SK_WIN_EVT_UNKNOWN:
            break;
        case skEventType::SK_KEY_PRESSED:
            skLogf(LD_INFO, "SK_KEY_PRESSED\n");
            break;
        case skEventType::SK_KEY_RELEASED:
            skLogf(LD_INFO, "SK_KEY_RELEASED\n");
            break;
        case skEventType::SK_MOUSE_PRESSED:
            skLogf(LD_INFO, "SK_MOUSE_CLICKED\n");
            break;
        case skEventType::SK_MOUSE_RELEASED:
            skLogf(LD_INFO, "SK_MOUSE_RELEASED\n");
            break;
        case skEventType::SK_MOUSE_WHEEL:
            skLogf(LD_INFO, "SK_MOUSE_WHEEL\n");
            skLogf(LD_WARN, " Absolute (%d)\n", (int)window->getMouseRef().z.abs);
            skLogf(LD_WARN, " Relative (%d)\n", (int)window->getMouseRef().z.rel);
            break;
        case skEventType::SK_WIN_SHOWN:
            skLogf(LD_INFO, "SK_WIN_SHOWN\n");
            break;
        case skEventType::SK_WIN_HIDDEN:
            skLogf(LD_INFO, "SK_WIN_HIDDEN\n");
            break;
        }
    }

    void handle(const skEventType& event, skWindow* window) override
    {
        logEvent(event, window);
        if (event == skEventType::SK_WIN_PAINT)
        {
            glClearColor(m_val, m_val, m_val, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, window->getWidth(), window->getHeight());

            m_val += 0.01f;
            if (m_val > 1)
                m_val = 0;

            window->flush();
        }
        else if (event == skEventType::SK_KEY_PRESSED)
        {
            if (window->getKeyboardRef().isKeyDown(KC_Q) && window->getKeyboardRef().isKeyDown(KC_CTRL))
                window->close();

            if (window->getKeyboardRef().isKeyDown(KC_R))
                window->refresh();
        }
    }

    void constantLoop() const
    {
        float v = 0;
        while (m_manager->processInteractive())
        {
            glClearColor(v, v, v, 1);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glViewport(0, 0, m_window->getWidth(), m_window->getHeight());

            m_window->flush();

            v += 0.01f;
            if (v > 1)
                v = 0;
        }
    }

    void testDestroyAll()
    {
        for (int i = 0; i < 6; ++i)
            m_manager->create("Test", 800, 600, WM_WF_DIALOG | WM_WF_SHOWN);
        m_manager->processInteractive();
        m_manager->destroyAll();
    }

    int run()
    {
        m_manager = new skWindowManager(skContextType::WM_CTX_SDL);
        m_manager->addHandler(this);

        m_window = m_manager->create("Test",
                                     800,
                                     600,
                                     WM_WF_CENTER | WM_WF_DIALOG | WM_WF_SHOWN);
        if (m_window == nullptr)
            return 1;

        m_manager->process();
        return 0;
    }
};

int main(int, char**)
{
    skLogger log;
    log.setFlags(LF_STDOUT);

    Application app;
    return app.run();
}
