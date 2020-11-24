#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "Cube.hpp"
#include "Shader.hpp"
#include "Renderer.hpp"

constexpr float screenWidth = 1200;
constexpr float screenHeight = 800;

int main() {
    GLFWwindow* window;

    if(!glfwInit()){
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, "Snake", NULL, NULL);

    if(!window){
        glfwTerminate();
        return -1;

    }
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cerr << "Error\n";
    }
    glfwSwapInterval(1);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //--------------------------------------------------------------------
    Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
    Renderer* renderer = new Renderer(shader, Cube::vertices_);

    glm::vec3 position = glm::vec3(300.0f, 200.0f, 0.0f);
    glm::vec3 size = glm::vec3(100.0f, 100.0f, 100.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

    std::vector<Cube*> cubes;
    cubes.push_back(new Cube(position, size, color));
    cubes.push_back(new Cube(position * 2.0f, size / 2.0f, color / 10.0f));
    //Cube* cube = new Cube(position, size, color);

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        for(const auto& cube : cubes){
            cube->draw(*renderer);
        }
        //cube->draw(*renderer);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete renderer;
    //delete cube;
    glfwTerminate();
    return 0;
}
