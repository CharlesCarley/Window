# Window

A small cross platform window library.

This is still largely a work in progress.  

## Current state

+ Win32 Native
+ X11 Native
+ SDL Windows, Linux

## Goals

+ Should be able to load, create and manage at least one toplevel window.
+ Handle all user input.
+ Setup OpenGL automatically.

## Building

Building with CMake

```txt
mkdir build
cd build
cmake ..
```

Optional defines.

+ Window_WITH_SDL - Build with support for SDL. Default: OFF
