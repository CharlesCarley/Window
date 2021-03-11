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

#if SK_COMPILER == SK_COMPILER_MSVC && defined(_DEBUG)

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

int CRT_Dump(const char* f)
{
    freopen(f, "w", stderr);

    int rc = 1;
    if (_CrtDumpMemoryLeaks() == 0)
    {
        fprintf(stderr, "No memory leaks were found using _CrtDumpMemoryLeaks\n");
        rc = 0;
    }
    _CrtSetReportHook(nullptr);
    return rc;
}

#define TestMemory CRT_TestMemory()
#define DumpMem(f) CRT_Dump(f)

#else
#define TestMemory
#define DumpMem(f) 0
#endif

#include "Utils/skFixedString.h"
#include "Utils/skPlatformHeaders.h"
#include "Utils/skString.h"

class skWin32CommandLine
{
public:
    typedef skFixedString<272> CLString;

    skWin32CommandLine() :
        m_argc(0),
        m_argv(nullptr)
    {
    }

    ~skWin32CommandLine() = default;

    int    m_argc;
    char** m_argv;

private:
    skArray<skString>    m_memory;
    skArray<const char*> m_command;

    void split(LPSTR args, SKsize nCmd)
    {
        const SKsize s = skChar::length(args);
        if (s > 0)
        {
            CLString maxPath;
            for (SKsize i = 0; i < s; ++i)
            {
                if (args[i] == ' ')
                {
                    m_memory.push_back(maxPath.c_str());
                    maxPath.clear();
                }
                else
                    maxPath.push_back(args[i]);
            }
            if (!maxPath.empty())
                m_memory.push_back(maxPath.c_str());
        }
    }

public:
    bool load(LPSTR args, SKsize nCmd)
    {
        CLString    fileName;
        const DWORD size = GetModuleFileName(GetModuleHandle(nullptr),
                                             fileName.ptr(),
                                             CLString::capacity());
        if (size > 0)
        {
            fileName.resize((SKuint16)size);

            m_memory.push_back(skString(fileName.c_str()));
            split(args, nCmd);

            skArray<skString>::Iterator it = m_memory.iterator();
            while (it.hasMoreElements())
                m_command.push_back(it.getNext().c_str());

            m_argc = (int)m_command.size();
            m_argv = (char**)m_command.ptr();
            return true;
        }
        return false;
    }
};

extern int main(int argc, char** argv);

int WINAPI WinMain(_In_       HINSTANCE,
                   _In_opt_   HINSTANCE,
                   _In_ LPSTR lpCmdLine,
                   _In_ int   nShowCmd)
{
    TestMemory;
    int rc = -1;
    {  // To make sure everything goes out of scope

        skWin32CommandLine cmd;
        if (cmd.load(lpCmdLine, nShowCmd))
            rc = main(cmd.m_argc, cmd.m_argv);
        else
            fprintf(stderr, "Failed to extract command line parameters.\n");
    }
    if (DumpMem("memdump.log") != 0)
        return 1;
    return rc;
}
