#include <GL/glew.h>
#include <iostream>

#include "Renderer.hpp"

Renderer::Renderer(Shader &shader, std::vector<float> vertices) : shader_(shader) {
    init(vertices);
}

Renderer::~Renderer() {
    glDeleteVertexArrays(1, &VAO_);
}

void Renderer::draw(glm::vec3 position, glm::vec3 size, glm::vec3 color) {
    shader_.Use();

    glm::mat4 model(1.0f);

    model = glm::translate(model, position);
    model = glm::scale(model, size);

    shader_.setVec3f("uColor", color);
    shader_.setMat4f("uModel", model);

    glBindVertexArray(VAO_);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void Renderer::init(std::vector<float> vertices) {
    unsigned int VBO;
    glGenVertexArrays(1, &VAO_);
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindVertexArray(VAO_);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}