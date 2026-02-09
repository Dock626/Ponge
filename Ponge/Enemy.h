#pragma once
#pragma once
#include <raylib.h>

class Enemy {
protected:
    float reactionDelay;
    float reactionTimer;
    float targetY;
    const float Speed_;
    Vector2 Position_;
    int ScreenHeight;
    int ScreenWidth;
    int Rect_Height_;
    int Rect_Width_;
public:
    Enemy(Vector2 Pos, int Game_Screen_Height, int Game_Screen_Width, int Width, int Height);
    virtual void Update(Vector2 ball);
    virtual ~Enemy();

    void Draw();
    Vector2 GetPosition();
    int GetHeight();
    Rectangle GetRec();
};