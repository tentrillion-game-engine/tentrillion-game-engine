cmake_minimum_required(VERSION 3.16.0)
set(PROJECT_NAME ten-trillion)
project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX)
# Definitions
set(TESTING_EXECUTABLE tentrillion-tentest)
set(EDITOR_EXECUTABLE tentrillion-editor)
set(LIBRARY_NAME tentrillion-game-engine)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_NO_SYSTEM_FROM_IMPORTED ON)

option(TENTRILLION_BACKEND_VULKAN "Use the Vulkan backend. Toggle OFF for OpenGL." ON)

file(GLOB LIBRARIES LIST_DIRECTORIES true RELATIVE ${CMAKE_SOURCE_DIR} "libs/*")
foreach (dir ${LIBRARIES})
    add_subdirectory(${dir} EXCLUDE_FROM_ALL)
endforeach (dir ${LIBRARIES})

include(GenerateExportHeader)
include(GNUInstallDirs)
include(CTest)
include(CMakePackageConfigHelpers)

add_subdirectory(src/lib)
add_subdirectory(src/editor)

# TenTrillion TenTEST Utility. This utility is used for testing the TenTrillion.

add_executable(${TESTING_EXECUTABLE} src/test/main.cpp)
target_link_libraries(${TESTING_EXECUTABLE} PUBLIC ${LIBRARY_NAME})