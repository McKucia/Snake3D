#pragma once

#include "Renderer.hpp"
#include "vector"

enum class DIRECTION{
    UP = 0, DOWN, LEFT, RIGHT
};

class Cube{
public:
    Cube(glm::vec3 position, glm::vec3 size, glm::vec3 color);
    void draw(Renderer& renderer);
    void move();

    static std::vector<float> vertices_;

    float speed_;
    DIRECTION direction_;
    glm::vec3 position_;
    glm::vec3 size_;
    glm::vec3 color_;
};