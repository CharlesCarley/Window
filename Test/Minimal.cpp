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
