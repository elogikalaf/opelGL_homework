cmake_minimum_required(VERSION 3.10)

project(openGl)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(MyOpenGLApp main.cpp)

target_link_libraries(MyOpenGLApp
    PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glut
)