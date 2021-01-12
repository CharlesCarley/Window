#------------------------------------------------------------------------------
#   $Id: Wrap.py 662 2019-04-18 20:38:06Z Charlie $
#
#   Copyright (c) 2011 Charlie C.
#
#   Contributor(s): none yet.
#------------------------------------------------------------------------------
#  This software is provided 'as-is', without any express or implied
#  warranty. In no event will the authors be held liable for any damages
#  arising from the use of this software.
#
#  Permission is granted to anyone to use this software for any purpose,
#  including commercial applications, and to alter it and redistribute it
#  freely, subject to the following restrictions:
#
#  1. The origin of this software must not be misrepresented; you must not
#     claim that you wrote the original software. If you use this software
#     in a product, an acknowledgment in the product documentation would be
#     appreciated but is not required.
#  2. Altered source versions must be plainly marked as such, and must not be
#     misrepresented as being the original software.
#  3. This notice may not be removed or altered from any source distribution.
#------------------------------------------------------------------------------
import OpenGL3 as Code
import sys
CODE = Code.OpenGL


def saveBuffer(file, buf):
    f = open(file, "w", encoding='utf-8')
    f.write(buf)
    f.close()


TEMPL = """/*
-------------------------------------------------------------------------------
    $Id: Wrap.py 662 2019-04-18 20:38:06Z Charlie $

    Copyright (c) 2011 Charlie C.

    Contributor(s): none yet.

-------------------------------------------------------------------------------
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
#include "windows.h"
#define GL3_PROTOTYPES
#include "OpenGL3.h"


#define DO_TRACE 1
#if DO_TRACE
#include <stdio.h>

static int OpenGL3_TOTAL   = 0;
static int OpenGL3_MISSING = 0;


#define OpenGL3_InitSym(FP, T, DEST) \\
    FP= (T)wglGetProcAddress(DEST);\\
	if (FP)\\
	{logf("Loaded ==> %s\\n", DEST); OpenGL3_TOTAL += 1;}\\
	else\\
	{logf("Missing ==> %s\\n", DEST); OpenGL3_MISSING += 1;}

#else
#define OpenGL3_InitSym(FP, T, DEST) FP= (T)wglGetProcAddress(DEST);
#endif
$TYPEDEFS
int OpenGL3Init( void (*logf)(char *, ...) ) {
#if DO_TRACE
    OpenGL3_TOTAL= 0;
    OpenGL3_MISSING= 0;
#endif

$INITSYM
#if DO_TRACE
    logf( "\\tLoaded %i symbols.\\n", OpenGL3_TOTAL );
    logf( "\\tAPI is missing %i symbols.\\n", OpenGL3_MISSING );
#endif
    return 1;
}
"""


TYPEDEFS = ""
INITSYM  = ""
WRAPPERS = ""
TEST_TEMPLVOID = """    if (__alWrap$SYM != NULL) {
        __alWrap$SYM($PARAM_CALL);
    }
"""
TEST_TEMPLRET = """    if (__alWrap$SYM != NULL) {
        return __alWrap$SYM($PARAM_CALL);
    }
    return (($TYPE)0);
"""


def writeCode(API, code):
    global TYPEDEFS, INITSYM, WRAPPERS, TEST_TEMPLVOID, TEST_TEMPLRET

    for i in code:
        TYPEDEFS += "PFN" + i[1].upper() + "PROC __"+i[1]+" = NULL;\n"
        INITSYM += "\tOpenGL3_InitSym(__" + i[1] + ", PFN" + i[1].upper() + "PROC, \"" + i[1] + "\");\n"

        PARAM_LIST = i[2]
        PARAM_STR = ""
        PARAM_CALL= "";

        PARAM_SIZE = len(PARAM_LIST)
        I = 0;
        for PARAM in PARAM_LIST:
            J = 0;
            for ITEM in PARAM:
                PARAM_STR += " " + ITEM
                if J == 1:
                    PARAM_CALL += ' ' + ITEM;
                J+= 1
            if I < PARAM_SIZE-1:
                PARAM_STR += ","
                PARAM_CALL += ","
            else:
                PARAM_STR += " "
                PARAM_CALL += " "
            I+= 1
        WRAPPERS += "GLAPI " + i[0] + " GL_APIENTRY " + i[1] + "("+PARAM_STR+"){\n";
        WRAPTEMPL = "";

        if (i[0] == "void"):
            WRAPTEMPL = TEST_TEMPLVOID;
            WRAPTEMPL = WRAPTEMPL.replace("$SYM", i[1])
            WRAPTEMPL = WRAPTEMPL.replace("$PARAM_CALL", PARAM_CALL)
        else:
            WRAPTEMPL = TEST_TEMPLRET;
            WRAPTEMPL = WRAPTEMPL.replace("$TYPE",  i[0])
            WRAPTEMPL = WRAPTEMPL.replace("$SYM",   i[1])
            WRAPTEMPL = WRAPTEMPL.replace("$PARAM_CALL", PARAM_CALL)
        WRAPPERS += WRAPTEMPL;
        WRAPPERS+= "}\n"

writeCode("GLAPI", Code.OpenGL)
tmpl = TEMPL
tmpl = tmpl.replace("$TYPEDEFS",    TYPEDEFS)
tmpl = tmpl.replace("$INITSYM",     INITSYM)
tmpl = tmpl.replace("$WRAPPERS",    WRAPPERS)
saveBuffer("OpenGL3Wrap.c", tmpl)
