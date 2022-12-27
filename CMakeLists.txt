# CMake version
cmake_minimum_required(VERSION 3.8.2 FATAL_ERROR)

# Include cmake modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

# Declare project
project(VoxelToy)

# Set output directories
set(DEFAULT_CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARRY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

# Set enable output of compile commands during generation
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Require OpenGL package
#find_package(OpenGL REQUIRED)

# Includes
include_directories(Includes)
include_directories(External)
include_directories(External/GLFW/include)
include_directories(External/Glad/include)
include_directories(SYSTEM External/glm)
include_directories(External/imgui)
include_directories(External/stb_image)

set(LIBS)
add_library(GLAD "External/Glad/src/glad.c")
add_library(imgui   External/imgui/imgui.cpp
                    External/imgui/imconfig.h
                    External/imgui/imgui_draw.cpp
                    External/imgui/imgui.h
                    External/imgui/imgui_demo.cpp
                    External/imgui/imgui_internal.h
                    External/imgui/imgui_tables.cpp
                    External/imgui/imgui_widgets.cpp
                    External/imgui/imstb_rectpack.h
                    External/imgui/imstb_textedit.h
                    External/imgui/imstb_truetype.h)
add_library(stb "External/stb_image/stb_image.cpp")

set(LIBS ${LIBS} GLAD imgui stb)

# Compile options
include(CMake/CompileOptions.cmake)

# Build type - Release by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Overrides
set(CMAKE_MACOSX_RPATH ON)
set(CMAKE_OSX_ARCHITECTURES "x86_64")

# Set Resources
#get_filename_component(RESOURCES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Resources ABSOLUTE)
#set(RESOURCES_OBJS
#        ${RESOURCES_DIR}/font.png)

# Project modules
add_subdirectory(External/GLFW)
add_subdirectory(Sources/VoxelToy)
#add_subdirectory(Tests/UnitTests)


# Code coverage - Debug only
# NOTE: Code coverage results with an optimized (non-Debug) build may be misleading
option(BUILD_COVERAGE "Build code coverage" OFF)
if (CMAKE_BUILD_TYPE MATCHES Debug AND CMAKE_COMPILER_IS_GNUCXX AND BUILD_COVERAGE)
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage UnitTests coverage)
endif()
