#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Game.hpp"
#include "Renderer.hpp"
#include "Cube.hpp"

Renderer* renderer;
std::vector<Cube*> cubes;
GLFWwindow* window;

Game::Game(float width, float height)
    : state_(GAME_STATE::GAME_ACTIVE), keys_(),
    width_(width), height_(height)
{
    createWindow();
    Init();
}

Game::~Game() {
    delete renderer;
}

void Game::createWindow() {

    if(!glfwInit()){
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width_, height_, "Snake", NULL, NULL);

    if(!window){
        glfwTerminate();
        return;

    }
    glfwMakeContextCurrent(window);

    if(glewInit() != GLEW_OK){
        std::cerr << "Error\n";
    }
    glfwSwapInterval(1);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::Init() {
    Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
    renderer = new Renderer(shader, Cube::vertices_);

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -20.0f));
    view = glm::rotate(view, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);
    proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, -1000.0f, 1000.0f);

    shader.Use();
    shader.setMat4f("uView", view);
    shader.setMat4f("uProj", proj);

    glm::vec3 position = glm::vec3(300.0f, 200.0f, 0.0f);
    glm::vec3 size = glm::vec3(100.0f, 100.0f, 100.0f);
    glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

    cubes.push_back(new Cube(position, size, color));
    cubes.push_back(new Cube(position * 2.0f, size / 2.0f, color / 10.0f));
}

void Game::ProcessInput() {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(state_ == GAME_STATE::GAME_ACTIVE){

        if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
            cubes[0]->move(DIRECTION::UP);
        }
        if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            cubes[0]->move(DIRECTION::DOWN);
        }
        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            cubes[0]->move(DIRECTION::LEFT);
        }
        if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            cubes[0]->move(DIRECTION::RIGHT);
        }
    }
}

void Game::Update(float dt) {

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(const auto& cube : cubes){
            cube->draw(*renderer);
        }
        ProcessInput();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Game::Render() {

}
