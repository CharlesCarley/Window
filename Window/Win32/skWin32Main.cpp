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
#include "Utils/Config/skConfig.h"
#include "Utils/skDebugger.h"

#if SK_COMPILER == SK_COMPILER_MSVC

#define _CRTDBG_MAP_ALLOC 1

#include <crtdbg.h>
#include <stdio.h>
#include <stdlib.h>

int CRT_ReportHook(int type, char* msg, int* ret)
{
    fprintf(stderr, "%s", msg);
    return 1;
}

void CRT_TestMemory()
{
    // enable reporting and keep any flags that are present.
    int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
    flag |= _CRTDBG_LEAK_CHECK_DF;

    // ignore internal CRT memory allocations
    flag &= ~_CRTDBG_CHECK_CRT_DF;

    _CrtSetDbgFlag(flag);
    _CrtSetReportHook(CRT_ReportHook);
}

void CRT_Dump(const char* f)
{
    freopen(f, "w", stderr);

    if (_CrtDumpMemoryLeaks() == 0)
        fprintf(stderr, "No memory leaks were found using _CrtDumpMemoryLeaks\n");
    _CrtSetReportHook(nullptr);
}

#define TestMemory CRT_TestMemory();
#define DumpMem(f) CRT_Dump(f);

#else
#define TestMemory
#define DumpMem(f)
#endif

#include "Utils/skFixedString.h"
#include "Utils/skPlatformHeaders.h"
#include "Utils/skString.h"

class skWin32CommandLine
{
public:
    skWin32CommandLine() :
        argc(0),
        argv(nullptr)
    {
    }

    ~skWin32CommandLine()
    {
    }

    int    argc;
    char** argv;

private:
    skArray<skString>    m_memory;
    skArray<const char*> m_command;

    void split(LPSTR args, SKsize nCmd)
    {
        const SKsize s = skStringUtils::length(args);
        if (s > 0)
        {
            skFixedString<272> tstr;
            for (SKsize i = 0; i < s; ++i)
            {
                if (args[i] == ' ')
                {
                    m_memory.push_back(tstr.c_str());
                    tstr.clear();
                }
                else
                    tstr.push_back(args[i]);
            }
            if (!tstr.empty())
                m_memory.push_back(tstr.c_str());
        }
    }

public:
    bool load(LPSTR args, SKsize nCmd)
    {
        skFixedString<272> fname;
        const DWORD size = GetModuleFileName(GetModuleHandle(nullptr),
                                             fname.ptr(),
                                             fname.capacity());
        if (size > 0)
        {
            fname.resize((SKuint16)size);

            m_memory.push_back(skString(fname.c_str()));
            split(args, nCmd);

            skArray<skString>::Iterator it = m_memory.iterator();
            while (it.hasMoreElements())
                m_command.push_back(it.getNext().c_str());

            argc = (int)m_command.size();
            argv = (char**)m_command.ptr();
            return true;
        }
        return false;
    }
};

extern int main(int argc, char** argv);

int WINAPI WinMain(_In_ HINSTANCE     hInst,
                   _In_opt_ HINSTANCE hPrevInst,
                   _In_ LPSTR         lpCmdLine,
                   _In_ int           nShowCmd)
{
    TestMemory;
    int rc = -1;

    { // To make sure everything goes out of scope

        skWin32CommandLine cmd;
        if (cmd.load(lpCmdLine, nShowCmd))
            rc = main(cmd.argc, cmd.argv);
        else
            fprintf(stderr, "Failed to extract command line parameters.\n");
    } 

    DumpMem("memdump.log");
    return rc;
}
