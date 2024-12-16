# Minimum CMake version
cmake_minimum_required(VERSION 3.15)

# Project Name
project(AbandonedCrypt)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add source files
file(GLOB_RECURSE SOURCES src/*.cpp)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/../Deps/include)

# Link libraries
link_directories(${CMAKE_SOURCE_DIR}/../Deps/lib)

# Add glad.c to the source list
set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/../Deps/src/glad.c)

# Add the stb_image.cpp file to the source list
set(SOURCES ${SOURCES} ${CMAKE_SOURCE_DIR}/../Deps/include/stbi/stb_image.cpp)

# Add the executable
add_executable(AbandonedCrypt ${SOURCES})

# Link required libraries
target_link_libraries(AbandonedCrypt glfw3 opengl32)
