// Pong.cpp : Defines the entry point for the application.
//

#include "Ponge.h"
#include <cmath>

using namespace std;

const int screenHeight = 700;
const int screenWidth = 1000;

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
    Player(Vector2 Pos, int Game_Screen_Height, int Width, int Height) {
        Position_ = Pos;
        Current_Speed_ = Speed_;
        Screen_Height_ = Game_Screen_Height;
        Rect_Height_ = Height;
        Rect_Width_ = Width;
    }

    void Draw() {
        DrawRectangle(Position_.x, Position_.y, Rect_Width_, Rect_Height_, BLUE);
    }

    void Update() {
        if (IsKeyDown(KEY_LEFT_SHIFT)) Current_Speed_ = Speed_ * 2;
        else Current_Speed_ = Speed_;
        if (IsKeyDown(KEY_UP) && Position_.y >= 0) {
            Position_.y -= Current_Speed_;
            is_moving_ = true;
        }
        else is_moving_ = false;
        if (IsKeyDown(KEY_DOWN) && Position_.y <= Screen_Height_ - Rect_Height_) Position_.y += Current_Speed_;
    }
    Vector2 GetPosition() { return Position_; }
    float GetSpeed() { return Current_Speed_; }

    Rectangle GetRec() {
        Rectangle rec;
        rec.x = Position_.x;
        rec.y = Position_.y;
        rec.width = Rect_Width_;
        rec.height = Rect_Height_;
        return rec;
    }
    int GetHeight() { return Rect_Height_; }
};

class Ball {
private:
    Vector2 Position_;
    float Speed_ = 5.0f;
    Vector2 Current_Speed_;
    int Radius_;
    int ScreenHeight;
    int ScreenWidth;

public:
    float GetRandomFloat(float min, float max) {
        return GetRandomValue(0, 1000) / 1000.0f * (max - min) + min;
    }
    Ball(Vector2 Pos, int Rad, int GetScreenHeight, int GetScreenWidth) {
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

    void SetAngle(float angle, bool isRightPaddle) {
        float speed = sqrt(Current_Speed_.x * Current_Speed_.x + Current_Speed_.y * Current_Speed_.y);
        Current_Speed_.x = speed * cos(angle) * (isRightPaddle ? -1 : 1);
        Current_Speed_.y = speed * sin(angle); 
    }

    void Draw() { DrawCircle(Position_.x, Position_.y, Radius_, RED); }

    void Update() {
        Position_.x += Current_Speed_.x;
        Position_.y += Current_Speed_.y;

        if (Position_.x <= Radius_) Current_Speed_.x = fabs(Current_Speed_.x);
        if (Position_.x >= ScreenWidth - Radius_) Current_Speed_.x = -fabs(Current_Speed_.x);
        if (Position_.y <= Radius_) Current_Speed_.y = fabs(Current_Speed_.y);
        if (Position_.y >= ScreenHeight - Radius_) Current_Speed_.y = -fabs(Current_Speed_.y);
    }

    Vector2 GetPosition() { return Position_; }
    int GetRadius() { return Radius_; }
};

class Enemy {
protected:
    const float Speed_ = 4.95f;
    Vector2 Position_;
    int ScreenHeight;
    int ScreenWidth;
    int Rect_Height_;
    int Rect_Width_;
public:
    Enemy(Vector2 Pos, int Game_Screen_Height, int Game_Screen_Width, int Width, int Height) {
        Position_ = Pos;
        ScreenHeight = Game_Screen_Height;
        ScreenWidth = Game_Screen_Width;
        Rect_Height_ = Height;
        Rect_Width_ = Width;
    }

    virtual void Update(Vector2 ball) {
        float center = Position_.y + Rect_Height_ / 2;
        if (ball.y > center && Position_.y < ScreenHeight - Rect_Height_) Position_.y += Speed_;
        else if (ball.y < center && Position_.y > 0) Position_.y -= Speed_;
    }
    virtual ~Enemy() = default;

    void Draw() { DrawRectangle(Position_.x, Position_.y, Rect_Width_, Rect_Height_, GREEN); }
    Vector2 GetPosition() { return Position_; }
    int GetHeight() { return Rect_Height_; }
    Rectangle GetRec() {
        Rectangle rec;
        rec.x = Position_.x;
        rec.y = Position_.y;
        rec.width = Rect_Width_;
        rec.height = Rect_Height_;
        return rec;
    }
};

class Enemy_AI_Type_2 : public Enemy {
public:
    using Enemy::Enemy;

    void Update(Vector2 ball) override {
        float center = Position_.y + Rect_Height_ / 2;
        float screenCenter = ScreenHeight / 2;

        if (ball.x < ScreenWidth / 2) {
            if (center > screenCenter + 5) Position_.y -= Speed_ * 0.8f;
            else if (center < screenCenter - 5) Position_.y += Speed_ * 0.8f;
        }
        else {
            float moveSpeed = Speed_;
            if (ball.y > center + 30 && Position_.y < ScreenHeight - Rect_Height_) Position_.y += moveSpeed;
            else if (ball.y < center - 30 && Position_.y > 0) Position_.y -= moveSpeed;
        }
    }
};

int main() {
    bool paused = false;
    Player Player(Vector2(screenWidth / 2 - 450, screenHeight / 2), screenHeight, 20, 80);
    Ball Ball(Vector2(screenWidth / 2, screenHeight / 2), 10, screenHeight, screenWidth);
    Enemy_AI_Type_2 Enemy(Vector2(screenWidth / 2 + 450, screenHeight / 2), screenHeight, screenWidth, 20, 80);

    InitWindow(screenWidth, screenHeight, "Pong with angled reflection");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_P)) paused = !paused;

        if (!paused) {
            // Player collision
            if (CheckCollisionCircleRec(Ball.GetPosition(), Ball.GetRadius(), Player.GetRec())) {
                float paddleCenter = Player.GetPosition().y + Player.GetHeight() / 2;
                float relativeY = Ball.GetPosition().y - paddleCenter;
                float normalizedY = relativeY / (Player.GetHeight() / 2);
                float maxAngle = 60 * (PI / 180);
                float angle = normalizedY * maxAngle;
                Ball.SetAngle(angle, false);
            }

            // Enemy collision
            if (CheckCollisionCircleRec(Ball.GetPosition(), Ball.GetRadius(), Enemy.GetRec())) {
                float paddleCenter = Enemy.GetPosition().y + Enemy.GetHeight() / 2;
                float relativeY = Ball.GetPosition().y - paddleCenter;
                float normalizedY = relativeY / (Enemy.GetHeight() / 2);
                float maxAngle = 60 * (PI / 180);
                float angle = normalizedY * maxAngle;
                Ball.SetAngle(angle, true); // true → enemy paddle
            }

            Player.Update();
            Enemy.Update(Ball.GetPosition());
            Ball.Update();
        }

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Player.Draw();
        Enemy.Draw();
        Ball.Draw();
        EndDrawing();
    }
    return 0;
}