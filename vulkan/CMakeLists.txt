# TENTRILLION GAME ENGINE: VULKAN SECTION
# An extremely optimized game engine written
# from scratch in Vulkan, OpenGL, SDL and OpenAL.
#
# Copyright (c) 2026 Thefirey33

set(TENTRILLION_VULKAN_TARGETS
      src/tenvulkan.cpp
)
set(TENTRILLION_VULKAN_LIBRARY tentrillionvulkan)
add_library(${TENTRILLION_VULKAN_LIBRARY} SHARED ${TENTRILLION_VULKAN_TARGETS})
