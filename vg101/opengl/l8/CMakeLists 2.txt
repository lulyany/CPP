cmake_minimum_required(VERSION 2.8)
project(Glut)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Werror -Wpedantic -Wextra -Wconversion -Wvla -Wno-deprecated-declarations")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

add_executable(Glut main.cpp)
target_link_libraries(Glut ${GLUT_LIBRARY} ${OPENGL_LIBRARY} m)