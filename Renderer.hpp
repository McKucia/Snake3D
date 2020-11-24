#pragma once
#include <vector>

#include "glm/glm/glm.hpp"
#include "glm/glm/gtc/matrix_transform.hpp"

#include "Shader.hpp"

class Renderer{
public:
    Renderer(Shader& shader, std::vector<float> vertices);
    ~Renderer();
    void draw(glm::vec3 position, glm::vec3 size, glm::vec3 color);
    void init(std::vector<float> vertices);

private:
    Shader shader_;
    unsigned int VAO_;
};