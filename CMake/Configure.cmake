# -----------------------------------------------------------------------------
#
#   Copyright (c) Charles Carley.
#
#   This software is provided 'as-is', without any express or implied
# warranty. In no event will the authors be held liable for any damages
# arising from the use of this software.
#
#   Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
#
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
# ------------------------------------------------------------------------------
include(StaticRuntime)
set_static_runtime()

option(Window_USE_FOLDERS  "Use solution folders" ON)
option(Window_WITH_SDL     "Build with support for SDL" OFF)

if (Window_USE_FOLDERS)
    set_property(GLOBAL PROPERTY USE_FOLDERS ON)
    set(CMAKE_USE_FOLDERS TRUE)
endif()


set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL  QUIET REQUIRED)


set(Extern_PATH ${CMAKE_SOURCE_DIR}/Extern)

set(Utils_ExternalTarget TRUE)
set(Utils_TargetFolders  ${CMAKE_USE_FOLDERS})
set(Utils_TargetName     Utils)
set(Utils_TargetGroup    Extern)
set(Utils_INCLUDE        ${Extern_PATH})
set(Utils_LIBRARY        ${Utils_TargetName})

set(Window_ExternalTarget      False)
set(Window_TargetFolders       ${CMAKE_USE_FOLDERS})
set(Window_TargetName          Window)
set(Window_TargetGroup         Extern)
set(Window_INCLUDE             ${CMAKE_SOURCE_DIR} ${OPENGL_INCLUDE})


if (Window_WITH_SDL)
    set(SDL_FOLDER   ${Utils_TargetGroup})
    set(SDL_INCLUDE  ${Extern_PATH}/SDL/SDL)
    set(SDL_LIBRARY  SDL2main SDL2-static)
endif()

set(Extern_LIBS ${Utils_TargetName} ${Window_TargetName} ${OPENGL_LIBRARIES})
