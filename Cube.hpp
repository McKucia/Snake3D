#pragma once

#include "Renderer.hpp"
#include "vector"

class Cube{
public:
    Cube(glm::vec3 position, glm::vec3 size, glm::vec3 color);
    void draw(Renderer& renderer);

    static std::vector<float> vertices_;

private:
    glm::vec3 position_;
    glm::vec3 size_;
    glm::vec3 color_;
};