cmake_minimum_required(VERSION 3.15)
project(X0V)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
endif()

add_compile_definitions(GLM_FORCE_DEFAULT_ALIGNED_GENTYPES)

# recursively get all source files
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp)

# exclude header-onlys
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/renderer/mesh/VertexAttribute.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/renderer/mesh/DefaultMaterial.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/shader/ShaderType.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/light/DirectionalLight.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/light/PointLight.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/light/SpotLight.cpp) # its header-only
list(REMOVE_ITEM PROJECT_SOURCES ${CMAKE_SOURCE_DIR}/src/light/LightData.cpp) # its header-only

# explicit externals
set(EXTERNAL_SOURCES 
    ${CMAKE_SOURCE_DIR}/../Deps/src/glad.c
    ${CMAKE_SOURCE_DIR}/../Deps/include/stbi/stb_image.cpp
)

# combine sources
set(SOURCES ${PROJECT_SOURCES} ${EXTERNAL_SOURCES})

# build binary
add_executable(X0V ${SOURCES})

# include dirs
target_include_directories(X0V 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/src    # project sources
    ${CMAKE_SOURCE_DIR}/../Deps/include # dependencies
)

# linking
target_link_directories(X0V PUBLIC ${CMAKE_SOURCE_DIR}/../Deps/lib/glfw)
target_link_directories(X0V PUBLIC ${CMAKE_SOURCE_DIR}/../Deps/lib/assimp)
target_link_directories(X0V PUBLIC ${CMAKE_SOURCE_DIR}/../Deps/lib)
target_link_libraries(X0V glfw3 opengl32 assimp-vc142-mtd)

# copy assimp dll to project folder
set(ASSIMP_DLL_PATH ${CMAKE_SOURCE_DIR}/../Deps/bin/assimp/assimp-vc142-mtd.dll)

add_custom_command(
    TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        ${ASSIMP_DLL_PATH}
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
)