#pragma once
#include "Snake.hpp"

enum GAME_STATE{
    GAME_ACTIVE = 0, GAME_MENU, GAME_WIN
};

class Game{
public:
    Game(float width, float height);
    ~Game();

    void Init();
    void createWindow();
    void ProcessInput();
    void Update(float dt);
    void Render();

private:
    Snake* snake_;
    GAME_STATE state_;
    bool keys_[1024];
    float width_, height_;
};