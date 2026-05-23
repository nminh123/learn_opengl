cmake_minimum_required(VERSION 3.26.0)
project(learn_opengl LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include (FetchContent)
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(glfw glad)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS 
    src/*.cpp)
add_executable(app ${SRC_FILES})

target_compile_features(app PRIVATE cxx_std_20)

target_include_directories(app PRIVATE 
    ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(app glfw OpenGL::GL)
