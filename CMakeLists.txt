cmake_minimum_required(VERSION 3.15)
project(X0V)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

# recursively get all source files
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

# exclude header-onlys
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/renderer/mesh/VertexAttribute.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/renderer/mesh/DefaultMaterial.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/shader/ShaderType.cpp) # its header-only

# explicit externals
set(EXTERNAL_SOURCES 
    ${CMAKE_SOURCE_DIR}/../Deps/src/glad.c
    ${CMAKE_SOURCE_DIR}/../Deps/include/stbi/stb_image.cpp
)

# combine sources
set(SOURCES ${PROJECT_SOURCES} ${EXTERNAL_SOURCES})

# build binary
add_executable(AbandonedCrypt ${SOURCES})

# include dirs
target_include_directories(AbandonedCrypt 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src    # project sources
    ${CMAKE_SOURCE_DIR}/../Deps/include # dependencies
)

# linking
target_link_directories(AbandonedCrypt PUBLIC ${CMAKE_SOURCE_DIR}/../Deps/lib)
target_link_libraries(AbandonedCrypt glfw3 opengl32)