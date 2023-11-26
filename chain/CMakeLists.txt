cmake_minimum_required(VERSION 3.0.0)
project(chain VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

add_executable(chain main.cpp)

target_link_libraries(chain
    PRIVATE
    OpenGL::GL
    GLEW::GLEW
    glut
)