# Target name
set(target VoxelToy)

# Set architecture
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
    set(ARCHITECTURE x86)
else()
    set(ARCHITECTURE x64)
endif()

# Define dependencies
set(root_dir ${CMAKE_CURRENT_SOURCE_DIR}/../..)

# Includes
include_directories(
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Links
#link_directories()

# Sources
file(GLOB header_dir
        ${root_dir}/Includes)

file(GLOB_RECURSE headers
        ${header_dir}/*.hpp)

file(GLOB_RECURSE sources
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

# Build library
add_executable(${target}
        ${sources})

# Project options
set_target_properties(${target} PROPERTIES
        ${DEFAULT_PROJECT_OPTIONS}
        )

# Compile options
target_compile_options(${target}
        PRIVATE

        PUBLIC
        ${DEFAULT_COMPILE_OPTIONS}

        INTERFACE
        )
target_compile_definitions(${target}
        PRIVATE
        RESOURCES_DIR="${RESOURCES_DIR}"
        )

target_link_libraries(${target}
        PRIVATE
            glfw
            ${LIBS}
            ${CMAKE_DL_LIBS}
        PUBLIC
            ${DEFAULT_LINKER_OPTIONS}
            ${DEFAULT_LIBRARIES}
        INTERFACE
        )

# Precompiled headers
target_precompile_headers(
        ${target}
            PRIVATE
                <string>
                <vector>
                <map>
                <memory>
                <unordered_map>
)
