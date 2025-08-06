cmake_minimum_required(VERSION 3.19.1)

project(2DNBodySim)



set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
  )


set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui)

file(GLOB IMGUI_SRC
   "${IMGUI_DIR}/*.cpp"
   "${IMGUI_DIR}/*.h"
)

set(IMGUI_SOURCES
    ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/src/glad.c
    ${IMGUI_SOURCES}
    ${IMGUI_SRC}
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glm
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/imgui/backends/
    )

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.4)
target_link_libraries(${PROJECT_NAME} glfw)


target_link_libraries(
    ${PROJECT_NAME} glfw
    )
