cmake_minimum_required(VERSION 3.0.0)
project(mouse VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(mouse main.cpp)

target_link_libraries(mouse
    PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glut
)