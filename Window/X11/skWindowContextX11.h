/*
-------------------------------------------------------------------------------
    Copyright (c) 2019 Charles Carley.

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
#ifndef _skWindowManagerContext_h_
#define _skWindowManagerContext_h_

#include <X11/Xlib.h>
#include "Utils/skString.h"
#include "Window/X11/skWindowStubs.h"
#include "Window/skWindowContext.h"
#include "Window/skWindowTypes.h"

class skWindowX11;

class skWindowContextX11 final : public skWindowContext
{
private:
    Display*         m_display{};
    skWindowManager* m_creator;
    Atom             m_deleteAtom;

    friend class skWindowX11;

    Display* getXDisplay(void) const
    {
        return m_display;
    }

    skWindow* extractWindowFromEvent(XEvent& evt) const;

    void processMessage(skWindow* win, XEvent& evt) const;
    void handleConfigure(XEvent& evt, skWindowX11* win) const;
    void handleExpose(XEvent& evt, skWindowX11* win) const;
    void handleDestroy(XEvent& evt, skWindowX11* win) const;
    void handleMotion(XEvent& evt, skWindowX11* win) const;
    void handleButton(XEvent& evt, skWindowX11* win) const;
    void handleKey(XEvent& evt, skWindowX11* win) const;
    void handleClient(XEvent& evt, skWindowX11* win) const;



public:
    explicit skWindowContextX11(skWindowManager* owner);
    virtual ~skWindowContextX11();

    void initialize(void) override;
    void processInteractive(bool dispatch = false) override;
    void process(void) override;
};

#endif  //_skWindowManagerContext_h_
