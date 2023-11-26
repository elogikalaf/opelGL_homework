cmake_minimum_required(VERSION 3.0.0)
project(parabola VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(parabola main.cpp)

target_link_libraries(parabola
    PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glut
)