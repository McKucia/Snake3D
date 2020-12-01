#pragma once

#include "Cube.hpp"

class Food : public Cube{
public:
    Food(glm::vec3 position, glm::vec3 size, glm::vec3 color, DIRECTION direction);
};