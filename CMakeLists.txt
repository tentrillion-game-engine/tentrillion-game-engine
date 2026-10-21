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

option(TENTRILLION_COMPILE_VULKAN "Compiles the Vulkan TenTrillion API" ON) # This is the compiler option for Vulkan.
option(TENTRILLION_COMPILE_OPENGL "Compiles the OpenGL TenTrillion API" ON) # This is the compiler option for OpenGL.
option(TENTRILLION_COMPILE_COMPAT "Compiles the Compatibility TenTrillion API" ON) # This is the compiler option for compatibility.mode. This is a mode that allows
# Compatibility with tons of Windows platforms.

# Extra GLFW stuff so it doesn't build the documentation, because we don't need it.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw EXCLUDE_FROM_ALL)
add_subdirectory(libs/json EXCLUDE_FROM_ALL) 

set(TENTRILLION_SHARED_TARGETS
        shared/src/tentrillion_context.cpp
)

set(TENTRILLION_SHARED_LIBRARY "tentrillionshared")
add_library(${TENTRILLION_SHARED_LIBRARY} ${TENTRILLION_SHARED_TARGETS})
target_include_directories(${TENTRILLION_SHARED_LIBRARY} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/shared/include>
        $<BUILD_INTERFACE:$<$<BOOL:${TENTRILLION_COMPILE_VULKAN}>:${CMAKE_CURRENT_SOURCE_DIR}/vulkan/libs>> # Vulkan non-linked loading.
        $<BUILD_INTERFACE:$<$<BOOL:${TENTRILLION_COMPILE_OPENGL}>:${CMAKE_CURRENT_SOURCE_DIR}/opengl/libs>> # OpenGL non-linked loading.
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/opengl/libs>
        $<INSTALL_INTERFACE:shared/include>
)

if(${TENTRILLION_COMPILE_VULKAN})
add_subdirectory(vulkan)
endif()

if(${TENTRILLION_COMPILE_OPENGL})
add_subdirectory(opengl)
endif()
