#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Game.hpp"
#include "Renderer.hpp"
#include "Cube.hpp"

Renderer* renderer;
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

    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Game::Init() {
    Shader shader("../shaders/vertex.shader", "../shaders/fragment.shader");
    renderer = new Renderer(shader, Cube::vertices_);
    snake_ = new Snake(glm::vec3(300.0f, 200.0f, 0.0f), glm::vec3(50.0f, 50.0f, 50.0f));

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -1000.0f));
    view = glm::rotate(view, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 proj = glm::perspective(glm::radians(45.0f), 1200.0f / 800.0f, 0.1f, 100.0f);
    proj = glm::ortho(0.0f, 1200.0f, 0.0f, 800.0f, -1000.0f, 1000.0f);

    shader.Use();
    shader.setMat4f("uView", view);
    shader.setMat4f("uProj", proj);
}

bool pressed = false;
void Game::ProcessInput() {
    int exit = glfwGetKey(window, GLFW_KEY_ESCAPE);
    if(exit == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if(state_ == GAME_STATE::GAME_ACTIVE){
        int w = glfwGetKey(window, GLFW_KEY_W);
        if(w == GLFW_PRESS)
            snake_->changeDirection(DIRECTION::UP);

        int s = glfwGetKey(window, GLFW_KEY_S);
        if(s == GLFW_PRESS)
            snake_->changeDirection(DIRECTION::DOWN);

        int a = glfwGetKey(window, GLFW_KEY_A);
        if(a == GLFW_PRESS)
            snake_->changeDirection(DIRECTION::LEFT);

        int d = glfwGetKey(window, GLFW_KEY_D);
        if(d == GLFW_PRESS)
            snake_->changeDirection(DIRECTION::RIGHT);

        int space = glfwGetKey(window, GLFW_KEY_SPACE);
        if(space == GLFW_PRESS && !pressed) {
            snake_->addCube();
            pressed = true;
        }
        if(space == GLFW_RELEASE){
            pressed = false;
        }
    }
}

void Game::Update(float dt) {

    while(!glfwWindowShouldClose(window)){
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        ProcessInput();
        snake_->draw(*renderer);
        snake_->move();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
}

void Game::Render() {

}
