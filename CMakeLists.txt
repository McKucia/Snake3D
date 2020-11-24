cmake_minimum_required(VERSION 3.17)
project(Snake3D)

set(CMAKE_CXX_STANDARD 17)

add_executable(Snake3D main.cpp Cube.cpp Cube.hpp Shader.cpp Shader.hpp Renderer.cpp Renderer.hpp)
target_link_libraries(Snake3D -lglfw -lGL -lGLEW)