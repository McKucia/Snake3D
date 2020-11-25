#include "Snake.hpp"
#include <iostream>

Snake::Snake(glm::vec3 position, glm::vec3 size) : nextDirection_(DIRECTION::UP){
    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    glm::vec3 color(r1, r2, r3);
    cubes_.push_back(new Cube(position, size, color, DIRECTION::UP));
}

void Snake::draw(Renderer& renderer){
    for(const auto& cube : cubes_){
        cube->draw(renderer);
    }
}

void Snake::move(){
    if(cubes_[0]->canChangeDir_ && cubes_[0]->direction_ != nextDirection_) {
            cubes_[0]->direction_ = nextDirection_;
            curvePos_.push_back(cubes_[0]->position_);
            std::cout << cubes_[0]->position_.x << " " << cubes_[0]->position_.x << '\n';
    }
    int i = 0;
    for(auto& cube : cubes_){
        cube->move();
        if(cube == cubes_.front()){
            continue;
        }
        for(const auto& curve : curvePos_) {
            if (cube->position_ == curve) {
                cube->direction_ = cubes_[i]->direction_;
                break;
            }
        }
        i++;
    }
}

void Snake::changeDirection(DIRECTION direction){
    nextDirection_ = direction;
}

void Snake::addCube(){
    glm::vec3 position = cubes_.back()->position_;
    glm::vec3 size = cubes_[0]->size_;
    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    glm::vec3 color(r1, r2, r3);
    DIRECTION direction = cubes_.back()->direction_;

    if(cubes_.back()->direction_ == DIRECTION::UP){
        position.y -= size.y;
    }
    if(cubes_.back()->direction_ == DIRECTION::DOWN){
        position.y += size.y;
    }
    if(cubes_.back()->direction_ == DIRECTION::LEFT){
        position.x += size.x;
    }
    if(cubes_.back()->direction_ == DIRECTION::RIGHT){
        position.x -= size.x;
    }
    cubes_.push_back(new Cube(position, size, color, direction));
}