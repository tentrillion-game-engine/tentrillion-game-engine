# TENTRILLION GAME ENGINE
# An extremely optimized game engine written
# from scratch in Vulkan, OpenGL, SDL and OpenAL.
#
# Copyright (c) 2026 Thefirey33

cmake_minimum_required(VERSION 3.16.0)
project(TenTrillionGameEngine VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 11)
include(GenerateExportHeader)
include(GNUInstallDirs)

option(TENTRILLION_COMPILE_VULKAN ON) # This is the compiler option for Vulkan.
option(TENTRILLION_COMPILE_OPENGL ON) # This is the compiler option for OpenGL.
option(TENTRILLION_COMPILE_COMPAT ON) # This is the compiler option for compatibility.mode. This is a mode that allows
# Compatibility with tons of Windows platforms.

# Extra GLFW stuff so it doesn't build the documentation, because we don't need it.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)
add_subdirectory(libs/json)

set(SHARED_TARGETS
    shared/src/tentrillion_window.cpp
)
