cmake_minimum_required(VERSION 3.0)

project(OGLA)

option(GLFW_BUILD_DOCS OFF)
option(GLFW_BUILD_EXAMPLES OFF)
option(GLFW_BUILD_TESTS OFF)
add_subdirectory(lib/glfw)

option(ASSIMP_BUILD_SAMPLES OFF)
option(ASSIMP_BUILD_TESTS OFF)
add_subdirectory(lib/assimp)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -std=c++2a")
    if (NOT WIN32)
        set(GLAD_LIBRARIES dl)
    endif()
endif()

include_directories(
    ./include
    lib/glad/include/
    lib/glfw/include/
    lib/assimp/include/
    lib/glm/
    lib/stb/
)

file(GLOB LIBRARY_SOURCES lib/glad/src/glad.c lib/stb/stb_image.cpp)
file(GLOB PROJECT_HEADERS include/*.h)
file(GLOB PROJECT_SOURCES src/*.cpp)
file(GLOB PROJECT_SHADERS res/shaders/*.fs res/shaders/*.vs)

file(GLOB PROJECT_CONFIGS 
    CMakeLists.txt
    README.md
    .gitignore
    .gitmodules
)

source_group("include" FILES ${PROJECT_HEADERS})
source_group("res/shaders" FILES ${PROJECT_SHADERS})
source_group("lib" FILES ${LIBRARY_SOURCES})
source_group("src" FILES ${PROJECT_SOURCES})

add_definitions(
    -DGLFW_INCLUDE_NONE
    -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\"
)

add_executable(
    ${PROJECT_NAME} 
    ${PROJECT_SOURCES} 
    ${PROJECT_HEADERS}
    ${PROJECT_SHADERS} 
    ${PROJECT_CONFIGS}
    ${LIBRARY_SOURCES}
)

target_link_libraries(
    ${PROJECT_NAME} 
    glfw
    assimp
    ${GLFW_LIBRARIES} 
    ${GLAD_LIBRARIES}
)

set_target_properties(
    ${PROJECT_NAME} 
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/${PROJECT_NAME}
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/res/shaders $<TARGET_FILE_DIR:${PROJECT_NAME}>
    DEPENDS ${PROJECT_SHADERS}
)