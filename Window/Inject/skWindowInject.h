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
#ifndef _skWindowInject_h_
#define _skWindowInject_h_

#include "Window/skWindow.h"
#include "Window/skWindowTypes.h"

class skWindowInject: public skWindow
{
public:
    skWindowInject(skWindowManager* creator);
    ~skWindowInject() override;

    void create(const char* title, SKuint32 w, SKuint32 h, SKuint32 flags) override;

    void refresh(void) override;

    void show(bool v) override;

    void flush(void) override;

    void capture(void) override;

    SKsize getWindowHandle(void) override
    {
        return 0;
    }
};

#endif  //_skWindowInject_h_
