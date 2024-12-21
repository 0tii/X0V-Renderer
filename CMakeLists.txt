# Minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Project Name
project(AbandonedCrypt)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

# Exclude specific files if necessary
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/renderer/mesh/VertexAttribute.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/renderer/mesh/DefaultMaterial.cpp) # its header-only

# Add external sources
set(EXTERNAL_SOURCES 
    ${CMAKE_SOURCE_DIR}/../Deps/src/glad.c
    ${CMAKE_SOURCE_DIR}/../Deps/include/stbi/stb_image.cpp
)

# Combine all sources
set(SOURCES ${PROJECT_SOURCES} ${EXTERNAL_SOURCES})

# Create the executable
add_executable(AbandonedCrypt ${SOURCES})

# Include directories for the project
target_include_directories(AbandonedCrypt 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src    # Your project sources
    ${CMAKE_SOURCE_DIR}/../Deps/include # External dependencies
)

# Link external libraries
target_link_directories(AbandonedCrypt PUBLIC ${CMAKE_SOURCE_DIR}/../Deps/lib)
target_link_libraries(AbandonedCrypt glfw3 opengl32)