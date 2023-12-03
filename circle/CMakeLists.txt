cmake_minimum_required(VERSION 3.0.0)
project(circle VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(circle main.cpp)

target_link_libraries(circle
    PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glut
)