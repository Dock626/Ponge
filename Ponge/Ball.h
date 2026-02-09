#pragma once
#pragma once
#include <raylib.h>

class Ball {
private:
    Vector2 Position_;
    float Speed_ = 5.0f;
    Vector2 Current_Speed_;
    int Radius_;
    int ScreenHeight;
    int ScreenWidth;

public:
    Ball(Vector2 Pos, int Rad, int GetScreenHeight, int GetScreenWidth);
    float GetRandomFloat(float min, float max);
    void Reset(int screenW, int screenH);
    void SetPosition(Vector2 pos);
    void SetAngle(float angle, bool isRightPaddle);
    void Draw();
    void Update();
    void AddSpeed();
    Vector2 GetPosition();
    int GetRadius();
};