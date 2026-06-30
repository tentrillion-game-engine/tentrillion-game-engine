# The TenTrillion Game Engine
# ENGINE Section
# This section contains the runtime for the TenTrillion Game Engine.

cmake_minimum_required(VERSION 3.16.0)
set(PROJECT_NAME TenTrillionGameEngine)
set(TENTEST_UTILITY_PROJECT_NAME TenTrillionTenTest)

project(${PROJECT_NAME} VERSION 0.1.0 LANGUAGES CXX C)
set(TENTRILLION_PACKAGE_NAME "tentrillionsdk")
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GenerateExportHeader)
include(GNUInstallDirs)

# Required dependencies for the TenTrillion's AUDIO, GRAPHICS and PROCESSING dependencies.
find_package(OpenGL REQUIRED)
find_package(OpenCL REQUIRED)
find_package(OpenAL REQUIRED)

add_subdirectory(libs/volk)
add_subdirectory(libs/Vulkan-Headers)

# Extra GLFW stuff so it doesn't build the documentation, because we don't need it.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(libs/glfw)

set(ENGINE_TARGETS
        src/tentrillion-game-engine.cpp
)

# Initialization of the TenTrillion Library.
add_library(${PROJECT_NAME} SHARED ${ENGINE_TARGETS})
generate_export_header(
        ${PROJECT_NAME}
        EXPORT_FILE_NAME "tentrillion-game-engine-export.h"
)
target_link_libraries(${PROJECT_NAME} PRIVATE
        volk
        OpenGL::GL
        OpenCL::OpenCL
        glfw
)
target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Add TenTrillion TenTest.
add_subdirectory(test)

install(TARGETS ${PROJECT_NAME}
        EXPORT TenTrillionTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(TARGETS ${TENTEST_UTILITY_PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES "LICENSE" DESTINATION .)

# CPack Configuration, for easy importing of the TenTrillion Game Engine libraries.
set(CPACK_PACKAGE_NAME " TenTrillion Game Engine SDK")
set(CPACK_PACKAGE_VENDOR "Thefirey33")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A highly optimized game engine using the Vulkan, OpenGL and other rendering subsystems.")

# Debian Specific CPack
set(CPACK_DEBIAN_PACKAGE_NAME ${TENTRILLION_PACKAGE_NAME})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "opencl-headers libopengl0 libgl1-mesa-dev libglu1-mesa-dev freeglut3-dev openal libopenal-dev")
set(CPACK_PACKAGE_CONTACT "Thefirey33")

# NSIS Specific CPack
set(CPACK_NSIS_MODIFY_PATH ON)
set(CPACK_NSIS_DISPLAY_NAME "TenTrillion Game Engine SDK")
set(CPACK_NSIS_PACKAGE_NAME "TenTrillion Game Engine SDK")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall the TenTrillion Game Engine SDK")
set(CPACK_NSIS_WELCOME_TITLE "Welcome to the TenTrillion Game Engine SDK Installer Wizard")
set(CPACK_NSIS_FINISH_TITLE "Finishing the TenTrillion Game Engine SDK Installer Wizard")

if (WIN32)
    set(CPACK_GENERATOR "TGZ;ZIP;NSIS;")
else ()
    set(CPACK_GENERATOR "TGZ;ZIP;DEB;RPM;")
endif ()

# RPM Specific CPack
set(CPACK_RPM_PACKAGE_NAME ${TENTRILLION_PACKAGE_NAME})

include(CPack)