#pragma once

enum GAME_STATE{
    GAME_ACTIVE = 0, GAME_MENU, GAME_WIN
};

class Game{
public:
    GAME_STATE state_;
    bool keys_[1024];
    float width_, height_;

    Game(float width, float height);
    ~Game();

    void Init();

    void createWindow();
    void ProcessInput();
    void Update(float dt);
    void Render();
};