cmake_minimum_required(VERSION 3.19.1)

project(2DNBodySim)



set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCE_FILES
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
     "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
    ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/src/glad.c
    )

target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${PROJECT_NAME} PUBLIC

    )


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glfw-3.4)
target_link_libraries(${PROJECT_NAME} glfw)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/glad/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR/thirdparty/glm})

target_link_libraries(
    ${PROJECT_NAME} glfw
    )
