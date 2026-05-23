cmake_minimum_required(VERSION 3.26.0)
project(learn_opengl LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
#glfw3
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)
#glad
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG v2.0.8
)
FetchContent_MakeAvailable(glfw glad)
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
add_executable(app ${SRC_FILES})

target_compile_features(app PRIVATE cxx_std_20)
target_include_directories(app PRIVATE
    ${CMAKE_SOURCE_DIR}/include)

# Thêm các framework bắt buộc trên macOS
if(APPLE)
    target_link_libraries(app PRIVATE
        "-framework Cocoa"
        "-framework IOKit"
        "-framework CoreVideo"
    )
endif()