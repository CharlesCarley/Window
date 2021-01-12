/*! \mainpage Window

Is a small cross platform window library for use with OpenGL.

This is still largely a work in progress.  

## Current state

+ Win32 Native
+ X11 Native
+ SDL Windows, Linux

## Goals

+ Should be able to load, create and manage at least one toplevel window.
+ Handle all user input.
+ Setup OpenGL automatically.

## Building

Building with CMake

```txt
mkdir build
cd build
cmake ..
```

Optional defines.

+ Window_WITH_SDL - Build with support for SDL. Default: OFF

### Usage

```cpp
#include "Window/skKeyboard.h"
#include "Window/skWindow.h"
#include "Window/skWindowHandler.h"
#include "Window/skWindowManager.h"

class Application : public skWindowHandler
{
private:
    skWindowManager* m_manager;

    void handle(const skEventType& event, skWindow* window) override
    {
        if (event == skEventType::SK_KEY_PRESSED)
        {
            if (window->getKeyboardRef().key == KC_ESC)
            {
                window->close();
            }
        }
    }

public:
    Application()
    {
        m_manager = new skWindowManager();
        m_manager->addHandler(this);
    }
    ~Application() override
    {
        delete m_manager;
    }

    void go()
    {
        skWindow* window = m_manager->create("Test Window", 800, 600, WM_WF_DEFAULT);
        window->show(true);

        m_manager->process();
    }
};

int main()
{
    Application app;
    app.go();
    return 0;
}
```
*/
