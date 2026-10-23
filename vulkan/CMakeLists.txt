# TENTRILLION GAME ENGINE: VULKAN SECTION
# An extremely optimized game engine written
# from scratch in Vulkan, OpenGL, SDL and OpenAL.
#
# Copyright (c) 2026 Thefirey33

set(TENTRILLION_VULKAN_TARGETS
      src/tenvulkan.cpp
)
add_subdirectory(libs/volk EXCLUDE_FROM_ALL)

set(TENTRILLION_VULKAN_LIBRARY tentrillionvulkan)
add_library(${TENTRILLION_VULKAN_LIBRARY} SHARED ${TENTRILLION_VULKAN_TARGETS} ${TENTRILLION_SHARED_TARGETS})
target_include_directories(${TENTRILLION_VULKAN_LIBRARY} PUBLIC
      ${TENTRILLION_SHARED_INCLUDES}
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:/include>
)
target_link_libraries(${TENTRILLION_VULKAN_LIBRARY} glfw volk::volk)