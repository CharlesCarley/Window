# -----------------------------------------------------------------------------
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
if (Window_ExternalTarget)
    set(TargetFolders ${Window_TargetFolders})
    set(TargetName    ${Window_TargetName})
    set(TargetGroup   ${Window_TargetGroup})
else()
    set(TargetFolders FALSE)
    set(TargetName Window)
    unset(TargetGroup )
endif()



set(Window_PLIB ${OPENGL_LIBRARY} ${Utils_LIBRARY} )
set(Window_PINC ${Utils_INCLUDE})
set(Window_PDEF )


if (Window_WITH_SDL)
    list(APPEND Window_PLIB ${SDL_LIBRARY})
    list(APPEND Window_PINC ${SDL_INCLUDE})
    list(APPEND Window_PDEF -DWITH_SDL)
endif()



set(Window_HDR
    skWindow.h
    skWindowEnums.h
    skWindowManager.h
    skWindowContext.h
    skWindowTypes.h
    skKeyboard.h
    skMouse.h
    skWindowHandler.h
    OpenGL/skOpenGL.h
    Inject/skWindowInject.h
    Inject/skWindowContextInject.h
)

set(Window_SRC
    skMouse.cpp
    skKeyboard.cpp
    skWindow.cpp
    skWindowHandler.cpp
    skWindowManager.cpp
    skWindowEnums.cpp
    OpenGL/skOpenGL.cpp
    Inject/skWindowInject.cpp
    Inject/skWindowContextInject.cpp
    
)

if (WIN32)

    set(Window_PLAT_SRC_NO_COMPILE 
        X11/skWindowX11.h
        X11/skWindowContextX11.h
        X11/skWindowX11.cpp
        X11/skWindowContextX11.cpp
    )

    set_source_files_properties(${Window_PLAT_SRC_NO_COMPILE} 
        PROPERTIES 
        VS_TOOL_OVERRIDE 
        "None")
    set_source_files_properties(${Window_PLAT_SRC_NO_COMPILE} 
        PROPERTIES 
        HEADER_FILE_ONLY 
        TRUE)

    set(Window_PLAT_SRC 
        Win32/skWindowWin32.h
        Win32/skWindowContextWin32.h
        Win32/skWindowWin32.cpp
        Win32/skWindowContextWin32.cpp
        ${Window_PLAT_SRC_NO_COMPILE}
    )

elseif (UNIX)

    find_package(X11  REQUIRED)



    list(APPEND Window_PINC ${X11_INCLUDE_DIR} )
    list(APPEND Window_PLIB ${X11_LIBRARIES} dl)

    set(Window_PLAT_SRC 
        X11/skWindowX11.h
        X11/skWindowContextX11.h
        X11/skWindowX11.cpp
        X11/skWindowContextX11.cpp
    )
endif()


if (Window_WITH_SDL)
    set(WindowSDL_PHDR
        SDL/skWindowSDL.h
        SDL/skWindowContextSDL.h
    )
    set(WindowSDL_PSRC
        SDL/skWindowSDL.cpp
        SDL/skWindowContextSDL.cpp
    )
    list(APPEND Window_PLAT_SRC ${WindowSDL_PHDR} ${WindowSDL_PSRC})
endif()

include_directories(.. . ${Window_PINC})
add_definitions(${Window_PDEF})

add_library(
    ${TargetName}
    ${Window_SRC} 
    ${Window_HDR}
    ${Window_PLAT_SRC}
)

target_link_libraries(
    ${TargetName} 
    ${Window_PLIB}
)

set_target_properties(${TargetName} PROPERTIES FOLDER "${TargetGroup}")
