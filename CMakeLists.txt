cmake_minimum_required(VERSION 3.17)
project(Snake3D)

set(CMAKE_CXX_STANDARD 17)

add_executable(Snake3D main.cpp Cube.cpp Cube.hpp Shader.cpp Shader.hpp Renderer.cpp Renderer.hpp Game.cpp Game.hpp Snake.cpp Snake.hpp Board.cpp Board.hpp Food.cpp Food.hpp)
target_link_libraries(Snake3D -lglfw -lGL -lGLEW)