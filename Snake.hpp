#pragma once

#include "Cube.hpp"

#include <vector>
#include <list>

class Snake{
public:
    Snake(glm::vec3 position, glm::vec3 size);
    void move();
    void draw(Renderer& renderer);
    void changeDirection(DIRECTION direction);
    void addCube();
    void checkCollision(Cube* other);

private:
    std::vector<Cube*> cubes_;
    DIRECTION nextDirection_;
    std::list<glm::vec3> curvePos_;
};