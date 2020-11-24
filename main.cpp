#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "Cube.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"
#include "Game.hpp"

constexpr float screenWidth = 1200;
constexpr float screenHeight = 800;


int main() {
    Game* game = new Game(screenWidth, screenHeight);
    game->Update(3.0f);

    return 0;
}
