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
#include "skOpenGL.h"
#include "Utils/skLogger.h"
#include "Utils/skPlatformHeaders.h"
#include "Utils/skFixedString.h"

#if SK_PLATFORM == SK_PLATFORM_WIN32
HMODULE opengl = 0;

void* WIN32_getProcAddress(HMODULE mod, char* str)
{
    // hack for loading gl profile 1.1
    // apparently it was made inaccessible
    // from WGL

    void* sym =  GetProcAddress(opengl, str);
    if (!sym)
        sym = wglGetProcAddress(str);
    return sym;
}

#elif SK_PLATFORM == SK_PLATFORM_LINUX
#include <dlfcn.h>
void* opengl = 0;

#endif



/*
========================================================
skGetOpenGL_Symbol
========================================================
*/
#if SK_PLATFORM == SK_PLATFORM_WIN32
#define skGetOpenGL_Symbol(X, Y) ((Y = (X)WIN32_getProcAddress(opengl, #Y)) != 0)
#elif SK_PLATFORM == SK_PLATFORM_LINUX
#define skGetOpenGL_Symbol(X, Y) ((Y = (X)dlsym(opengl, #Y ) ) != 0)
#endif

/*
========================================================
                       OpenGL_1_1
========================================================
*/
PFNGLDRAWARRAYSPROC           glDrawArrays           = 0;
PFNGLDRAWELEMENTSPROC         glDrawElements         = 0;
PFNGLGETPOINTERVPROC          glGetPointerv          = 0;
PFNGLPOLYGONOFFSETPROC        glPolygonOffset        = 0;
PFNGLCOPYTEXIMAGE1DPROC       glCopyTexImage1D       = 0;
PFNGLCOPYTEXIMAGE2DPROC       glCopyTexImage2D       = 0;
PFNGLCOPYTEXSUBIMAGE1DPROC    glCopyTexSubImage1D    = 0;
PFNGLCOPYTEXSUBIMAGE2DPROC    glCopyTexSubImage2D    = 0;
PFNGLTEXSUBIMAGE1DPROC        glTexSubImage1D        = 0;
PFNGLTEXSUBIMAGE2DPROC        glTexSubImage2D        = 0;
PFNGLBINDTEXTUREPROC          glBindTexture          = 0;
PFNGLDELETETEXTURESPROC       glDeleteTextures       = 0;
PFNGLGENTEXTURESPROC          glGenTextures          = 0;
PFNGLISTEXTUREPROC            glIsTexture            = 0;


bool skLoadOpenGL_1_1(void)
{



    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLDRAWARRAYSPROC,           glDrawArrays)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLDRAWELEMENTSPROC,         glDrawElements)         || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETPOINTERVPROC,          glGetPointerv)          || rval;
    rval = skGetOpenGL_Symbol(PFNGLPOLYGONOFFSETPROC,        glPolygonOffset)        || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOPYTEXIMAGE1DPROC,       glCopyTexImage1D)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOPYTEXIMAGE2DPROC,       glCopyTexImage2D)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOPYTEXSUBIMAGE1DPROC,    glCopyTexSubImage1D)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOPYTEXSUBIMAGE2DPROC,    glCopyTexSubImage2D)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLTEXSUBIMAGE1DPROC,        glTexSubImage1D)        || rval;
    rval = skGetOpenGL_Symbol(PFNGLTEXSUBIMAGE2DPROC,        glTexSubImage2D)        || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDTEXTUREPROC,          glBindTexture)          || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETETEXTURESPROC,       glDeleteTextures)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLGENTEXTURESPROC,          glGenTextures)          || rval;
    rval = skGetOpenGL_Symbol(PFNGLISTEXTUREPROC,            glIsTexture)            || rval;
    return rval;
}


/*
========================================================
                       OpenGL_1_2
========================================================
*/
PFNGLBLENDCOLORPROC           glBlendColor           = 0;
PFNGLBLENDEQUATIONPROC        glBlendEquation        = 0;
PFNGLDRAWRANGEELEMENTSPROC    glDrawRangeElements    = 0;
PFNGLTEXIMAGE3DPROC           glTexImage3D           = 0;
PFNGLTEXSUBIMAGE3DPROC        glTexSubImage3D        = 0;
PFNGLCOPYTEXSUBIMAGE3DPROC    glCopyTexSubImage3D    = 0;


bool skLoadOpenGL_1_2(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLBLENDCOLORPROC,           glBlendColor)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLBLENDEQUATIONPROC,        glBlendEquation)        || rval;
    rval = skGetOpenGL_Symbol(PFNGLDRAWRANGEELEMENTSPROC,    glDrawRangeElements)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLTEXIMAGE3DPROC,           glTexImage3D)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLTEXSUBIMAGE3DPROC,        glTexSubImage3D)        || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOPYTEXSUBIMAGE3DPROC,    glCopyTexSubImage3D)    || rval;
    return rval;
}

/*
========================================================
                       OpenGL_1_3
========================================================
*/
PFNGLACTIVETEXTUREPROC              glActiveTexture              = 0;
PFNGLSAMPLECOVERAGEPROC             glSampleCoverage             = 0;
PFNGLCOMPRESSEDTEXIMAGE3DPROC       glCompressedTexImage3D       = 0;
PFNGLCOMPRESSEDTEXIMAGE2DPROC       glCompressedTexImage2D       = 0;
PFNGLCOMPRESSEDTEXIMAGE1DPROC       glCompressedTexImage1D       = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC    glCompressedTexSubImage3D    = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC    glCompressedTexSubImage2D    = 0;
PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC    glCompressedTexSubImage1D    = 0;
PFNGLGETCOMPRESSEDTEXIMAGEPROC      glGetCompressedTexImage      = 0;


bool skLoadOpenGL_1_3(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLACTIVETEXTUREPROC,              glActiveTexture)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLSAMPLECOVERAGEPROC,             glSampleCoverage)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOMPRESSEDTEXIMAGE3DPROC,       glCompressedTexImage3D)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOMPRESSEDTEXIMAGE2DPROC,       glCompressedTexImage2D)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOMPRESSEDTEXIMAGE1DPROC,       glCompressedTexImage1D)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC,    glCompressedTexSubImage3D)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC,    glCompressedTexSubImage2D)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC,    glCompressedTexSubImage1D)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETCOMPRESSEDTEXIMAGEPROC,      glGetCompressedTexImage)      || rval;
    return rval;
}


/*
========================================================
                       OpenGL_1_4
========================================================
*/
PFNGLBLENDFUNCSEPARATEPROC    glBlendFuncSeparate    = 0;
PFNGLMULTIDRAWARRAYSPROC      glMultiDrawArrays      = 0;
PFNGLMULTIDRAWELEMENTSPROC    glMultiDrawElements    = 0;
PFNGLPOINTPARAMETERFPROC      glPointParameterf      = 0;
PFNGLPOINTPARAMETERFVPROC     glPointParameterfv     = 0;
PFNGLPOINTPARAMETERIPROC      glPointParameteri      = 0;
PFNGLPOINTPARAMETERIVPROC     glPointParameteriv     = 0;


bool skLoadOpenGL_1_4(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLBLENDFUNCSEPARATEPROC,    glBlendFuncSeparate)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLMULTIDRAWARRAYSPROC,      glMultiDrawArrays)      || rval;
    rval = skGetOpenGL_Symbol(PFNGLMULTIDRAWELEMENTSPROC,    glMultiDrawElements)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLPOINTPARAMETERFPROC,      glPointParameterf)      || rval;
    rval = skGetOpenGL_Symbol(PFNGLPOINTPARAMETERFVPROC,     glPointParameterfv)     || rval;
    rval = skGetOpenGL_Symbol(PFNGLPOINTPARAMETERIPROC,      glPointParameteri)      || rval;
    rval = skGetOpenGL_Symbol(PFNGLPOINTPARAMETERIVPROC,     glPointParameteriv)     || rval;
    return rval;
}


/*
========================================================
                       OpenGL_1_5
========================================================
*/
PFNGLGENQUERIESPROC              glGenQueries              = 0;
PFNGLDELETEQUERIESPROC           glDeleteQueries           = 0;
PFNGLISQUERYPROC                 glIsQuery                 = 0;
PFNGLBEGINQUERYPROC              glBeginQuery              = 0;
PFNGLENDQUERYPROC                glEndQuery                = 0;
PFNGLGETQUERYIVPROC              glGetQueryiv              = 0;
PFNGLGETQUERYOBJECTIVPROC        glGetQueryObjectiv        = 0;
PFNGLGETQUERYOBJECTUIVPROC       glGetQueryObjectuiv       = 0;
PFNGLBINDBUFFERPROC              glBindBuffer              = 0;
PFNGLDELETEBUFFERSPROC           glDeleteBuffers           = 0;
PFNGLGENBUFFERSPROC              glGenBuffers              = 0;
PFNGLISBUFFERPROC                glIsBuffer                = 0;
PFNGLBUFFERDATAPROC              glBufferData              = 0;
PFNGLBUFFERSUBDATAPROC           glBufferSubData           = 0;
PFNGLGETBUFFERSUBDATAPROC        glGetBufferSubData        = 0;
PFNGLMAPBUFFERPROC               glMapBuffer               = 0;
PFNGLUNMAPBUFFERPROC             glUnmapBuffer             = 0;
PFNGLGETBUFFERPARAMETERIVPROC    glGetBufferParameteriv    = 0;
PFNGLGETBUFFERPOINTERVPROC       glGetBufferPointerv       = 0;


bool skLoadOpenGL_1_5(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLGENQUERIESPROC,              glGenQueries)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETEQUERIESPROC,           glDeleteQueries)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLISQUERYPROC,                 glIsQuery)                 || rval;
    rval = skGetOpenGL_Symbol(PFNGLBEGINQUERYPROC,              glBeginQuery)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLENDQUERYPROC,                glEndQuery)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETQUERYIVPROC,              glGetQueryiv)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETQUERYOBJECTIVPROC,        glGetQueryObjectiv)        || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETQUERYOBJECTUIVPROC,       glGetQueryObjectuiv)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDBUFFERPROC,              glBindBuffer)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETEBUFFERSPROC,           glDeleteBuffers)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGENBUFFERSPROC,              glGenBuffers)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLISBUFFERPROC,                glIsBuffer)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLBUFFERDATAPROC,              glBufferData)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLBUFFERSUBDATAPROC,           glBufferSubData)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETBUFFERSUBDATAPROC,        glGetBufferSubData)        || rval;
    rval = skGetOpenGL_Symbol(PFNGLMAPBUFFERPROC,               glMapBuffer)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNMAPBUFFERPROC,             glUnmapBuffer)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETBUFFERPARAMETERIVPROC,    glGetBufferParameteriv)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETBUFFERPOINTERVPROC,       glGetBufferPointerv)       || rval;
    return rval;
}


/*
========================================================
                       OpenGL_2_0
========================================================
*/


PFNGLBLENDEQUATIONSEPARATEPROC       glBlendEquationSeparate       = 0;
PFNGLDRAWBUFFERSPROC                 glDrawBuffers                 = 0;
PFNGLSTENCILOPSEPARATEPROC           glStencilOpSeparate           = 0;
PFNGLSTENCILFUNCSEPARATEPROC         glStencilFuncSeparate         = 0;
PFNGLSTENCILMASKSEPARATEPROC         glStencilMaskSeparate         = 0;
PFNGLATTACHSHADERPROC                glAttachShader                = 0;
PFNGLBINDATTRIBLOCATIONPROC          glBindAttribLocation          = 0;
PFNGLCOMPILESHADERPROC               glCompileShader               = 0;
PFNGLCREATEPROGRAMPROC               glCreateProgram               = 0;
PFNGLCREATESHADERPROC                glCreateShader                = 0;
PFNGLDELETEPROGRAMPROC               glDeleteProgram               = 0;
PFNGLDELETESHADERPROC                glDeleteShader                = 0;
PFNGLDETACHSHADERPROC                glDetachShader                = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC    glDisableVertexAttribArray    = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC     glEnableVertexAttribArray     = 0;
PFNGLGETACTIVEATTRIBPROC             glGetActiveAttrib             = 0;
PFNGLGETACTIVEUNIFORMPROC            glGetActiveUniform            = 0;
PFNGLGETATTACHEDSHADERSPROC          glGetAttachedShaders          = 0;
PFNGLGETATTRIBLOCATIONPROC           glGetAttribLocation           = 0;
PFNGLGETPROGRAMIVPROC                glGetProgramiv                = 0;
PFNGLGETPROGRAMINFOLOGPROC           glGetProgramInfoLog           = 0;
PFNGLGETSHADERIVPROC                 glGetShaderiv                 = 0;
PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog            = 0;
PFNGLGETSHADERSOURCEPROC             glGetShaderSource             = 0;
PFNGLGETUNIFORMLOCATIONPROC          glGetUniformLocation          = 0;
PFNGLGETUNIFORMFVPROC                glGetUniformfv                = 0;
PFNGLGETUNIFORMIVPROC                glGetUniformiv                = 0;
PFNGLGETVERTEXATTRIBDVPROC           glGetVertexAttribdv           = 0;
PFNGLGETVERTEXATTRIBFVPROC           glGetVertexAttribfv           = 0;
PFNGLGETVERTEXATTRIBIVPROC           glGetVertexAttribiv           = 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC     glGetVertexAttribPointerv     = 0;
PFNGLISPROGRAMPROC                   glIsProgram                   = 0;
PFNGLISSHADERPROC                    glIsShader                    = 0;
PFNGLLINKPROGRAMPROC                 glLinkProgram                 = 0;
PFNGLSHADERSOURCEPROC                glShaderSource                = 0;
PFNGLUSEPROGRAMPROC                  glUseProgram                  = 0;
PFNGLUNIFORM1FPROC                   glUniform1f                   = 0;
PFNGLUNIFORM2FPROC                   glUniform2f                   = 0;
PFNGLUNIFORM3FPROC                   glUniform3f                   = 0;
PFNGLUNIFORM4FPROC                   glUniform4f                   = 0;
PFNGLUNIFORM1IPROC                   glUniform1i                   = 0;
PFNGLUNIFORM2IPROC                   glUniform2i                   = 0;
PFNGLUNIFORM3IPROC                   glUniform3i                   = 0;
PFNGLUNIFORM4IPROC                   glUniform4i                   = 0;
PFNGLUNIFORM1FVPROC                  glUniform1fv                  = 0;
PFNGLUNIFORM2FVPROC                  glUniform2fv                  = 0;
PFNGLUNIFORM3FVPROC                  glUniform3fv                  = 0;
PFNGLUNIFORM4FVPROC                  glUniform4fv                  = 0;
PFNGLUNIFORM1IVPROC                  glUniform1iv                  = 0;
PFNGLUNIFORM2IVPROC                  glUniform2iv                  = 0;
PFNGLUNIFORM3IVPROC                  glUniform3iv                  = 0;
PFNGLUNIFORM4IVPROC                  glUniform4iv                  = 0;
PFNGLUNIFORMMATRIX2FVPROC            glUniformMatrix2fv            = 0;
PFNGLUNIFORMMATRIX3FVPROC            glUniformMatrix3fv            = 0;
PFNGLUNIFORMMATRIX4FVPROC            glUniformMatrix4fv            = 0;
PFNGLVALIDATEPROGRAMPROC             glValidateProgram             = 0;
PFNGLVERTEXATTRIB1DPROC              glVertexAttrib1d              = 0;
PFNGLVERTEXATTRIB1DVPROC             glVertexAttrib1dv             = 0;
PFNGLVERTEXATTRIB1FPROC              glVertexAttrib1f              = 0;
PFNGLVERTEXATTRIB1FVPROC             glVertexAttrib1fv             = 0;
PFNGLVERTEXATTRIB1SPROC              glVertexAttrib1s              = 0;
PFNGLVERTEXATTRIB1SVPROC             glVertexAttrib1sv             = 0;
PFNGLVERTEXATTRIB2DPROC              glVertexAttrib2d              = 0;
PFNGLVERTEXATTRIB2DVPROC             glVertexAttrib2dv             = 0;
PFNGLVERTEXATTRIB2FPROC              glVertexAttrib2f              = 0;
PFNGLVERTEXATTRIB2FVPROC             glVertexAttrib2fv             = 0;
PFNGLVERTEXATTRIB2SPROC              glVertexAttrib2s              = 0;
PFNGLVERTEXATTRIB2SVPROC             glVertexAttrib2sv             = 0;
PFNGLVERTEXATTRIB3DPROC              glVertexAttrib3d              = 0;
PFNGLVERTEXATTRIB3DVPROC             glVertexAttrib3dv             = 0;
PFNGLVERTEXATTRIB3FPROC              glVertexAttrib3f              = 0;
PFNGLVERTEXATTRIB3FVPROC             glVertexAttrib3fv             = 0;
PFNGLVERTEXATTRIB3SPROC              glVertexAttrib3s              = 0;
PFNGLVERTEXATTRIB3SVPROC             glVertexAttrib3sv             = 0;
PFNGLVERTEXATTRIB4NBVPROC            glVertexAttrib4Nbv            = 0;
PFNGLVERTEXATTRIB4NIVPROC            glVertexAttrib4Niv            = 0;
PFNGLVERTEXATTRIB4NSVPROC            glVertexAttrib4Nsv            = 0;
PFNGLVERTEXATTRIB4NUBPROC            glVertexAttrib4Nub            = 0;
PFNGLVERTEXATTRIB4NUBVPROC           glVertexAttrib4Nubv           = 0;
PFNGLVERTEXATTRIB4NUIVPROC           glVertexAttrib4Nuiv           = 0;
PFNGLVERTEXATTRIB4NUSVPROC           glVertexAttrib4Nusv           = 0;
PFNGLVERTEXATTRIB4BVPROC             glVertexAttrib4bv             = 0;
PFNGLVERTEXATTRIB4DPROC              glVertexAttrib4d              = 0;
PFNGLVERTEXATTRIB4DVPROC             glVertexAttrib4dv             = 0;
PFNGLVERTEXATTRIB4FPROC              glVertexAttrib4f              = 0;
PFNGLVERTEXATTRIB4FVPROC             glVertexAttrib4fv             = 0;
PFNGLVERTEXATTRIB4IVPROC             glVertexAttrib4iv             = 0;
PFNGLVERTEXATTRIB4SPROC              glVertexAttrib4s              = 0;
PFNGLVERTEXATTRIB4SVPROC             glVertexAttrib4sv             = 0;
PFNGLVERTEXATTRIB4UBVPROC            glVertexAttrib4ubv            = 0;
PFNGLVERTEXATTRIB4UIVPROC            glVertexAttrib4uiv            = 0;
PFNGLVERTEXATTRIB4USVPROC            glVertexAttrib4usv            = 0;
PFNGLVERTEXATTRIBPOINTERPROC         glVertexAttribPointer         = 0;


bool skLoadOpenGL_2_0(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLBLENDEQUATIONSEPARATEPROC,       glBlendEquationSeparate)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLDRAWBUFFERSPROC,                 glDrawBuffers)                 || rval;
    rval = skGetOpenGL_Symbol(PFNGLSTENCILOPSEPARATEPROC,           glStencilOpSeparate)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLSTENCILFUNCSEPARATEPROC,         glStencilFuncSeparate)         || rval;
    rval = skGetOpenGL_Symbol(PFNGLSTENCILMASKSEPARATEPROC,         glStencilMaskSeparate)         || rval;
    rval = skGetOpenGL_Symbol(PFNGLATTACHSHADERPROC,                glAttachShader)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDATTRIBLOCATIONPROC,          glBindAttribLocation)          || rval;
    rval = skGetOpenGL_Symbol(PFNGLCOMPILESHADERPROC,               glCompileShader)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLCREATEPROGRAMPROC,               glCreateProgram)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLCREATESHADERPROC,                glCreateShader)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETEPROGRAMPROC,               glDeleteProgram)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETESHADERPROC,                glDeleteShader)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLDETACHSHADERPROC,                glDetachShader)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLDISABLEVERTEXATTRIBARRAYPROC,    glDisableVertexAttribArray)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLENABLEVERTEXATTRIBARRAYPROC,     glEnableVertexAttribArray)     || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETACTIVEATTRIBPROC,             glGetActiveAttrib)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETACTIVEUNIFORMPROC,            glGetActiveUniform)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETATTACHEDSHADERSPROC,          glGetAttachedShaders)          || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETATTRIBLOCATIONPROC,           glGetAttribLocation)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETPROGRAMIVPROC,                glGetProgramiv)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETPROGRAMINFOLOGPROC,           glGetProgramInfoLog)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETSHADERIVPROC,                 glGetShaderiv)                 || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETSHADERINFOLOGPROC,            glGetShaderInfoLog)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETSHADERSOURCEPROC,             glGetShaderSource)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETUNIFORMLOCATIONPROC,          glGetUniformLocation)          || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETUNIFORMFVPROC,                glGetUniformfv)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETUNIFORMIVPROC,                glGetUniformiv)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETVERTEXATTRIBDVPROC,           glGetVertexAttribdv)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETVERTEXATTRIBFVPROC,           glGetVertexAttribfv)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETVERTEXATTRIBIVPROC,           glGetVertexAttribiv)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETVERTEXATTRIBPOINTERVPROC,     glGetVertexAttribPointerv)     || rval;
    rval = skGetOpenGL_Symbol(PFNGLISPROGRAMPROC,                   glIsProgram)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLISSHADERPROC,                    glIsShader)                    || rval;
    rval = skGetOpenGL_Symbol(PFNGLLINKPROGRAMPROC,                 glLinkProgram)                 || rval;
    rval = skGetOpenGL_Symbol(PFNGLSHADERSOURCEPROC,                glShaderSource)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLUSEPROGRAMPROC,                  glUseProgram)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM1FPROC,                   glUniform1f)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM2FPROC,                   glUniform2f)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM3FPROC,                   glUniform3f)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM4FPROC,                   glUniform4f)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM1IPROC,                   glUniform1i)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM2IPROC,                   glUniform2i)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM3IPROC,                   glUniform3i)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM4IPROC,                   glUniform4i)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM1FVPROC,                  glUniform1fv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM2FVPROC,                  glUniform2fv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM3FVPROC,                  glUniform3fv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM4FVPROC,                  glUniform4fv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM1IVPROC,                  glUniform1iv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM2IVPROC,                  glUniform2iv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM3IVPROC,                  glUniform3iv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM4IVPROC,                  glUniform4iv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX2FVPROC,            glUniformMatrix2fv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX3FVPROC,            glUniformMatrix3fv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX4FVPROC,            glUniformMatrix4fv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVALIDATEPROGRAMPROC,             glValidateProgram)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB1DPROC,              glVertexAttrib1d)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB1DVPROC,             glVertexAttrib1dv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB1FPROC,              glVertexAttrib1f)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB1FVPROC,             glVertexAttrib1fv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB1SPROC,              glVertexAttrib1s)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB1SVPROC,             glVertexAttrib1sv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB2DPROC,              glVertexAttrib2d)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB2DVPROC,             glVertexAttrib2dv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB2FPROC,              glVertexAttrib2f)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB2FVPROC,             glVertexAttrib2fv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB2SPROC,              glVertexAttrib2s)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB2SVPROC,             glVertexAttrib2sv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB3DPROC,              glVertexAttrib3d)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB3DVPROC,             glVertexAttrib3dv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB3FPROC,              glVertexAttrib3f)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB3FVPROC,             glVertexAttrib3fv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB3SPROC,              glVertexAttrib3s)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB3SVPROC,             glVertexAttrib3sv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4NBVPROC,            glVertexAttrib4Nbv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4NIVPROC,            glVertexAttrib4Niv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4NSVPROC,            glVertexAttrib4Nsv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4NUBPROC,            glVertexAttrib4Nub)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4NUBVPROC,           glVertexAttrib4Nubv)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4NUIVPROC,           glVertexAttrib4Nuiv)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4NUSVPROC,           glVertexAttrib4Nusv)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4BVPROC,             glVertexAttrib4bv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4DPROC,              glVertexAttrib4d)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4DVPROC,             glVertexAttrib4dv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4FPROC,              glVertexAttrib4f)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4FVPROC,             glVertexAttrib4fv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4IVPROC,             glVertexAttrib4iv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4SPROC,              glVertexAttrib4s)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4SVPROC,             glVertexAttrib4sv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4UBVPROC,            glVertexAttrib4ubv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4UIVPROC,            glVertexAttrib4uiv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIB4USVPROC,            glVertexAttrib4usv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBPOINTERPROC,         glVertexAttribPointer)         || rval;
    return rval;
}


/*
========================================================
                       OpenGL_2_1
========================================================
*/
PFNGLUNIFORMMATRIX2X3FVPROC    glUniformMatrix2x3fv    = 0;
PFNGLUNIFORMMATRIX3X2FVPROC    glUniformMatrix3x2fv    = 0;
PFNGLUNIFORMMATRIX2X4FVPROC    glUniformMatrix2x4fv    = 0;
PFNGLUNIFORMMATRIX4X2FVPROC    glUniformMatrix4x2fv    = 0;
PFNGLUNIFORMMATRIX3X4FVPROC    glUniformMatrix3x4fv    = 0;
PFNGLUNIFORMMATRIX4X3FVPROC    glUniformMatrix4x3fv    = 0;


bool skLoadOpenGL_2_1(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX2X3FVPROC,    glUniformMatrix2x3fv)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX3X2FVPROC,    glUniformMatrix3x2fv)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX2X4FVPROC,    glUniformMatrix2x4fv)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX4X2FVPROC,    glUniformMatrix4x2fv)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX3X4FVPROC,    glUniformMatrix3x4fv)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORMMATRIX4X3FVPROC,    glUniformMatrix4x3fv)    || rval;
    return rval;
}


/*
========================================================
                       OpenGL_3_0
========================================================
*/


PFNGLCOLORMASKIPROC                     glColorMaski                     = 0;
PFNGLGETBOOLEANI_VPROC                  glGetBooleani_v                  = 0;
PFNGLGETINTEGERI_VPROC                  glGetIntegeri_v                  = 0;
PFNGLENABLEIPROC                        glEnablei                        = 0;
PFNGLDISABLEIPROC                       glDisablei                       = 0;
PFNGLISENABLEDIPROC                     glIsEnabledi                     = 0;
PFNGLBEGINTRANSFORMFEEDBACKPROC         glBeginTransformFeedback         = 0;
PFNGLENDTRANSFORMFEEDBACKPROC           glEndTransformFeedback           = 0;
PFNGLBINDBUFFERRANGEPROC                glBindBufferRange                = 0;
PFNGLBINDBUFFERBASEPROC                 glBindBufferBase                 = 0;
PFNGLTRANSFORMFEEDBACKVARYINGSPROC      glTransformFeedbackVaryings      = 0;
PFNGLGETTRANSFORMFEEDBACKVARYINGPROC    glGetTransformFeedbackVarying    = 0;
PFNGLCLAMPCOLORPROC                     glClampColor                     = 0;
PFNGLBEGINCONDITIONALRENDERPROC         glBeginConditionalRender         = 0;
PFNGLENDCONDITIONALRENDERPROC           glEndConditionalRender           = 0;
PFNGLVERTEXATTRIBIPOINTERPROC           glVertexAttribIPointer           = 0;
PFNGLGETVERTEXATTRIBIIVPROC             glGetVertexAttribIiv             = 0;
PFNGLGETVERTEXATTRIBIUIVPROC            glGetVertexAttribIuiv            = 0;
PFNGLVERTEXATTRIBI1IPROC                glVertexAttribI1i                = 0;
PFNGLVERTEXATTRIBI2IPROC                glVertexAttribI2i                = 0;
PFNGLVERTEXATTRIBI3IPROC                glVertexAttribI3i                = 0;
PFNGLVERTEXATTRIBI4IPROC                glVertexAttribI4i                = 0;
PFNGLVERTEXATTRIBI1UIPROC               glVertexAttribI1ui               = 0;
PFNGLVERTEXATTRIBI2UIPROC               glVertexAttribI2ui               = 0;
PFNGLVERTEXATTRIBI3UIPROC               glVertexAttribI3ui               = 0;
PFNGLVERTEXATTRIBI4UIPROC               glVertexAttribI4ui               = 0;
PFNGLVERTEXATTRIBI1IVPROC               glVertexAttribI1iv               = 0;
PFNGLVERTEXATTRIBI2IVPROC               glVertexAttribI2iv               = 0;
PFNGLVERTEXATTRIBI3IVPROC               glVertexAttribI3iv               = 0;
PFNGLVERTEXATTRIBI4IVPROC               glVertexAttribI4iv               = 0;
PFNGLVERTEXATTRIBI1UIVPROC              glVertexAttribI1uiv              = 0;
PFNGLVERTEXATTRIBI2UIVPROC              glVertexAttribI2uiv              = 0;
PFNGLVERTEXATTRIBI3UIVPROC              glVertexAttribI3uiv              = 0;
PFNGLVERTEXATTRIBI4UIVPROC              glVertexAttribI4uiv              = 0;
PFNGLVERTEXATTRIBI4BVPROC               glVertexAttribI4bv               = 0;
PFNGLVERTEXATTRIBI4SVPROC               glVertexAttribI4sv               = 0;
PFNGLVERTEXATTRIBI4UBVPROC              glVertexAttribI4ubv              = 0;
PFNGLVERTEXATTRIBI4USVPROC              glVertexAttribI4usv              = 0;
PFNGLGETUNIFORMUIVPROC                  glGetUniformuiv                  = 0;
PFNGLBINDFRAGDATALOCATIONPROC           glBindFragDataLocation           = 0;
PFNGLGETFRAGDATALOCATIONPROC            glGetFragDataLocation            = 0;
PFNGLUNIFORM1UIPROC                     glUniform1ui                     = 0;
PFNGLUNIFORM2UIPROC                     glUniform2ui                     = 0;
PFNGLUNIFORM3UIPROC                     glUniform3ui                     = 0;
PFNGLUNIFORM4UIPROC                     glUniform4ui                     = 0;
PFNGLUNIFORM1UIVPROC                    glUniform1uiv                    = 0;
PFNGLUNIFORM2UIVPROC                    glUniform2uiv                    = 0;
PFNGLUNIFORM3UIVPROC                    glUniform3uiv                    = 0;
PFNGLUNIFORM4UIVPROC                    glUniform4uiv                    = 0;
PFNGLTEXPARAMETERIIVPROC                glTexParameterIiv                = 0;
PFNGLTEXPARAMETERIUIVPROC               glTexParameterIuiv               = 0;
PFNGLGETTEXPARAMETERIIVPROC             glGetTexParameterIiv             = 0;
PFNGLGETTEXPARAMETERIUIVPROC            glGetTexParameterIuiv            = 0;
PFNGLCLEARBUFFERIVPROC                  glClearBufferiv                  = 0;
PFNGLCLEARBUFFERUIVPROC                 glClearBufferuiv                 = 0;
PFNGLCLEARBUFFERFVPROC                  glClearBufferfv                  = 0;
PFNGLCLEARBUFFERFIPROC                  glClearBufferfi                  = 0;
PFNGLGETSTRINGIPROC                     glGetStringi                     = 0;


bool skLoadOpenGL_3_0(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLCOLORMASKIPROC,                     glColorMaski)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETBOOLEANI_VPROC,                  glGetBooleani_v)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETINTEGERI_VPROC,                  glGetIntegeri_v)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLENABLEIPROC,                        glEnablei)                        || rval;
    rval = skGetOpenGL_Symbol(PFNGLDISABLEIPROC,                       glDisablei)                       || rval;
    rval = skGetOpenGL_Symbol(PFNGLISENABLEDIPROC,                     glIsEnabledi)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLBEGINTRANSFORMFEEDBACKPROC,         glBeginTransformFeedback)         || rval;
    rval = skGetOpenGL_Symbol(PFNGLENDTRANSFORMFEEDBACKPROC,           glEndTransformFeedback)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDBUFFERRANGEPROC,                glBindBufferRange)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDBUFFERBASEPROC,                 glBindBufferBase)                 || rval;
    rval = skGetOpenGL_Symbol(PFNGLTRANSFORMFEEDBACKVARYINGSPROC,      glTransformFeedbackVaryings)      || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETTRANSFORMFEEDBACKVARYINGPROC,    glGetTransformFeedbackVarying)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLCLAMPCOLORPROC,                     glClampColor)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLBEGINCONDITIONALRENDERPROC,         glBeginConditionalRender)         || rval;
    rval = skGetOpenGL_Symbol(PFNGLENDCONDITIONALRENDERPROC,           glEndConditionalRender)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBIPOINTERPROC,           glVertexAttribIPointer)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETVERTEXATTRIBIIVPROC,             glGetVertexAttribIiv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETVERTEXATTRIBIUIVPROC,            glGetVertexAttribIuiv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI1IPROC,                glVertexAttribI1i)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI2IPROC,                glVertexAttribI2i)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI3IPROC,                glVertexAttribI3i)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4IPROC,                glVertexAttribI4i)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI1UIPROC,               glVertexAttribI1ui)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI2UIPROC,               glVertexAttribI2ui)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI3UIPROC,               glVertexAttribI3ui)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4UIPROC,               glVertexAttribI4ui)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI1IVPROC,               glVertexAttribI1iv)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI2IVPROC,               glVertexAttribI2iv)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI3IVPROC,               glVertexAttribI3iv)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4IVPROC,               glVertexAttribI4iv)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI1UIVPROC,              glVertexAttribI1uiv)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI2UIVPROC,              glVertexAttribI2uiv)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI3UIVPROC,              glVertexAttribI3uiv)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4UIVPROC,              glVertexAttribI4uiv)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4BVPROC,               glVertexAttribI4bv)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4SVPROC,               glVertexAttribI4sv)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4UBVPROC,              glVertexAttribI4ubv)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLVERTEXATTRIBI4USVPROC,              glVertexAttribI4usv)              || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETUNIFORMUIVPROC,                  glGetUniformuiv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDFRAGDATALOCATIONPROC,           glBindFragDataLocation)           || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETFRAGDATALOCATIONPROC,            glGetFragDataLocation)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM1UIPROC,                     glUniform1ui)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM2UIPROC,                     glUniform2ui)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM3UIPROC,                     glUniform3ui)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM4UIPROC,                     glUniform4ui)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM1UIVPROC,                    glUniform1uiv)                    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM2UIVPROC,                    glUniform2uiv)                    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM3UIVPROC,                    glUniform3uiv)                    || rval;
    rval = skGetOpenGL_Symbol(PFNGLUNIFORM4UIVPROC,                    glUniform4uiv)                    || rval;
    rval = skGetOpenGL_Symbol(PFNGLTEXPARAMETERIIVPROC,                glTexParameterIiv)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLTEXPARAMETERIUIVPROC,               glTexParameterIuiv)               || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETTEXPARAMETERIIVPROC,             glGetTexParameterIiv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETTEXPARAMETERIUIVPROC,            glGetTexParameterIuiv)            || rval;
    rval = skGetOpenGL_Symbol(PFNGLCLEARBUFFERIVPROC,                  glClearBufferiv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLCLEARBUFFERUIVPROC,                 glClearBufferuiv)                 || rval;
    rval = skGetOpenGL_Symbol(PFNGLCLEARBUFFERFVPROC,                  glClearBufferfv)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLCLEARBUFFERFIPROC,                  glClearBufferfi)                  || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETSTRINGIPROC,                     glGetStringi)                     || rval;
    return rval;
}


/*
========================================================
               GL_ARB_vertex_array_object
========================================================
*/


PFNGLBINDVERTEXARRAYPROC       glBindVertexArray       = 0;
PFNGLDELETEVERTEXARRAYSPROC    glDeleteVertexArrays    = 0;
PFNGLGENVERTEXARRAYSPROC       glGenVertexArrays       = 0;
PFNGLISVERTEXARRAYPROC         glIsVertexArray         = 0;


bool skLoadGL_ARB_vertex_array_object(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLBINDVERTEXARRAYPROC,       glBindVertexArray)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETEVERTEXARRAYSPROC,    glDeleteVertexArrays)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLGENVERTEXARRAYSPROC,       glGenVertexArrays)       || rval;
    rval = skGetOpenGL_Symbol(PFNGLISVERTEXARRAYPROC,         glIsVertexArray)         || rval;
    return rval;
}
/*
========================================================
                GL_ARB_framebuffer_object
========================================================
*/
PFNGLISRENDERBUFFERPROC                         glIsRenderbuffer                         = 0;
PFNGLBINDRENDERBUFFERPROC                       glBindRenderbuffer                       = 0;
PFNGLDELETERENDERBUFFERSPROC                    glDeleteRenderbuffers                    = 0;
PFNGLGENRENDERBUFFERSPROC                       glGenRenderbuffers                       = 0;
PFNGLRENDERBUFFERSTORAGEPROC                    glRenderbufferStorage                    = 0;
PFNGLGETRENDERBUFFERPARAMETERIVPROC             glGetRenderbufferParameteriv             = 0;
PFNGLISFRAMEBUFFERPROC                          glIsFramebuffer                          = 0;
PFNGLBINDFRAMEBUFFERPROC                        glBindFramebuffer                        = 0;
PFNGLDELETEFRAMEBUFFERSPROC                     glDeleteFramebuffers                     = 0;
PFNGLGENFRAMEBUFFERSPROC                        glGenFramebuffers                        = 0;
PFNGLCHECKFRAMEBUFFERSTATUSPROC                 glCheckFramebufferStatus                 = 0;
PFNGLFRAMEBUFFERTEXTURE1DPROC                   glFramebufferTexture1D                   = 0;
PFNGLFRAMEBUFFERTEXTURE2DPROC                   glFramebufferTexture2D                   = 0;
PFNGLFRAMEBUFFERTEXTURE3DPROC                   glFramebufferTexture3D                   = 0;
PFNGLFRAMEBUFFERRENDERBUFFERPROC                glFramebufferRenderbuffer                = 0;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC    glGetFramebufferAttachmentParameteriv    = 0;
PFNGLGENERATEMIPMAPPROC                         glGenerateMipmap                         = 0;
PFNGLBLITFRAMEBUFFERPROC                        glBlitFramebuffer                        = 0;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC         glRenderbufferStorageMultisample         = 0;
PFNGLFRAMEBUFFERTEXTURELAYERPROC                glFramebufferTextureLayer                = 0;


bool skLoadGL_ARB_framebuffer_object(void)
{

    bool rval = false;
    rval = skGetOpenGL_Symbol(PFNGLISRENDERBUFFERPROC,                         glIsRenderbuffer)                         || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDRENDERBUFFERPROC,                       glBindRenderbuffer)                       || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETERENDERBUFFERSPROC,                    glDeleteRenderbuffers)                    || rval;
    rval = skGetOpenGL_Symbol(PFNGLGENRENDERBUFFERSPROC,                       glGenRenderbuffers)                       || rval;
    rval = skGetOpenGL_Symbol(PFNGLRENDERBUFFERSTORAGEPROC,                    glRenderbufferStorage)                    || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETRENDERBUFFERPARAMETERIVPROC,             glGetRenderbufferParameteriv)             || rval;
    rval = skGetOpenGL_Symbol(PFNGLISFRAMEBUFFERPROC,                          glIsFramebuffer)                          || rval;
    rval = skGetOpenGL_Symbol(PFNGLBINDFRAMEBUFFERPROC,                        glBindFramebuffer)                        || rval;
    rval = skGetOpenGL_Symbol(PFNGLDELETEFRAMEBUFFERSPROC,                     glDeleteFramebuffers)                     || rval;
    rval = skGetOpenGL_Symbol(PFNGLGENFRAMEBUFFERSPROC,                        glGenFramebuffers)                        || rval;
    rval = skGetOpenGL_Symbol(PFNGLCHECKFRAMEBUFFERSTATUSPROC,                 glCheckFramebufferStatus)                 || rval;
    rval = skGetOpenGL_Symbol(PFNGLFRAMEBUFFERTEXTURE1DPROC,                   glFramebufferTexture1D)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLFRAMEBUFFERTEXTURE2DPROC,                   glFramebufferTexture2D)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLFRAMEBUFFERTEXTURE3DPROC,                   glFramebufferTexture3D)                   || rval;
    rval = skGetOpenGL_Symbol(PFNGLFRAMEBUFFERRENDERBUFFERPROC,                glFramebufferRenderbuffer)                || rval;
    rval = skGetOpenGL_Symbol(PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC,    glGetFramebufferAttachmentParameteriv)    || rval;
    rval = skGetOpenGL_Symbol(PFNGLGENERATEMIPMAPPROC,                         glGenerateMipmap)                         || rval;
    rval = skGetOpenGL_Symbol(PFNGLBLITFRAMEBUFFERPROC,                        glBlitFramebuffer)                        || rval;
    rval = skGetOpenGL_Symbol(PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC,         glRenderbufferStorageMultisample)         || rval;
    rval = skGetOpenGL_Symbol(PFNGLFRAMEBUFFERTEXTURELAYERPROC,                glFramebufferTextureLayer)                || rval;
    return rval;
}



static skOpenGLCapabilities g_caps;


/*
===================
skGetOpenGLCapabilities
===================
*/
skOpenGLCapabilities* skGetOpenGLCapabilities(void)
{
    return &g_caps;
}
/*
===================
skLoadOpenGL
===================
*/
bool skLoadOpenGL(void)
{


#if SK_PLATFORM == SK_PLATFORM_WIN32
    opengl = LoadLibrary("Opengl32.dll");
    if (!opengl)
        return false;
#elif SK_PLATFORM == SK_PLATFORM_LINUX
    opengl = dlopen("gl", RTLD_LAZY);
    if (!opengl)
        return false;
#endif
    skFixedString<32> str = (const char*) glGetString(GL_VERSION);
    skLogf(LD_INFO, "Loading OpenGL %s\n", str.c_str());

    g_caps.skOpenGL_1_1 = skLoadOpenGL_1_1();
    if (g_caps.skOpenGL_1_1) skLogf(LD_INFO, "Loaded: OpenGL 1.1 profile.\n");
    g_caps.skOpenGL_1_2 = skLoadOpenGL_1_2();
    if (g_caps.skOpenGL_1_2) skLogf(LD_INFO, "Loaded: OpenGL 1.2 profile.\n");
    g_caps.skOpenGL_1_3 = skLoadOpenGL_1_3();
    if (g_caps.skOpenGL_1_3) skLogf(LD_INFO, "Loaded: OpenGL 1.3 profile.\n");
    g_caps.skOpenGL_1_4 = skLoadOpenGL_1_4();
    if (g_caps.skOpenGL_1_4) skLogf(LD_INFO, "Loaded: OpenGL 1.4 profile.\n");
    g_caps.skOpenGL_1_5 = skLoadOpenGL_1_5();
    if (g_caps.skOpenGL_1_5) skLogf(LD_INFO, "Loaded: OpenGL 1.5 profile.\n");
    g_caps.skOpenGL_2_0 = skLoadOpenGL_2_0();
    if (g_caps.skOpenGL_2_0) skLogf(LD_INFO, "Loaded: OpenGL 2_0 profile.\n");
    g_caps.skOpenGL_2_1 = skLoadOpenGL_2_1();
    if (g_caps.skOpenGL_2_1) skLogf(LD_INFO, "Loaded: OpenGL 2_1 profile.\n");
    g_caps.skOpenGL_3_0 = skLoadOpenGL_3_0();
    if (g_caps.skOpenGL_3_0) skLogf(LD_INFO, "Loaded: OpenGL 3_0 profile.\n");
    g_caps.skOpenGL_ARB_vertex_array_object = skLoadGL_ARB_vertex_array_object();
    if (g_caps.skOpenGL_ARB_vertex_array_object)
        skLogf(LD_INFO, "Loaded: OpenGL ARB_vertex_array_object profile.\n");
    g_caps.skOpenGL_ARB_framebuffer_object = skLoadGL_ARB_framebuffer_object();
    if (g_caps.skOpenGL_ARB_framebuffer_object)
        skLogf(LD_INFO, "Loaded: OpenGL ARB_framebuffer_object profile.\n");

#if SK_PLATFORM == SK_PLATFORM_WIN32
    opengl = 0;
#endif

    return true;
}
