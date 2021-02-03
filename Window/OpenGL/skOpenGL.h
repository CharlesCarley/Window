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
#ifndef _skOpenGL_h_
#define _skOpenGL_h_

#include "Utils/Config/skConfig.h"

#if SK_PLATFORM == SK_PLATFORM_WIN32
    #define GL3_APIENTRY  __stdcall
#else
    #define GL3_APIENTRY
#endif

#define GL3_APIENTRYP GL3_APIENTRY *
#define GL3_API extern "C"


typedef unsigned int    GLenum;
typedef unsigned char   GLboolean;
typedef unsigned int    GLbitfield;
typedef signed char     GLbyte;
typedef short           GLshort;
typedef int             GLint;
typedef int             GLsizei;
typedef unsigned char   GLubyte;
typedef unsigned short  GLushort;
typedef unsigned int    GLuint;
typedef float           GLfloat;
typedef float           GLclampf;
typedef double          GLdouble;
typedef double          GLclampd;
typedef void            GLvoid;
typedef char            GLchar;
typedef SKintPtr        GLsizeiptr;
typedef SKintPtr        GLintptr;
/*
========================================================
                       OpenGL_1_0
========================================================
*/
GL3_API void           GL3_APIENTRY glCullFace(GLenum mode);
GL3_API void           GL3_APIENTRY glFrontFace(GLenum mode);
GL3_API void           GL3_APIENTRY glHint(GLenum target, GLenum mode);
GL3_API void           GL3_APIENTRY glLineWidth(GLfloat width);
GL3_API void           GL3_APIENTRY glPointSize(GLfloat size);
GL3_API void           GL3_APIENTRY glPolygonMode(GLenum face, GLenum mode);
GL3_API void           GL3_APIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
GL3_API void           GL3_APIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param);
GL3_API void           GL3_APIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params);
GL3_API void           GL3_APIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param);
GL3_API void           GL3_APIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint* params);
GL3_API void           GL3_APIENTRY glTexImage1D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
GL3_API void           GL3_APIENTRY glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
GL3_API void           GL3_APIENTRY glDrawBuffer(GLenum mode);
GL3_API void           GL3_APIENTRY glClear(GLbitfield mask);
GL3_API void           GL3_APIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
GL3_API void           GL3_APIENTRY glClearStencil(GLint s);
GL3_API void           GL3_APIENTRY glClearDepth(GLclampd depth);
GL3_API void           GL3_APIENTRY glStencilMask(GLuint mask);
GL3_API void           GL3_APIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
GL3_API void           GL3_APIENTRY glDepthMask(GLboolean flag);
GL3_API void           GL3_APIENTRY glDisable(GLenum cap);
GL3_API void           GL3_APIENTRY glEnable(GLenum cap);
GL3_API void           GL3_APIENTRY glFinish();
GL3_API void           GL3_APIENTRY glFlush();
GL3_API void           GL3_APIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor);
GL3_API void           GL3_APIENTRY glLogicOp(GLenum opcode);
GL3_API void           GL3_APIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask);
GL3_API void           GL3_APIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass);
GL3_API void           GL3_APIENTRY glDepthFunc(GLenum func);
GL3_API void           GL3_APIENTRY glPixelStoref(GLenum pname, GLfloat param);
GL3_API void           GL3_APIENTRY glPixelStorei(GLenum pname, GLint param);
GL3_API void           GL3_APIENTRY glReadBuffer(GLenum mode);
GL3_API void           GL3_APIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
GL3_API void           GL3_APIENTRY glGetBooleanv(GLenum pname, GLboolean* params);
GL3_API void           GL3_APIENTRY glGetDoublev(GLenum pname, GLdouble* params);
GL3_API GLenum         GL3_APIENTRY glGetError();
GL3_API void           GL3_APIENTRY glGetFloatv(GLenum pname, GLfloat* params);
GL3_API void           GL3_APIENTRY glGetIntegerv(GLenum pname, GLint* params);
GL3_API const GLubyte* GL3_APIENTRY glGetString(GLenum name);
GL3_API void           GL3_APIENTRY glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid* pixels);
GL3_API void           GL3_APIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
GL3_API void           GL3_APIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint* params);
GL3_API void           GL3_APIENTRY glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat* params);
GL3_API void           GL3_APIENTRY glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint* params);
GL3_API GLboolean      GL3_APIENTRY glIsEnabled(GLenum cap);
GL3_API void           GL3_APIENTRY glDepthRange(GLclampd _near, GLclampd _far);
GL3_API void           GL3_APIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height);
/*
========================================================
                       OpenGL_1_1
========================================================
*/
#define GL_DEPTH_BUFFER_BIT           0x00000100
#define GL_STENCIL_BUFFER_BIT         0x00000400
#define GL_COLOR_BUFFER_BIT           0x00004000
#define GL_FALSE                      0
#define GL_TRUE                       1
#define GL_POINTS                     0x0000
#define GL_LINES                      0x0001
#define GL_LINE_LOOP                  0x0002
#define GL_LINE_STRIP                 0x0003
#define GL_TRIANGLES                  0x0004
#define GL_TRIANGLE_STRIP             0x0005
#define GL_TRIANGLE_FAN               0x0006
#define GL_NEVER                      0x0200
#define GL_LESS                       0x0201
#define GL_EQUAL                      0x0202
#define GL_LEQUAL                     0x0203
#define GL_GREATER                    0x0204
#define GL_NOTEQUAL                   0x0205
#define GL_GEQUAL                     0x0206
#define GL_ALWAYS                     0x0207
#define GL_ZERO                       0
#define GL_ONE                        1
#define GL_SRC_COLOR                  0x0300
#define GL_ONE_MINUS_SRC_COLOR        0x0301
#define GL_SRC_ALPHA                  0x0302
#define GL_ONE_MINUS_SRC_ALPHA        0x0303
#define GL_DST_ALPHA                  0x0304
#define GL_ONE_MINUS_DST_ALPHA        0x0305
#define GL_DST_COLOR                  0x0306
#define GL_ONE_MINUS_DST_COLOR        0x0307
#define GL_SRC_ALPHA_SATURATE         0x0308
#define GL_NONE                       0
#define GL_FRONT_LEFT                 0x0400
#define GL_FRONT_RIGHT                0x0401
#define GL_BACK_LEFT                  0x0402
#define GL_BACK_RIGHT                 0x0403
#define GL_FRONT                      0x0404
#define GL_BACK                       0x0405
#define GL_LEFT                       0x0406
#define GL_RIGHT                      0x0407
#define GL_FRONT_AND_BACK             0x0408
#define GL_NO_ERROR                   0
#define GL_INVALID_ENUM               0x0500
#define GL_INVALID_VALUE              0x0501
#define GL_INVALID_OPERATION          0x0502
#define GL_OUT_OF_MEMORY              0x0505
#define GL_CW                         0x0900
#define GL_CCW                        0x0901
#define GL_POINT_SIZE                 0x0B11
#define GL_POINT_SIZE_RANGE           0x0B12
#define GL_POINT_SIZE_GRANULARITY     0x0B13
#define GL_LINE_SMOOTH                0x0B20
#define GL_LINE_WIDTH                 0x0B21
#define GL_LINE_WIDTH_RANGE           0x0B22
#define GL_LINE_WIDTH_GRANULARITY     0x0B23
#define GL_POLYGON_SMOOTH             0x0B41
#define GL_CULL_FACE                  0x0B44
#define GL_CULL_FACE_MODE             0x0B45
#define GL_FRONT_FACE                 0x0B46
#define GL_DEPTH_RANGE                0x0B70
#define GL_DEPTH_TEST                 0x0B71
#define GL_DEPTH_WRITEMASK            0x0B72
#define GL_DEPTH_CLEAR_VALUE          0x0B73
#define GL_DEPTH_FUNC                 0x0B74
#define GL_STENCIL_TEST               0x0B90
#define GL_STENCIL_CLEAR_VALUE        0x0B91
#define GL_STENCIL_FUNC               0x0B92
#define GL_STENCIL_VALUE_MASK         0x0B93
#define GL_STENCIL_FAIL               0x0B94
#define GL_STENCIL_PASS_DEPTH_FAIL    0x0B95
#define GL_STENCIL_PASS_DEPTH_PASS    0x0B96
#define GL_STENCIL_REF                0x0B97
#define GL_STENCIL_WRITEMASK          0x0B98
#define GL_VIEWPORT                   0x0BA2
#define GL_DITHER                     0x0BD0
#define GL_BLEND_DST                  0x0BE0
#define GL_BLEND_SRC                  0x0BE1
#define GL_BLEND                      0x0BE2
#define GL_LOGIC_OP_MODE              0x0BF0
#define GL_COLOR_LOGIC_OP             0x0BF2
#define GL_DRAW_BUFFER                0x0C01
#define GL_READ_BUFFER                0x0C02
#define GL_SCISSOR_BOX                0x0C10
#define GL_SCISSOR_TEST               0x0C11
#define GL_COLOR_CLEAR_VALUE          0x0C22
#define GL_COLOR_WRITEMASK            0x0C23
#define GL_DOUBLEBUFFER               0x0C32
#define GL_STEREO                     0x0C33
#define GL_LINE_SMOOTH_HINT           0x0C52
#define GL_POLYGON_SMOOTH_HINT        0x0C53
#define GL_UNPACK_SWAP_BYTES          0x0CF0
#define GL_UNPACK_LSB_FIRST           0x0CF1
#define GL_UNPACK_ROW_LENGTH          0x0CF2
#define GL_UNPACK_SKIP_ROWS           0x0CF3
#define GL_UNPACK_SKIP_PIXELS         0x0CF4
#define GL_UNPACK_ALIGNMENT           0x0CF5
#define GL_PACK_SWAP_BYTES            0x0D00
#define GL_PACK_LSB_FIRST             0x0D01
#define GL_PACK_ROW_LENGTH            0x0D02
#define GL_PACK_SKIP_ROWS             0x0D03
#define GL_PACK_SKIP_PIXELS           0x0D04
#define GL_PACK_ALIGNMENT             0x0D05
#define GL_MAX_TEXTURE_SIZE           0x0D33
#define GL_MAX_VIEWPORT_DIMS          0x0D3A
#define GL_SUBPIXEL_BITS              0x0D50
#define GL_TEXTURE_1D                 0x0DE0
#define GL_TEXTURE_2D                 0x0DE1
#define GL_POLYGON_OFFSET_UNITS       0x2A00
#define GL_POLYGON_OFFSET_POINT       0x2A01
#define GL_POLYGON_OFFSET_LINE        0x2A02
#define GL_POLYGON_OFFSET_FILL        0x8037
#define GL_POLYGON_OFFSET_FACTOR      0x8038
#define GL_TEXTURE_BINDING_1D         0x8068
#define GL_TEXTURE_BINDING_2D         0x8069
#define GL_TEXTURE_WIDTH              0x1000
#define GL_TEXTURE_HEIGHT             0x1001
#define GL_TEXTURE_INTERNAL_FORMAT    0x1003
#define GL_TEXTURE_BORDER_COLOR       0x1004
#define GL_TEXTURE_RED_SIZE           0x805C
#define GL_TEXTURE_GREEN_SIZE         0x805D
#define GL_TEXTURE_BLUE_SIZE          0x805E
#define GL_TEXTURE_ALPHA_SIZE         0x805F
#define GL_DONT_CARE                  0x1100
#define GL_FASTEST                    0x1101
#define GL_NICEST                     0x1102
#define GL_BYTE                       0x1400
#define GL_UNSIGNED_BYTE              0x1401
#define GL_SHORT                      0x1402
#define GL_UNSIGNED_SHORT             0x1403
#define GL_INT                        0x1404
#define GL_UNSIGNED_INT               0x1405
#define GL_FLOAT                      0x1406
#define GL_DOUBLE                     0x140A
#define GL_CLEAR                      0x1500
#define GL_AND                        0x1501
#define GL_AND_REVERSE                0x1502
#define GL_COPY                       0x1503
#define GL_AND_INVERTED               0x1504
#define GL_NOOP                       0x1505
#define GL_XOR                        0x1506
#define GL_OR                         0x1507
#define GL_NOR                        0x1508
#define GL_EQUIV                      0x1509
#define GL_INVERT                     0x150A
#define GL_OR_REVERSE                 0x150B
#define GL_COPY_INVERTED              0x150C
#define GL_OR_INVERTED                0x150D
#define GL_NAND                       0x150E
#define GL_SET                        0x150F
#define GL_TEXTURE                    0x1702
#define GL_COLOR                      0x1800
#define GL_DEPTH                      0x1801
#define GL_STENCIL                    0x1802
#define GL_STENCIL_INDEX              0x1901
#define GL_DEPTH_COMPONENT            0x1902
#define GL_RED                        0x1903
#define GL_GREEN                      0x1904
#define GL_BLUE                       0x1905
#define GL_ALPHA                      0x1906
#define GL_RGB                        0x1907
#define GL_RGBA                       0x1908
#define GL_POINT                      0x1B00
#define GL_LINE                       0x1B01
#define GL_FILL                       0x1B02
#define GL_KEEP                       0x1E00
#define GL_REPLACE                    0x1E01
#define GL_INCR                       0x1E02
#define GL_DECR                       0x1E03
#define GL_VENDOR                     0x1F00
#define GL_RENDERER                   0x1F01
#define GL_VERSION                    0x1F02
#define GL_EXTENSIONS                 0x1F03
#define GL_NEAREST                    0x2600
#define GL_LINEAR                     0x2601
#define GL_NEAREST_MIPMAP_NEAREST     0x2700
#define GL_LINEAR_MIPMAP_NEAREST      0x2701
#define GL_NEAREST_MIPMAP_LINEAR      0x2702
#define GL_LINEAR_MIPMAP_LINEAR       0x2703
#define GL_TEXTURE_MAG_FILTER         0x2800
#define GL_TEXTURE_MIN_FILTER         0x2801
#define GL_TEXTURE_WRAP_S             0x2802
#define GL_TEXTURE_WRAP_T             0x2803
#define GL_PROXY_TEXTURE_1D           0x8063
#define GL_PROXY_TEXTURE_2D           0x8064
#define GL_REPEAT                     0x2901
#define GL_R3_G3_B2                   0x2A10
#define GL_RGB4                       0x804F
#define GL_RGB5                       0x8050
#define GL_RGB8                       0x8051
#define GL_RGB10                      0x8052
#define GL_RGB12                      0x8053
#define GL_RGB16                      0x8054
#define GL_RGBA2                      0x8055
#define GL_RGBA4                      0x8056
#define GL_RGB5_A1                    0x8057
#define GL_RGBA8                      0x8058
#define GL_RGB10_A2                   0x8059
#define GL_RGBA12                     0x805A
#define GL_RGBA16                     0x805B


typedef void (GL3_APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum, GLint, GLsizei);
typedef void (GL3_APIENTRYP PFNGLDRAWELEMENTSPROC)(GLenum, GLsizei, GLenum, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLGETPOINTERVPROC)(GLenum, GLvoid**);
typedef void (GL3_APIENTRYP PFNGLPOLYGONOFFSETPROC)(GLfloat, GLfloat);
typedef void (GL3_APIENTRYP PFNGLCOPYTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLint);
typedef void (GL3_APIENTRYP PFNGLCOPYTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLint, GLint, GLsizei, GLsizei, GLint);
typedef void (GL3_APIENTRYP PFNGLCOPYTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei);
typedef void (GL3_APIENTRYP PFNGLCOPYTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);
typedef void (GL3_APIENTRYP PFNGLTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLenum, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLBINDTEXTUREPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLDELETETEXTURESPROC)(GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLGENTEXTURESPROC)(GLsizei, GLuint*);
typedef GLboolean(GL3_APIENTRYP PFNGLISTEXTUREPROC)(GLuint);


extern PFNGLDRAWARRAYSPROC           glDrawArrays;
extern PFNGLDRAWELEMENTSPROC         glDrawElements;
extern PFNGLGETPOINTERVPROC          glGetPointerv;
extern PFNGLPOLYGONOFFSETPROC        glPolygonOffset;
extern PFNGLCOPYTEXIMAGE1DPROC       glCopyTexImage1D;
extern PFNGLCOPYTEXIMAGE2DPROC       glCopyTexImage2D;
extern PFNGLCOPYTEXSUBIMAGE1DPROC    glCopyTexSubImage1D;
extern PFNGLCOPYTEXSUBIMAGE2DPROC    glCopyTexSubImage2D;
extern PFNGLTEXSUBIMAGE1DPROC        glTexSubImage1D;
extern PFNGLTEXSUBIMAGE2DPROC        glTexSubImage2D;
extern PFNGLBINDTEXTUREPROC          glBindTexture;
extern PFNGLDELETETEXTURESPROC       glDeleteTextures;
extern PFNGLGENTEXTURESPROC          glGenTextures;
extern PFNGLISTEXTUREPROC            glIsTexture;


/*
========================================================
                       OpenGL_1_2
========================================================
*/
#define GL_UNSIGNED_BYTE_3_3_2              0x8032
#define GL_UNSIGNED_SHORT_4_4_4_4           0x8033
#define GL_UNSIGNED_SHORT_5_5_5_1           0x8034
#define GL_UNSIGNED_INT_8_8_8_8             0x8035
#define GL_UNSIGNED_INT_10_10_10_2          0x8036
#define GL_TEXTURE_BINDING_3D               0x806A
#define GL_PACK_SKIP_IMAGES                 0x806B
#define GL_PACK_IMAGE_HEIGHT                0x806C
#define GL_UNPACK_SKIP_IMAGES               0x806D
#define GL_UNPACK_IMAGE_HEIGHT              0x806E
#define GL_TEXTURE_3D                       0x806F
#define GL_PROXY_TEXTURE_3D                 0x8070
#define GL_TEXTURE_DEPTH                    0x8071
#define GL_TEXTURE_WRAP_R                   0x8072
#define GL_MAX_3D_TEXTURE_SIZE              0x8073
#define GL_UNSIGNED_BYTE_2_3_3_REV          0x8362
#define GL_UNSIGNED_SHORT_5_6_5             0x8363
#define GL_UNSIGNED_SHORT_5_6_5_REV         0x8364
#define GL_UNSIGNED_SHORT_4_4_4_4_REV       0x8365
#define GL_UNSIGNED_SHORT_1_5_5_5_REV       0x8366
#define GL_UNSIGNED_INT_8_8_8_8_REV         0x8367
#define GL_UNSIGNED_INT_2_10_10_10_REV      0x8368
#define GL_BGR                              0x80E0
#define GL_BGRA                             0x80E1
#define GL_MAX_ELEMENTS_VERTICES            0x80E8
#define GL_MAX_ELEMENTS_INDICES             0x80E9
#define GL_CLAMP_TO_EDGE                    0x812F
#define GL_TEXTURE_MIN_LOD                  0x813A
#define GL_TEXTURE_MAX_LOD                  0x813B
#define GL_TEXTURE_BASE_LEVEL               0x813C
#define GL_TEXTURE_MAX_LEVEL                0x813D
#define GL_SMOOTH_POINT_SIZE_RANGE          0x0B12
#define GL_SMOOTH_POINT_SIZE_GRANULARITY    0x0B13
#define GL_SMOOTH_LINE_WIDTH_RANGE          0x0B22
#define GL_SMOOTH_LINE_WIDTH_GRANULARITY    0x0B23
#define GL_ALIASED_LINE_WIDTH_RANGE         0x846E


typedef void (GL3_APIENTRYP PFNGLBLENDCOLORPROC)(GLclampf, GLclampf, GLclampf, GLclampf);
typedef void (GL3_APIENTRYP PFNGLBLENDEQUATIONPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLDRAWRANGEELEMENTSPROC)(GLenum, GLuint, GLuint, GLsizei, GLenum, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLTEXIMAGE3DPROC)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLCOPYTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLint, GLint, GLsizei, GLsizei);


extern PFNGLBLENDCOLORPROC           glBlendColor;
extern PFNGLBLENDEQUATIONPROC        glBlendEquation;
extern PFNGLDRAWRANGEELEMENTSPROC    glDrawRangeElements;
extern PFNGLTEXIMAGE3DPROC           glTexImage3D;
extern PFNGLTEXSUBIMAGE3DPROC        glTexSubImage3D;
extern PFNGLCOPYTEXSUBIMAGE3DPROC    glCopyTexSubImage3D;


/*
========================================================
                       OpenGL_1_3
========================================================
*/
#define GL_TEXTURE0                          0x84C0
#define GL_TEXTURE1                          0x84C1
#define GL_TEXTURE2                          0x84C2
#define GL_TEXTURE3                          0x84C3
#define GL_TEXTURE4                          0x84C4
#define GL_TEXTURE5                          0x84C5
#define GL_TEXTURE6                          0x84C6
#define GL_TEXTURE7                          0x84C7
#define GL_TEXTURE8                          0x84C8
#define GL_TEXTURE9                          0x84C9
#define GL_TEXTURE10                         0x84CA
#define GL_TEXTURE11                         0x84CB
#define GL_TEXTURE12                         0x84CC
#define GL_TEXTURE13                         0x84CD
#define GL_TEXTURE14                         0x84CE
#define GL_TEXTURE15                         0x84CF
#define GL_TEXTURE16                         0x84D0
#define GL_TEXTURE17                         0x84D1
#define GL_TEXTURE18                         0x84D2
#define GL_TEXTURE19                         0x84D3
#define GL_TEXTURE20                         0x84D4
#define GL_TEXTURE21                         0x84D5
#define GL_TEXTURE22                         0x84D6
#define GL_TEXTURE23                         0x84D7
#define GL_TEXTURE24                         0x84D8
#define GL_TEXTURE25                         0x84D9
#define GL_TEXTURE26                         0x84DA
#define GL_TEXTURE27                         0x84DB
#define GL_TEXTURE28                         0x84DC
#define GL_TEXTURE29                         0x84DD
#define GL_TEXTURE30                         0x84DE
#define GL_TEXTURE31                         0x84DF
#define GL_ACTIVE_TEXTURE                    0x84E0
#define GL_MULTISAMPLE                       0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE          0x809E
#define GL_SAMPLE_ALPHA_TO_ONE               0x809F
#define GL_SAMPLE_COVERAGE                   0x80A0
#define GL_SAMPLE_BUFFERS                    0x80A8
#define GL_SAMPLES                           0x80A9
#define GL_SAMPLE_COVERAGE_VALUE             0x80AA
#define GL_SAMPLE_COVERAGE_INVERT            0x80AB
#define GL_TEXTURE_CUBE_MAP                  0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP          0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X       0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X       0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y       0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y       0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z       0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z       0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP            0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE         0x851C
#define GL_COMPRESSED_RGB                    0x84ED
#define GL_COMPRESSED_RGBA                   0x84EE
#define GL_TEXTURE_COMPRESSION_HINT          0x84EF
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE     0x86A0
#define GL_TEXTURE_COMPRESSED                0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS    0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS        0x86A3
#define GL_CLAMP_TO_BORDER                   0x812D


typedef void (GL3_APIENTRYP PFNGLACTIVETEXTUREPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLSAMPLECOVERAGEPROC)(GLclampf, GLboolean);
typedef void (GL3_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE3DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE2DPROC)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLCOMPRESSEDTEXIMAGE1DPROC)(GLenum, GLint, GLenum, GLsizei, GLint, GLsizei, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)(GLenum, GLint, GLint, GLint, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)(GLenum, GLint, GLint, GLsizei, GLenum, GLsizei, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLGETCOMPRESSEDTEXIMAGEPROC)(GLenum, GLint, GLvoid*);


extern PFNGLACTIVETEXTUREPROC              glActiveTexture;
extern PFNGLSAMPLECOVERAGEPROC             glSampleCoverage;
extern PFNGLCOMPRESSEDTEXIMAGE3DPROC       glCompressedTexImage3D;
extern PFNGLCOMPRESSEDTEXIMAGE2DPROC       glCompressedTexImage2D;
extern PFNGLCOMPRESSEDTEXIMAGE1DPROC       glCompressedTexImage1D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC    glCompressedTexSubImage3D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC    glCompressedTexSubImage2D;
extern PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC    glCompressedTexSubImage1D;
extern PFNGLGETCOMPRESSEDTEXIMAGEPROC      glGetCompressedTexImage;


/*
========================================================
                       OpenGL_1_4
========================================================
*/
#define GL_BLEND_DST_RGB                0x80C8
#define GL_BLEND_SRC_RGB                0x80C9
#define GL_BLEND_DST_ALPHA              0x80CA
#define GL_BLEND_SRC_ALPHA              0x80CB
#define GL_POINT_FADE_THRESHOLD_SIZE    0x8128
#define GL_DEPTH_COMPONENT16            0x81A5
#define GL_DEPTH_COMPONENT24            0x81A6
#define GL_DEPTH_COMPONENT32            0x81A7
#define GL_MIRRORED_REPEAT              0x8370
#define GL_MAX_TEXTURE_LOD_BIAS         0x84FD
#define GL_TEXTURE_LOD_BIAS             0x8501
#define GL_INCR_WRAP                    0x8507
#define GL_DECR_WRAP                    0x8508
#define GL_TEXTURE_DEPTH_SIZE           0x884A
#define GL_TEXTURE_COMPARE_MODE         0x884C
#define GL_TEXTURE_COMPARE_FUNC         0x884D


typedef void (GL3_APIENTRYP PFNGLBLENDFUNCSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
typedef void (GL3_APIENTRYP PFNGLMULTIDRAWARRAYSPROC)(GLenum, const GLint*, const GLsizei*, GLsizei);
typedef void (GL3_APIENTRYP PFNGLMULTIDRAWELEMENTSPROC)(GLenum, const GLsizei*, GLenum, const GLvoid**, GLsizei);
typedef void (GL3_APIENTRYP PFNGLPOINTPARAMETERFPROC)(GLenum, GLfloat);
typedef void (GL3_APIENTRYP PFNGLPOINTPARAMETERFVPROC)(GLenum, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLPOINTPARAMETERIPROC)(GLenum, GLint);
typedef void (GL3_APIENTRYP PFNGLPOINTPARAMETERIVPROC)(GLenum, const GLint*);


extern PFNGLBLENDFUNCSEPARATEPROC    glBlendFuncSeparate;
extern PFNGLMULTIDRAWARRAYSPROC      glMultiDrawArrays;
extern PFNGLMULTIDRAWELEMENTSPROC    glMultiDrawElements;
extern PFNGLPOINTPARAMETERFPROC      glPointParameterf;
extern PFNGLPOINTPARAMETERFVPROC     glPointParameterfv;
extern PFNGLPOINTPARAMETERIPROC      glPointParameteri;
extern PFNGLPOINTPARAMETERIVPROC     glPointParameteriv;


/*
========================================================
                       OpenGL_1_5
========================================================
*/
#define GL_BUFFER_SIZE                           0x8764
#define GL_BUFFER_USAGE                          0x8765
#define GL_QUERY_COUNTER_BITS                    0x8864
#define GL_CURRENT_QUERY                         0x8865
#define GL_QUERY_RESULT                          0x8866
#define GL_QUERY_RESULT_AVAILABLE                0x8867
#define GL_ARRAY_BUFFER                          0x8892
#define GL_ELEMENT_ARRAY_BUFFER                  0x8893
#define GL_ARRAY_BUFFER_BINDING                  0x8894
#define GL_ELEMENT_ARRAY_BUFFER_BINDING          0x8895
#define GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING    0x889F
#define GL_READ_ONLY                             0x88B8
#define GL_WRITE_ONLY                            0x88B9
#define GL_READ_WRITE                            0x88BA
#define GL_BUFFER_ACCESS                         0x88BB
#define GL_BUFFER_MAPPED                         0x88BC
#define GL_BUFFER_MAP_POINTER                    0x88BD
#define GL_STREAM_DRAW                           0x88E0
#define GL_STREAM_READ                           0x88E1
#define GL_STREAM_COPY                           0x88E2
#define GL_STATIC_DRAW                           0x88E4
#define GL_STATIC_READ                           0x88E5
#define GL_STATIC_COPY                           0x88E6
#define GL_DYNAMIC_DRAW                          0x88E8
#define GL_DYNAMIC_READ                          0x88E9
#define GL_DYNAMIC_COPY                          0x88EA
#define GL_SAMPLES_PASSED                        0x8914


typedef void (GL3_APIENTRYP PFNGLGENQUERIESPROC)(GLsizei, GLuint*);
typedef void (GL3_APIENTRYP PFNGLDELETEQUERIESPROC)(GLsizei, const GLuint*);
typedef GLboolean(GL3_APIENTRYP PFNGLISQUERYPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLBEGINQUERYPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLENDQUERYPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLGETQUERYIVPROC)(GLenum, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETQUERYOBJECTIVPROC)(GLuint, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETQUERYOBJECTUIVPROC)(GLuint, GLenum, GLuint*);
typedef void (GL3_APIENTRYP PFNGLBINDBUFFERPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLDELETEBUFFERSPROC)(GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei, GLuint*);
typedef GLboolean(GL3_APIENTRYP PFNGLISBUFFERPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLBUFFERDATAPROC)(GLenum, GLsizeiptr, const GLvoid*, GLenum);
typedef void (GL3_APIENTRYP PFNGLBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLGETBUFFERSUBDATAPROC)(GLenum, GLintptr, GLsizeiptr, GLvoid*);
typedef GLvoid* (GL3_APIENTRYP PFNGLMAPBUFFERPROC)(GLenum, GLenum);
typedef GLboolean(GL3_APIENTRYP PFNGLUNMAPBUFFERPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLGETBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETBUFFERPOINTERVPROC)(GLenum, GLenum, GLvoid**);


extern PFNGLGENQUERIESPROC              glGenQueries;
extern PFNGLDELETEQUERIESPROC           glDeleteQueries;
extern PFNGLISQUERYPROC                 glIsQuery;
extern PFNGLBEGINQUERYPROC              glBeginQuery;
extern PFNGLENDQUERYPROC                glEndQuery;
extern PFNGLGETQUERYIVPROC              glGetQueryiv;
extern PFNGLGETQUERYOBJECTIVPROC        glGetQueryObjectiv;
extern PFNGLGETQUERYOBJECTUIVPROC       glGetQueryObjectuiv;
extern PFNGLBINDBUFFERPROC              glBindBuffer;
extern PFNGLDELETEBUFFERSPROC           glDeleteBuffers;
extern PFNGLGENBUFFERSPROC              glGenBuffers;
extern PFNGLISBUFFERPROC                glIsBuffer;
extern PFNGLBUFFERDATAPROC              glBufferData;
extern PFNGLBUFFERSUBDATAPROC           glBufferSubData;
extern PFNGLGETBUFFERSUBDATAPROC        glGetBufferSubData;
extern PFNGLMAPBUFFERPROC               glMapBuffer;
extern PFNGLUNMAPBUFFERPROC             glUnmapBuffer;
extern PFNGLGETBUFFERPARAMETERIVPROC    glGetBufferParameteriv;
extern PFNGLGETBUFFERPOINTERVPROC       glGetBufferPointerv;


/*
========================================================
                       OpenGL_2_0
========================================================
*/
#define GL_BLEND_EQUATION_RGB                  0x8009
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED         0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE            0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE          0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE            0x8625
#define GL_CURRENT_VERTEX_ATTRIB               0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE           0x8642
#define GL_VERTEX_ATTRIB_ARRAY_POINTER         0x8645
#define GL_STENCIL_BACK_FUNC                   0x8800
#define GL_STENCIL_BACK_FAIL                   0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL        0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS        0x8803
#define GL_MAX_DRAW_BUFFERS                    0x8824
#define GL_DRAW_BUFFER0                        0x8825
#define GL_DRAW_BUFFER1                        0x8826
#define GL_DRAW_BUFFER2                        0x8827
#define GL_DRAW_BUFFER3                        0x8828
#define GL_DRAW_BUFFER4                        0x8829
#define GL_DRAW_BUFFER5                        0x882A
#define GL_DRAW_BUFFER6                        0x882B
#define GL_DRAW_BUFFER7                        0x882C
#define GL_DRAW_BUFFER8                        0x882D
#define GL_DRAW_BUFFER9                        0x882E
#define GL_DRAW_BUFFER10                       0x882F
#define GL_DRAW_BUFFER11                       0x8830
#define GL_DRAW_BUFFER12                       0x8831
#define GL_DRAW_BUFFER13                       0x8832
#define GL_DRAW_BUFFER14                       0x8833
#define GL_DRAW_BUFFER15                       0x8834
#define GL_BLEND_EQUATION_ALPHA                0x883D
#define GL_MAX_VERTEX_ATTRIBS                  0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED      0x886A
#define GL_MAX_TEXTURE_IMAGE_UNITS             0x8872
#define GL_FRAGMENT_SHADER                     0x8B30
#define GL_VERTEX_SHADER                       0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS     0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS       0x8B4A
#define GL_MAX_VARYING_FLOATS                  0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS      0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS    0x8B4D
#define GL_SHADER_TYPE                         0x8B4F
#define GL_FLOAT_VEC2                          0x8B50
#define GL_FLOAT_VEC3                          0x8B51
#define GL_FLOAT_VEC4                          0x8B52
#define GL_INT_VEC2                            0x8B53
#define GL_INT_VEC3                            0x8B54
#define GL_INT_VEC4                            0x8B55
#define GL_BOOL                                0x8B56
#define GL_BOOL_VEC2                           0x8B57
#define GL_BOOL_VEC3                           0x8B58
#define GL_BOOL_VEC4                           0x8B59
#define GL_FLOAT_MAT2                          0x8B5A
#define GL_FLOAT_MAT3                          0x8B5B
#define GL_FLOAT_MAT4                          0x8B5C
#define GL_SAMPLER_1D                          0x8B5D
#define GL_SAMPLER_2D                          0x8B5E
#define GL_SAMPLER_3D                          0x8B5F
#define GL_SAMPLER_CUBE                        0x8B60
#define GL_SAMPLER_1D_SHADOW                   0x8B61
#define GL_SAMPLER_2D_SHADOW                   0x8B62
#define GL_DELETE_STATUS                       0x8B80
#define GL_COMPILE_STATUS                      0x8B81
#define GL_LINK_STATUS                         0x8B82
#define GL_VALIDATE_STATUS                     0x8B83
#define GL_INFO_LOG_LENGTH                     0x8B84
#define GL_ATTACHED_SHADERS                    0x8B85
#define GL_ACTIVE_UNIFORMS                     0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH           0x8B87
#define GL_SHADER_SOURCE_LENGTH                0x8B88
#define GL_ACTIVE_ATTRIBUTES                   0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH         0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT     0x8B8B
#define GL_SHADING_LANGUAGE_VERSION            0x8B8C
#define GL_CURRENT_PROGRAM                     0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN           0x8CA0
#define GL_LOWER_LEFT                          0x8CA1
#define GL_UPPER_LEFT                          0x8CA2
#define GL_STENCIL_BACK_REF                    0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK             0x8CA4
#define GL_STENCIL_BACK_WRITEMASK              0x8CA5


typedef void (GL3_APIENTRYP PFNGLBLENDEQUATIONSEPARATEPROC)(GLenum, GLenum);
typedef void (GL3_APIENTRYP PFNGLDRAWBUFFERSPROC)(GLsizei, const GLenum*);
typedef void (GL3_APIENTRYP PFNGLSTENCILOPSEPARATEPROC)(GLenum, GLenum, GLenum, GLenum);
typedef void (GL3_APIENTRYP PFNGLSTENCILFUNCSEPARATEPROC)(GLenum, GLenum, GLint, GLuint);
typedef void (GL3_APIENTRYP PFNGLSTENCILMASKSEPARATEPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLATTACHSHADERPROC)(GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLBINDATTRIBLOCATIONPROC)(GLuint, GLuint, const GLchar*);
typedef void (GL3_APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint);
typedef GLuint(GL3_APIENTRYP PFNGLCREATEPROGRAMPROC)();
typedef GLuint(GL3_APIENTRYP PFNGLCREATESHADERPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLDELETEPROGRAMPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLDELETESHADERPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLDETACHSHADERPROC)(GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLDISABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLGETACTIVEATTRIBPROC)(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (GL3_APIENTRYP PFNGLGETACTIVEUNIFORMPROC)(GLuint, GLuint, GLsizei, GLsizei*, GLint*, GLenum*, GLchar*);
typedef void (GL3_APIENTRYP PFNGLGETATTACHEDSHADERSPROC)(GLuint, GLsizei, GLsizei*, GLuint*);
typedef GLint(GL3_APIENTRYP PFNGLGETATTRIBLOCATIONPROC)(GLuint, const GLchar*);
typedef void (GL3_APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GL3_APIENTRYP PFNGLGETSHADERIVPROC)(GLuint, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef void (GL3_APIENTRYP PFNGLGETSHADERSOURCEPROC)(GLuint, GLsizei, GLsizei*, GLchar*);
typedef GLint(GL3_APIENTRYP PFNGLGETUNIFORMLOCATIONPROC)(GLuint, const GLchar*);
typedef void (GL3_APIENTRYP PFNGLGETUNIFORMFVPROC)(GLuint, GLint, GLfloat*);
typedef void (GL3_APIENTRYP PFNGLGETUNIFORMIVPROC)(GLuint, GLint, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETVERTEXATTRIBDVPROC)(GLuint, GLenum, GLdouble*);
typedef void (GL3_APIENTRYP PFNGLGETVERTEXATTRIBFVPROC)(GLuint, GLenum, GLfloat*);
typedef void (GL3_APIENTRYP PFNGLGETVERTEXATTRIBIVPROC)(GLuint, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETVERTEXATTRIBPOINTERVPROC)(GLuint, GLenum, GLvoid**);
typedef GLboolean(GL3_APIENTRYP PFNGLISPROGRAMPROC)(GLuint);
typedef GLboolean(GL3_APIENTRYP PFNGLISSHADERPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint, GLsizei, const GLchar**, const GLint*);
typedef void (GL3_APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM1FPROC)(GLint, GLfloat);
typedef void (GL3_APIENTRYP PFNGLUNIFORM2FPROC)(GLint, GLfloat, GLfloat);
typedef void (GL3_APIENTRYP PFNGLUNIFORM3FPROC)(GLint, GLfloat, GLfloat, GLfloat);
typedef void (GL3_APIENTRYP PFNGLUNIFORM4FPROC)(GLint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GL3_APIENTRYP PFNGLUNIFORM1IPROC)(GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM2IPROC)(GLint, GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM3IPROC)(GLint, GLint, GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM4IPROC)(GLint, GLint, GLint, GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM1FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM2FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM3FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM4FVPROC)(GLint, GLsizei, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM1IVPROC)(GLint, GLsizei, const GLint*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM2IVPROC)(GLint, GLsizei, const GLint*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM3IVPROC)(GLint, GLsizei, const GLint*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM4IVPROC)(GLint, GLsizei, const GLint*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLVALIDATEPROGRAMPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB1DPROC)(GLuint, GLdouble);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB1DVPROC)(GLuint, const GLdouble*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB1FPROC)(GLuint, GLfloat);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB1FVPROC)(GLuint, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB1SPROC)(GLuint, GLshort);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB1SVPROC)(GLuint, const GLshort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB2DPROC)(GLuint, GLdouble, GLdouble);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB2DVPROC)(GLuint, const GLdouble*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB2FPROC)(GLuint, GLfloat, GLfloat);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB2FVPROC)(GLuint, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB2SPROC)(GLuint, GLshort, GLshort);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB2SVPROC)(GLuint, const GLshort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB3DPROC)(GLuint, GLdouble, GLdouble, GLdouble);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB3DVPROC)(GLuint, const GLdouble*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB3FPROC)(GLuint, GLfloat, GLfloat, GLfloat);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB3FVPROC)(GLuint, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB3SPROC)(GLuint, GLshort, GLshort, GLshort);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB3SVPROC)(GLuint, const GLshort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4NBVPROC)(GLuint, const GLbyte*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4NIVPROC)(GLuint, const GLint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4NSVPROC)(GLuint, const GLshort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4NUBPROC)(GLuint, GLubyte, GLubyte, GLubyte, GLubyte);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4NUBVPROC)(GLuint, const GLubyte*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4NUIVPROC)(GLuint, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4NUSVPROC)(GLuint, const GLushort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4BVPROC)(GLuint, const GLbyte*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4DPROC)(GLuint, GLdouble, GLdouble, GLdouble, GLdouble);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4DVPROC)(GLuint, const GLdouble*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4FPROC)(GLuint, GLfloat, GLfloat, GLfloat, GLfloat);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4FVPROC)(GLuint, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4IVPROC)(GLuint, const GLint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4SPROC)(GLuint, GLshort, GLshort, GLshort, GLshort);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4SVPROC)(GLuint, const GLshort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4UBVPROC)(GLuint, const GLubyte*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4UIVPROC)(GLuint, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIB4USVPROC)(GLuint, const GLushort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint, GLint, GLenum, GLboolean, GLsizei, const GLvoid*);


extern PFNGLBLENDEQUATIONSEPARATEPROC       glBlendEquationSeparate;
extern PFNGLDRAWBUFFERSPROC                 glDrawBuffers;
extern PFNGLSTENCILOPSEPARATEPROC           glStencilOpSeparate;
extern PFNGLSTENCILFUNCSEPARATEPROC         glStencilFuncSeparate;
extern PFNGLSTENCILMASKSEPARATEPROC         glStencilMaskSeparate;
extern PFNGLATTACHSHADERPROC                glAttachShader;
extern PFNGLBINDATTRIBLOCATIONPROC          glBindAttribLocation;
extern PFNGLCOMPILESHADERPROC               glCompileShader;
extern PFNGLCREATEPROGRAMPROC               glCreateProgram;
extern PFNGLCREATESHADERPROC                glCreateShader;
extern PFNGLDELETEPROGRAMPROC               glDeleteProgram;
extern PFNGLDELETESHADERPROC                glDeleteShader;
extern PFNGLDETACHSHADERPROC                glDetachShader;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC    glDisableVertexAttribArray;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC     glEnableVertexAttribArray;
extern PFNGLGETACTIVEATTRIBPROC             glGetActiveAttrib;
extern PFNGLGETACTIVEUNIFORMPROC            glGetActiveUniform;
extern PFNGLGETATTACHEDSHADERSPROC          glGetAttachedShaders;
extern PFNGLGETATTRIBLOCATIONPROC           glGetAttribLocation;
extern PFNGLGETPROGRAMIVPROC                glGetProgramiv;
extern PFNGLGETPROGRAMINFOLOGPROC           glGetProgramInfoLog;
extern PFNGLGETSHADERIVPROC                 glGetShaderiv;
extern PFNGLGETSHADERINFOLOGPROC            glGetShaderInfoLog;
extern PFNGLGETSHADERSOURCEPROC             glGetShaderSource;
extern PFNGLGETUNIFORMLOCATIONPROC          glGetUniformLocation;
extern PFNGLGETUNIFORMFVPROC                glGetUniformfv;
extern PFNGLGETUNIFORMIVPROC                glGetUniformiv;
extern PFNGLGETVERTEXATTRIBDVPROC           glGetVertexAttribdv;
extern PFNGLGETVERTEXATTRIBFVPROC           glGetVertexAttribfv;
extern PFNGLGETVERTEXATTRIBIVPROC           glGetVertexAttribiv;
extern PFNGLGETVERTEXATTRIBPOINTERVPROC     glGetVertexAttribPointerv;
extern PFNGLISPROGRAMPROC                   glIsProgram;
extern PFNGLISSHADERPROC                    glIsShader;
extern PFNGLLINKPROGRAMPROC                 glLinkProgram;
extern PFNGLSHADERSOURCEPROC                glShaderSource;
extern PFNGLUSEPROGRAMPROC                  glUseProgram;
extern PFNGLUNIFORM1FPROC                   glUniform1f;
extern PFNGLUNIFORM2FPROC                   glUniform2f;
extern PFNGLUNIFORM3FPROC                   glUniform3f;
extern PFNGLUNIFORM4FPROC                   glUniform4f;
extern PFNGLUNIFORM1IPROC                   glUniform1i;
extern PFNGLUNIFORM2IPROC                   glUniform2i;
extern PFNGLUNIFORM3IPROC                   glUniform3i;
extern PFNGLUNIFORM4IPROC                   glUniform4i;
extern PFNGLUNIFORM1FVPROC                  glUniform1fv;
extern PFNGLUNIFORM2FVPROC                  glUniform2fv;
extern PFNGLUNIFORM3FVPROC                  glUniform3fv;
extern PFNGLUNIFORM4FVPROC                  glUniform4fv;
extern PFNGLUNIFORM1IVPROC                  glUniform1iv;
extern PFNGLUNIFORM2IVPROC                  glUniform2iv;
extern PFNGLUNIFORM3IVPROC                  glUniform3iv;
extern PFNGLUNIFORM4IVPROC                  glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC            glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC            glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC            glUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC             glValidateProgram;
extern PFNGLVERTEXATTRIB1DPROC              glVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC             glVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC              glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC             glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC              glVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC             glVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC              glVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC             glVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC              glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC             glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC              glVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC             glVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC              glVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC             glVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC              glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC             glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC              glVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC             glVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC            glVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC            glVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC            glVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC            glVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC           glVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC           glVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC           glVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC             glVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC              glVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC             glVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC              glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC             glVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC             glVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC              glVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC             glVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC            glVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC            glVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC            glVertexAttrib4usv;
extern PFNGLVERTEXATTRIBPOINTERPROC         glVertexAttribPointer;


/*
========================================================
                       OpenGL_2_1
========================================================
*/
#define GL_PIXEL_PACK_BUFFER              0x88EB
#define GL_PIXEL_UNPACK_BUFFER            0x88EC
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#define GL_PIXEL_UNPACK_BUFFER_BINDING    0x88EF
#define GL_FLOAT_MAT2x3                   0x8B65
#define GL_FLOAT_MAT2x4                   0x8B66
#define GL_FLOAT_MAT3x2                   0x8B67
#define GL_FLOAT_MAT3x4                   0x8B68
#define GL_FLOAT_MAT4x2                   0x8B69
#define GL_FLOAT_MAT4x3                   0x8B6A
#define GL_SRGB                           0x8C40
#define GL_SRGB8                          0x8C41
#define GL_SRGB_ALPHA                     0x8C42
#define GL_SRGB8_ALPHA8                   0x8C43
#define GL_COMPRESSED_SRGB                0x8C48
#define GL_COMPRESSED_SRGB_ALPHA          0x8C49


typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX2X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX3X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX2X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX4X2FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX3X4FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLUNIFORMMATRIX4X3FVPROC)(GLint, GLsizei, GLboolean, const GLfloat*);


extern PFNGLUNIFORMMATRIX2X3FVPROC    glUniformMatrix2x3fv;
extern PFNGLUNIFORMMATRIX3X2FVPROC    glUniformMatrix3x2fv;
extern PFNGLUNIFORMMATRIX2X4FVPROC    glUniformMatrix2x4fv;
extern PFNGLUNIFORMMATRIX4X2FVPROC    glUniformMatrix4x2fv;
extern PFNGLUNIFORMMATRIX3X4FVPROC    glUniformMatrix3x4fv;
extern PFNGLUNIFORMMATRIX4X3FVPROC    glUniformMatrix4x3fv;


/*
========================================================
                       OpenGL_3_0
========================================================
*/
#define GL_COMPARE_REF_TO_TEXTURE                           0x884E
#define GL_CLIP_DISTANCE0                                   0x3000
#define GL_CLIP_DISTANCE1                                   0x3001
#define GL_CLIP_DISTANCE2                                   0x3002
#define GL_CLIP_DISTANCE3                                   0x3003
#define GL_CLIP_DISTANCE4                                   0x3004
#define GL_CLIP_DISTANCE5                                   0x3005
#define GL_CLIP_DISTANCE6                                   0x3006
#define GL_CLIP_DISTANCE7                                   0x3007
#define GL_MAX_CLIP_DISTANCES                               0x0D32
#define GL_MAJOR_VERSION                                    0x821B
#define GL_MINOR_VERSION                                    0x821C
#define GL_NUM_EXTENSIONS                                   0x821D
#define GL_CONTEXT_FLAGS                                    0x821E
#define GL_DEPTH_BUFFER                                     0x8223
#define GL_STENCIL_BUFFER                                   0x8224
#define GL_COMPRESSED_RED                                   0x8225
#define GL_COMPRESSED_RG                                    0x8226
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT              0x0001
#define GL_RGBA32F                                          0x8814
#define GL_RGB32F                                           0x8815
#define GL_RGBA16F                                          0x881A
#define GL_RGB16F                                           0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER                      0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS                         0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET                         0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET                         0x8905
#define GL_CLAMP_READ_COLOR                                 0x891C
#define GL_FIXED_ONLY                                       0x891D
#define GL_MAX_VARYING_COMPONENTS                           0x8B4B
#define GL_TEXTURE_1D_ARRAY                                 0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY                           0x8C19
#define GL_TEXTURE_2D_ARRAY                                 0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY                           0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY                         0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY                         0x8C1D
#define GL_R11F_G11F_B10F                                   0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV                     0x8C3B
#define GL_RGB9_E5                                          0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV                         0x8C3E
#define GL_TEXTURE_SHARED_SIZE                              0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH            0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE                   0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS       0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS                      0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START                  0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE                   0x8C85
#define GL_PRIMITIVES_GENERATED                             0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN            0x8C88
#define GL_RASTERIZER_DISCARD                               0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS    0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS          0x8C8B
#define GL_INTERLEAVED_ATTRIBS                              0x8C8C
#define GL_SEPARATE_ATTRIBS                                 0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER                        0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING                0x8C8F
#define GL_RGBA32UI                                         0x8D70
#define GL_RGB32UI                                          0x8D71
#define GL_RGBA16UI                                         0x8D76
#define GL_RGB16UI                                          0x8D77
#define GL_RGBA8UI                                          0x8D7C
#define GL_RGB8UI                                           0x8D7D
#define GL_RGBA32I                                          0x8D82
#define GL_RGB32I                                           0x8D83
#define GL_RGBA16I                                          0x8D88
#define GL_RGB16I                                           0x8D89
#define GL_RGBA8I                                           0x8D8E
#define GL_RGB8I                                            0x8D8F
#define GL_RED_INTEGER                                      0x8D94
#define GL_GREEN_INTEGER                                    0x8D95
#define GL_BLUE_INTEGER                                     0x8D96
#define GL_RGB_INTEGER                                      0x8D98
#define GL_RGBA_INTEGER                                     0x8D99
#define GL_BGR_INTEGER                                      0x8D9A
#define GL_BGRA_INTEGER                                     0x8D9B
#define GL_SAMPLER_1D_ARRAY                                 0x8DC0
#define GL_SAMPLER_2D_ARRAY                                 0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW                          0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW                          0x8DC4
#define GL_SAMPLER_CUBE_SHADOW                              0x8DC5
#define GL_UNSIGNED_INT_VEC2                                0x8DC6
#define GL_UNSIGNED_INT_VEC3                                0x8DC7
#define GL_UNSIGNED_INT_VEC4                                0x8DC8
#define GL_INT_SAMPLER_1D                                   0x8DC9
#define GL_INT_SAMPLER_2D                                   0x8DCA
#define GL_INT_SAMPLER_3D                                   0x8DCB
#define GL_INT_SAMPLER_CUBE                                 0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY                             0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY                             0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D                          0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D                          0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D                          0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE                        0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY                    0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY                    0x8DD7
#define GL_QUERY_WAIT                                       0x8E13
#define GL_QUERY_NO_WAIT                                    0x8E14
#define GL_QUERY_BY_REGION_WAIT                             0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT                          0x8E16
#define GL_BUFFER_ACCESS_FLAGS                              0x911F
#define GL_BUFFER_MAP_LENGTH                                0x9120
#define GL_BUFFER_MAP_OFFSET                                0x9121


typedef void (GL3_APIENTRYP PFNGLCOLORMASKIPROC)(GLuint, GLboolean, GLboolean, GLboolean, GLboolean);
typedef void (GL3_APIENTRYP PFNGLGETBOOLEANI_VPROC)(GLenum, GLuint, GLboolean*);
typedef void (GL3_APIENTRYP PFNGLGETINTEGERI_VPROC)(GLenum, GLuint, GLint*);
typedef void (GL3_APIENTRYP PFNGLENABLEIPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLDISABLEIPROC)(GLenum, GLuint);
typedef GLboolean(GL3_APIENTRYP PFNGLISENABLEDIPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLBEGINTRANSFORMFEEDBACKPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLENDTRANSFORMFEEDBACKPROC)();
typedef void (GL3_APIENTRYP PFNGLBINDBUFFERRANGEPROC)(GLenum, GLuint, GLuint, GLintptr, GLsizeiptr);
typedef void (GL3_APIENTRYP PFNGLBINDBUFFERBASEPROC)(GLenum, GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLTRANSFORMFEEDBACKVARYINGSPROC)(GLuint, GLsizei, const GLchar**, GLenum);
typedef void (GL3_APIENTRYP PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)(GLuint, GLuint, GLsizei, GLsizei*, GLsizei*, GLenum*, GLchar*);
typedef void (GL3_APIENTRYP PFNGLCLAMPCOLORPROC)(GLenum, GLenum);
typedef void (GL3_APIENTRYP PFNGLBEGINCONDITIONALRENDERPROC)(GLuint, GLenum);
typedef void (GL3_APIENTRYP PFNGLENDCONDITIONALRENDERPROC)();
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBIPOINTERPROC)(GLuint, GLint, GLenum, GLsizei, const GLvoid*);
typedef void (GL3_APIENTRYP PFNGLGETVERTEXATTRIBIIVPROC)(GLuint, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETVERTEXATTRIBIUIVPROC)(GLuint, GLenum, GLuint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI1IPROC)(GLuint, GLint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI2IPROC)(GLuint, GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI3IPROC)(GLuint, GLint, GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4IPROC)(GLuint, GLint, GLint, GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI1UIPROC)(GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI2UIPROC)(GLuint, GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI3UIPROC)(GLuint, GLuint, GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4UIPROC)(GLuint, GLuint, GLuint, GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI1IVPROC)(GLuint, const GLint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI2IVPROC)(GLuint, const GLint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI3IVPROC)(GLuint, const GLint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4IVPROC)(GLuint, const GLint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI1UIVPROC)(GLuint, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI2UIVPROC)(GLuint, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI3UIVPROC)(GLuint, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4UIVPROC)(GLuint, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4BVPROC)(GLuint, const GLbyte*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4SVPROC)(GLuint, const GLshort*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4UBVPROC)(GLuint, const GLubyte*);
typedef void (GL3_APIENTRYP PFNGLVERTEXATTRIBI4USVPROC)(GLuint, const GLushort*);
typedef void (GL3_APIENTRYP PFNGLGETUNIFORMUIVPROC)(GLuint, GLint, GLuint*);
typedef void (GL3_APIENTRYP PFNGLBINDFRAGDATALOCATIONPROC)(GLuint, GLuint, const GLchar*);
typedef GLint(GL3_APIENTRYP PFNGLGETFRAGDATALOCATIONPROC)(GLuint, const GLchar*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM1UIPROC)(GLint, GLuint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM2UIPROC)(GLint, GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM3UIPROC)(GLint, GLuint, GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM4UIPROC)(GLint, GLuint, GLuint, GLuint, GLuint);
typedef void (GL3_APIENTRYP PFNGLUNIFORM1UIVPROC)(GLint, GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM2UIVPROC)(GLint, GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM3UIVPROC)(GLint, GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLUNIFORM4UIVPROC)(GLint, GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLTEXPARAMETERIIVPROC)(GLenum, GLenum, const GLint*);
typedef void (GL3_APIENTRYP PFNGLTEXPARAMETERIUIVPROC)(GLenum, GLenum, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLGETTEXPARAMETERIIVPROC)(GLenum, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGETTEXPARAMETERIUIVPROC)(GLenum, GLenum, GLuint*);
typedef void (GL3_APIENTRYP PFNGLCLEARBUFFERIVPROC)(GLenum, GLint, const GLint*);
typedef void (GL3_APIENTRYP PFNGLCLEARBUFFERUIVPROC)(GLenum, GLint, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLCLEARBUFFERFVPROC)(GLenum, GLint, const GLfloat*);
typedef void (GL3_APIENTRYP PFNGLCLEARBUFFERFIPROC)(GLenum, GLint, GLfloat, GLint);
typedef const GLubyte* (GL3_APIENTRYP PFNGLGETSTRINGIPROC)(GLenum, GLuint);


extern PFNGLCOLORMASKIPROC                     glColorMaski;
extern PFNGLGETBOOLEANI_VPROC                  glGetBooleani_v;
extern PFNGLGETINTEGERI_VPROC                  glGetIntegeri_v;
extern PFNGLENABLEIPROC                        glEnablei;
extern PFNGLDISABLEIPROC                       glDisablei;
extern PFNGLISENABLEDIPROC                     glIsEnabledi;
extern PFNGLBEGINTRANSFORMFEEDBACKPROC         glBeginTransformFeedback;
extern PFNGLENDTRANSFORMFEEDBACKPROC           glEndTransformFeedback;
extern PFNGLBINDBUFFERRANGEPROC                glBindBufferRange;
extern PFNGLBINDBUFFERBASEPROC                 glBindBufferBase;
extern PFNGLTRANSFORMFEEDBACKVARYINGSPROC      glTransformFeedbackVaryings;
extern PFNGLGETTRANSFORMFEEDBACKVARYINGPROC    glGetTransformFeedbackVarying;
extern PFNGLCLAMPCOLORPROC                     glClampColor;
extern PFNGLBEGINCONDITIONALRENDERPROC         glBeginConditionalRender;
extern PFNGLENDCONDITIONALRENDERPROC           glEndConditionalRender;
extern PFNGLVERTEXATTRIBIPOINTERPROC           glVertexAttribIPointer;
extern PFNGLGETVERTEXATTRIBIIVPROC             glGetVertexAttribIiv;
extern PFNGLGETVERTEXATTRIBIUIVPROC            glGetVertexAttribIuiv;
extern PFNGLVERTEXATTRIBI1IPROC                glVertexAttribI1i;
extern PFNGLVERTEXATTRIBI2IPROC                glVertexAttribI2i;
extern PFNGLVERTEXATTRIBI3IPROC                glVertexAttribI3i;
extern PFNGLVERTEXATTRIBI4IPROC                glVertexAttribI4i;
extern PFNGLVERTEXATTRIBI1UIPROC               glVertexAttribI1ui;
extern PFNGLVERTEXATTRIBI2UIPROC               glVertexAttribI2ui;
extern PFNGLVERTEXATTRIBI3UIPROC               glVertexAttribI3ui;
extern PFNGLVERTEXATTRIBI4UIPROC               glVertexAttribI4ui;
extern PFNGLVERTEXATTRIBI1IVPROC               glVertexAttribI1iv;
extern PFNGLVERTEXATTRIBI2IVPROC               glVertexAttribI2iv;
extern PFNGLVERTEXATTRIBI3IVPROC               glVertexAttribI3iv;
extern PFNGLVERTEXATTRIBI4IVPROC               glVertexAttribI4iv;
extern PFNGLVERTEXATTRIBI1UIVPROC              glVertexAttribI1uiv;
extern PFNGLVERTEXATTRIBI2UIVPROC              glVertexAttribI2uiv;
extern PFNGLVERTEXATTRIBI3UIVPROC              glVertexAttribI3uiv;
extern PFNGLVERTEXATTRIBI4UIVPROC              glVertexAttribI4uiv;
extern PFNGLVERTEXATTRIBI4BVPROC               glVertexAttribI4bv;
extern PFNGLVERTEXATTRIBI4SVPROC               glVertexAttribI4sv;
extern PFNGLVERTEXATTRIBI4UBVPROC              glVertexAttribI4ubv;
extern PFNGLVERTEXATTRIBI4USVPROC              glVertexAttribI4usv;
extern PFNGLGETUNIFORMUIVPROC                  glGetUniformuiv;
extern PFNGLBINDFRAGDATALOCATIONPROC           glBindFragDataLocation;
extern PFNGLGETFRAGDATALOCATIONPROC            glGetFragDataLocation;
extern PFNGLUNIFORM1UIPROC                     glUniform1ui;
extern PFNGLUNIFORM2UIPROC                     glUniform2ui;
extern PFNGLUNIFORM3UIPROC                     glUniform3ui;
extern PFNGLUNIFORM4UIPROC                     glUniform4ui;
extern PFNGLUNIFORM1UIVPROC                    glUniform1uiv;
extern PFNGLUNIFORM2UIVPROC                    glUniform2uiv;
extern PFNGLUNIFORM3UIVPROC                    glUniform3uiv;
extern PFNGLUNIFORM4UIVPROC                    glUniform4uiv;
extern PFNGLTEXPARAMETERIIVPROC                glTexParameterIiv;
extern PFNGLTEXPARAMETERIUIVPROC               glTexParameterIuiv;
extern PFNGLGETTEXPARAMETERIIVPROC             glGetTexParameterIiv;
extern PFNGLGETTEXPARAMETERIUIVPROC            glGetTexParameterIuiv;
extern PFNGLCLEARBUFFERIVPROC                  glClearBufferiv;
extern PFNGLCLEARBUFFERUIVPROC                 glClearBufferuiv;
extern PFNGLCLEARBUFFERFVPROC                  glClearBufferfv;
extern PFNGLCLEARBUFFERFIPROC                  glClearBufferfi;
extern PFNGLGETSTRINGIPROC                     glGetStringi;


/*
========================================================
               GL_ARB_vertex_array_object
========================================================
*/
#define GL_VERTEX_ARRAY_BINDING    0x85B5


typedef void (GL3_APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLDELETEVERTEXARRAYSPROC)(GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei, GLuint*);
typedef GLboolean(GL3_APIENTRYP PFNGLISVERTEXARRAYPROC)(GLuint);


extern PFNGLBINDVERTEXARRAYPROC       glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC    glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC       glGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC         glIsVertexArray;




/*
========================================================
                GL_ARB_framebuffer_object
========================================================
*/
#define GL_INVALID_FRAMEBUFFER_OPERATION                   0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING           0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE           0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE                 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE               0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE                0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE               0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE               0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE             0x8217
#define GL_FRAMEBUFFER_DEFAULT                             0x8218
#define GL_FRAMEBUFFER_UNDEFINED                           0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT                        0x821A
#define GL_MAX_RENDERBUFFER_SIZE                           0x84E8
#define GL_DEPTH_STENCIL                                   0x84F9
#define GL_UNSIGNED_INT_24_8                               0x84FA
#define GL_DEPTH24_STENCIL8                                0x88F0
#define GL_TEXTURE_STENCIL_SIZE                            0x88F1
#define GL_TEXTURE_RED_TYPE                                0x8C10
#define GL_TEXTURE_GREEN_TYPE                              0x8C11
#define GL_TEXTURE_BLUE_TYPE                               0x8C12
#define GL_TEXTURE_ALPHA_TYPE                              0x8C13
#define GL_TEXTURE_DEPTH_TYPE                              0x8C16
#define GL_UNSIGNED_NORMALIZED                             0x8C17
#define GL_FRAMEBUFFER_BINDING                             0x8CA6
#define GL_DRAW_FRAMEBUFFER_BINDING                        GL_FRAMEBUFFER_BINDING
#define GL_RENDERBUFFER_BINDING                            0x8CA7
#define GL_READ_FRAMEBUFFER                                0x8CA8
#define GL_DRAW_FRAMEBUFFER                                0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING                        0x8CAA
#define GL_RENDERBUFFER_SAMPLES                            0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE              0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME              0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL            0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE    0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER            0x8CD4
#define GL_FRAMEBUFFER_COMPLETE                            0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT               0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT       0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER              0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER              0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED                         0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS                           0x8CDF
#define GL_COLOR_ATTACHMENT0                               0x8CE0
#define GL_COLOR_ATTACHMENT1                               0x8CE1
#define GL_COLOR_ATTACHMENT2                               0x8CE2
#define GL_COLOR_ATTACHMENT3                               0x8CE3
#define GL_COLOR_ATTACHMENT4                               0x8CE4
#define GL_COLOR_ATTACHMENT5                               0x8CE5
#define GL_COLOR_ATTACHMENT6                               0x8CE6
#define GL_COLOR_ATTACHMENT7                               0x8CE7
#define GL_COLOR_ATTACHMENT8                               0x8CE8
#define GL_COLOR_ATTACHMENT9                               0x8CE9
#define GL_COLOR_ATTACHMENT10                              0x8CEA
#define GL_COLOR_ATTACHMENT11                              0x8CEB
#define GL_COLOR_ATTACHMENT12                              0x8CEC
#define GL_COLOR_ATTACHMENT13                              0x8CED
#define GL_COLOR_ATTACHMENT14                              0x8CEE
#define GL_COLOR_ATTACHMENT15                              0x8CEF
#define GL_DEPTH_ATTACHMENT                                0x8D00
#define GL_STENCIL_ATTACHMENT                              0x8D20
#define GL_FRAMEBUFFER                                     0x8D40
#define GL_RENDERBUFFER                                    0x8D41
#define GL_RENDERBUFFER_WIDTH                              0x8D42
#define GL_RENDERBUFFER_HEIGHT                             0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT                    0x8D44
#define GL_STENCIL_INDEX1                                  0x8D46
#define GL_STENCIL_INDEX4                                  0x8D47
#define GL_STENCIL_INDEX8                                  0x8D48
#define GL_STENCIL_INDEX16                                 0x8D49
#define GL_RENDERBUFFER_RED_SIZE                           0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE                         0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE                          0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE                         0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE                         0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE                       0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE              0x8D56
#define GL_MAX_SAMPLES                                     0x8D57


typedef GLboolean(GL3_APIENTRYP PFNGLISRENDERBUFFERPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLBINDRENDERBUFFERPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLDELETERENDERBUFFERSPROC)(GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLGENRENDERBUFFERSPROC)(GLsizei, GLuint*);
typedef void (GL3_APIENTRYP PFNGLRENDERBUFFERSTORAGEPROC)(GLenum, GLenum, GLsizei, GLsizei);
typedef void (GL3_APIENTRYP PFNGLGETRENDERBUFFERPARAMETERIVPROC)(GLenum, GLenum, GLint*);
typedef GLboolean(GL3_APIENTRYP PFNGLISFRAMEBUFFERPROC)(GLuint);
typedef void (GL3_APIENTRYP PFNGLBINDFRAMEBUFFERPROC)(GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLDELETEFRAMEBUFFERSPROC)(GLsizei, const GLuint*);
typedef void (GL3_APIENTRYP PFNGLGENFRAMEBUFFERSPROC)(GLsizei, GLuint*);
typedef GLenum(GL3_APIENTRYP PFNGLCHECKFRAMEBUFFERSTATUSPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLFRAMEBUFFERTEXTURE1DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (GL3_APIENTRYP PFNGLFRAMEBUFFERTEXTURE2DPROC)(GLenum, GLenum, GLenum, GLuint, GLint);
typedef void (GL3_APIENTRYP PFNGLFRAMEBUFFERTEXTURE3DPROC)(GLenum, GLenum, GLenum, GLuint, GLint, GLint);
typedef void (GL3_APIENTRYP PFNGLFRAMEBUFFERRENDERBUFFERPROC)(GLenum, GLenum, GLenum, GLuint);
typedef void (GL3_APIENTRYP PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)(GLenum, GLenum, GLenum, GLint*);
typedef void (GL3_APIENTRYP PFNGLGENERATEMIPMAPPROC)(GLenum);
typedef void (GL3_APIENTRYP PFNGLBLITFRAMEBUFFERPROC)(GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLint, GLbitfield, GLenum);
typedef void (GL3_APIENTRYP PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)(GLenum, GLsizei, GLenum, GLsizei, GLsizei);
typedef void (GL3_APIENTRYP PFNGLFRAMEBUFFERTEXTURELAYERPROC)(GLenum, GLenum, GLuint, GLint, GLint);


extern PFNGLISRENDERBUFFERPROC                         glIsRenderbuffer;
extern PFNGLBINDRENDERBUFFERPROC                       glBindRenderbuffer;
extern PFNGLDELETERENDERBUFFERSPROC                    glDeleteRenderbuffers;
extern PFNGLGENRENDERBUFFERSPROC                       glGenRenderbuffers;
extern PFNGLRENDERBUFFERSTORAGEPROC                    glRenderbufferStorage;
extern PFNGLGETRENDERBUFFERPARAMETERIVPROC             glGetRenderbufferParameteriv;
extern PFNGLISFRAMEBUFFERPROC                          glIsFramebuffer;
extern PFNGLBINDFRAMEBUFFERPROC                        glBindFramebuffer;
extern PFNGLDELETEFRAMEBUFFERSPROC                     glDeleteFramebuffers;
extern PFNGLGENFRAMEBUFFERSPROC                        glGenFramebuffers;
extern PFNGLCHECKFRAMEBUFFERSTATUSPROC                 glCheckFramebufferStatus;
extern PFNGLFRAMEBUFFERTEXTURE1DPROC                   glFramebufferTexture1D;
extern PFNGLFRAMEBUFFERTEXTURE2DPROC                   glFramebufferTexture2D;
extern PFNGLFRAMEBUFFERTEXTURE3DPROC                   glFramebufferTexture3D;
extern PFNGLFRAMEBUFFERRENDERBUFFERPROC                glFramebufferRenderbuffer;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC    glGetFramebufferAttachmentParameteriv;
extern PFNGLGENERATEMIPMAPPROC                         glGenerateMipmap;
extern PFNGLBLITFRAMEBUFFERPROC                        glBlitFramebuffer;
extern PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC         glRenderbufferStorageMultisample;
extern PFNGLFRAMEBUFFERTEXTURELAYERPROC                glFramebufferTextureLayer;



typedef struct skOpenGLCapabilities
{
    bool skOpenGL_1_1;
    bool skOpenGL_1_2;
    bool skOpenGL_1_3;
    bool skOpenGL_1_4;
    bool skOpenGL_1_5;
    bool skOpenGL_2_0;
    bool skOpenGL_2_1;
    bool skOpenGL_3_0;
    bool skOpenGL_ARB_vertex_array_object;
    bool skOpenGL_ARB_framebuffer_object;
} skOpenGLCapabilities;


extern skOpenGLCapabilities* skGetOpenGLCapabilities(void);
extern bool skLoadOpenGL(void);

#endif//_skOpenGL_h_
