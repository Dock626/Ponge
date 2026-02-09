#pragma once
#include <raylib.h>

class Player {
private:
    Vector2 Position_;
    const float Speed_ = 5.0f;
    float Current_Speed_;
    int Screen_Height_;
    int Rect_Height_;
    int Rect_Width_;

public:
    bool is_moving_ = false;
    Player(Vector2 Pos, int Game_Screen_Height, int Width, int Height);

    void Draw();
    void Update();
    Vector2 GetPosition();
    float GetSpeed();
    Rectangle GetRec();
    int GetHeight();
};