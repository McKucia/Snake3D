#include "Cube.hpp"
#include <iostream>

std::vector<float> Cube::vertices_ = {
        //back
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f,0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        //front
        -0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        //left
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

        //right
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,

        //down
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f,  0.5f,
        0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        //up
        -0.5f,  0.5f, -0.5f,
        0.5f,  0.5f, -0.5f,
        0.5f,  0.5f,  0.5f,
        0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
};

Cube::Cube(glm::vec3 position, glm::vec3 size, glm::vec3 color, DIRECTION direction)
    : position_(position), size_(size), color_(color),
    direction_(direction), speed_(5.0f), canChangeDir_(true) {}

void Cube::draw(Renderer& renderer){
    renderer.draw(position_, size_, color_);
}

void Cube::move(){
    if(direction_ == DIRECTION::UP){
        position_.y += speed_;
    }
    if(direction_ == DIRECTION::DOWN){
        position_.y -= speed_;
    }
    if(direction_ == DIRECTION::LEFT){
        position_.x -= speed_;
    }
    if(direction_ == DIRECTION::RIGHT){
        position_.x += speed_;
    }

    if(static_cast<int>(position_.x) % static_cast<int>(size_.x) == 0
       && static_cast<int>(position_.y) % static_cast<int>(size_.y) == 0){
        canChangeDir_ = true;
    }
    else{
        canChangeDir_ = false;
    }
}