#include "Ball.h"
#include <cmath>

float Ball::GetRandomFloat(float min, float max) {
    return GetRandomValue(0, 1000) / 1000.0f * (max - min) + min;
}

Ball::Ball(Vector2 Pos, int Rad, int GetScreenHeight, int GetScreenWidth) {
    Position_ = Pos;
    Radius_ = Rad;
    ScreenHeight = GetScreenHeight;
    ScreenWidth = GetScreenWidth;

    // Pick a random angle (e.g., -45° to 45° for right side or 135° to 225° for left side)
    float angle = GetRandomFloat(-45.0f, 45.0f) * (PI / 180.0f); // convert degrees to radians

    // Randomly decide left or right initial direction
    bool startRight = GetRandomValue(0, 1) == 1;

    // Set the initial velocity
    Current_Speed_.x = Speed_ * cos(angle) * (startRight ? 1 : -1);
    Current_Speed_.y = Speed_ * sin(angle);
}

void Ball::Reset(int screenW, int screenH) {
    Position_ = Vector2{ screenW / 2.0f, screenH / 2.0f };
    Speed_ = 5.0f;

    // Pick random starting angle
    float angle = GetRandomFloat(-45.0f, 45.0f) * (PI / 180.0f);
    bool startRight = GetRandomValue(0, 1) == 1;
    Current_Speed_.x = Speed_ * cos(angle) * (startRight ? 1 : -1);
    Current_Speed_.y = Speed_ * sin(angle);
}

void Ball::SetPosition(Vector2 pos) { Position_ = pos; }

void Ball::SetAngle(float angle, bool isRightPaddle) {
    float speed = sqrt(Current_Speed_.x * Current_Speed_.x + Current_Speed_.y * Current_Speed_.y);
    Current_Speed_.x = speed * cos(angle) * (isRightPaddle ? -1 : 1);
    Current_Speed_.y = speed * sin(angle);
}

void Ball::Draw() { DrawCircle(Position_.x, Position_.y, Radius_, RED); }

void Ball::Update() {
    Position_.x += Current_Speed_.x;
    Position_.y += Current_Speed_.y;

    if (Position_.x <= Radius_) Current_Speed_.x = fabs(Current_Speed_.x);
    if (Position_.x >= ScreenWidth - Radius_) Current_Speed_.x = -fabs(Current_Speed_.x);
    if (Position_.y <= Radius_) Current_Speed_.y = fabs(Current_Speed_.y);
    if (Position_.y >= ScreenHeight - Radius_) Current_Speed_.y = -fabs(Current_Speed_.y);
}

void Ball::AddSpeed() {
    float speed = sqrt(Current_Speed_.x * Current_Speed_.x + Current_Speed_.y * Current_Speed_.y);
    speed += 0.2f;  // increase by small amount
    float angle = atan2(Current_Speed_.y, Current_Speed_.x);
    Current_Speed_.x = speed * cos(angle);
    Current_Speed_.y = speed * sin(angle);
}

Vector2 Ball::GetPosition() { return Position_; }
int Ball::GetRadius() { return Radius_; }