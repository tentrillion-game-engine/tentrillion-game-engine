
set(SOURCE_FILES
        tentrillion.cpp
        tentrillionService.cpp
        services/renderingService.cpp
        services/textureService.cpp
        math/vectorMath.cpp
)
set(SDL_TEST OFF CACHE BOOL "Disable SDL test library" FORCE)

find_package(Vulkan REQUIRED)
find_package(OpenGL REQUIRED)
option(TENTRILLION_BACKEND_VULKAN "Use the Vulkan backend. Toggle OFF for OpenGL." ON)

add_library(${LIBRARY_NAME} SHARED ${SOURCE_FILES})

target_include_directories(${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/lib/services>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/lib>
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(${LIBRARY_NAME} PUBLIC
        $<BUILD_INTERFACE:SDL3::SDL3>
        $<BUILD_INTERFACE:SDL3_image::SDL3_image>
        $<BUILD_INTERFACE:SDL3_mixer::SDL3_mixer>
        $<BUILD_INTERFACE:nlohmann_json::nlohmann_json>
        $<$<BOOL:${TENTRILLION_BACKEND_VULKAN}>:$<BUILD_INTERFACE:Vulkan::Vulkan>>
        $<$<NOT:$<BOOL:${TENTRILLION_BACKEND_VULKAN}>>:$<BUILD_INTERFACE:OpenGL::GL>>
)

# Add definitions if the project is compiling for VULKAN targets.

if(TENTRILLION_BACKEND_VULKAN)
        target_compile_definitions(${LIBRARY_NAME} PUBLIC
                TENTRILLION_BACKEND_VULKAN
        )
endif()


generate_export_header(${LIBRARY_NAME} 
        EXPORT_FILE_NAME "${CMAKE_BINARY_DIR}/tentrillion_export.h"
)



# CMake Instructions for installing to other projects.

install(TARGETS ${LIBRARY_NAME}
        EXPORT TenTrillionTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${ENGINE_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT TenTrillionTargets
        FILE TenTrillionTargets.cmake
        NAMESPACE TenTrillionGameEngine::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}.cmake
)
install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/TenTrillionConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/TenTrillionConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)
configure_package_config_file(${CMAKE_SOURCE_DIR}/Config.cmake.in
        "${CMAKE_CURRENT_BINARY_DIR}/TenTrillionConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/${LIBRARY_NAME}
)

