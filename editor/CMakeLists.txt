# TENTRILLION GAME ENGINE: EDITOR SECTION
# An extremely optimized game engine written
# from scratch in Vulkan, OpenGL, SDL and OpenAL.
#
# Copyright (c) 2026 Thefirey33

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(TENTRILLION_EDITOR_APPLICATION "tenditor")
find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(TENTRILLION_EDITOR_TARGETS
    src/main.cpp
)
if(WIN32)
    add_executable(${TENTRILLION_EDITOR_APPLICATION} WIN32 ${TENTRILLION_EDITOR_TARGETS})
else()
    add_executable(${TENTRILLION_EDITOR_APPLICATION} ${TENTRILLION_EDITOR_TARGETS})
endif()
target_link_libraries(${TENTRILLION_EDITOR_APPLICATION} Qt5::Core)

