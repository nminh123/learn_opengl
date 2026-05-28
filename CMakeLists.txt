cmake_minimum_required(VERSION 3.26.0)
project(learn_opengl VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.c)
add_executable(app ${SRC_FILES})

target_include_directories(app PRIVATE ${CMAKE_SOURCE_DIR}/include)
file(COPY
    "${CMAKE_SOURCE_DIR}/Resources Files/"
    DESTINATION
    "${CMAKE_BINARY_DIR}"
)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
target_link_libraries(app PRIVATE
    glfw
    OpenGL::GL)