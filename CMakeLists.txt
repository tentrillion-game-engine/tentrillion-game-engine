# TENTRILLION GAME ENGINE
# An extremely optimized game engine written
# from scratch in Vulkan, OpenGL, SDL and OpenAL.
#
# Copyright (c) 2026 Thefirey33

cmake_minimum_required(VERSION 3.16.0)
project(TenTrillionGameEngine VERSION 0.1.0 LANGUAGES CXX C)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(GenerateExportHeader)
include(ExternalProject)
include(GNUInstallDirs)

option(TENTRILLION_COMPILE_EDITOR "Compiles the TenTrillion Editor" ON)
option(TENTRILLION_COMPILE_VULKAN "Compiles the Vulkan TenTrillion API" ON)
option(TENTRILLION_COMPILE_OPENGL "Compiles the OpenGL TenTrillion API" ON)
option(TENTRILLION_COMPILE_COMPAT "Compiles the Compat. TenTrillion API" ON)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(libs/glfw EXCLUDE_FROM_ALL)
add_subdirectory(libs/json EXCLUDE_FROM_ALL)

set(TENTRILLION_SHARED_TARGETS
  ${CMAKE_SOURCE_DIR}/shared/src/tentrillion_context.cpp
  ${CMAKE_SOURCE_DIR}/shared/src/tentrillion_math.cpp
)

set(TENTRILLION_SHARED_INCLUDES
  $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/shared/include>
  $<INSTALL_INTERFACE:shared/include>
)

if(${TENTRILLION_COMPILE_VULKAN})
  add_subdirectory(vulkan)
endif()

if(${TENTRILLION_COMPILE_OPENGL})
  add_subdirectory(opengl)
endif()

if(${TENTRILLION_COMPILE_COMPAT})
  ExternalProject_Add(compatibility
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/compat
    DOWNLOAD_COMMAND ""
    BUILD_IN_SOURCE true
    CONFIGURE_COMMAND ""
    BUILD_COMMAND make
    INSTALL_COMMAND make install
  )
endif()

if(LINUX)
  if(${TENTRILLION_COMPILE_COMPAT} AND ${TENTRILLION_COMPILE_OPENGL} AND ${TENTRILLION_COMPILE_VULKAN})
    add_subdirectory(editor)
  endif()
elseif(WIN32)
# TODO
endif()

