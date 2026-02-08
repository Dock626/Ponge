// Pong.cpp : Defines the entry point for the application.
//

#include "Ponge.h"

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
        if (IsKeyDown(KEY_UP) and Position_.y >= 0) {
            Position_.y -= Current_Speed_;
			is_moving_ = true;
        } else is_moving_ = false;
        if (IsKeyDown(KEY_DOWN) and Position_.y <= Screen_Height_ - Rect_Height_) Position_.y += Current_Speed_;
    }
    Vector2 GetPosition() {
        return Position_;
    }

    float GetSpeed() {
        return Current_Speed_;
	}

    Rectangle GetRec() {
        Rectangle rec;
        rec.x = Position_.x;
        rec.y = Position_.y;
        rec.width = Rect_Width_;
        rec.height = Rect_Height_;
        return rec;
	}
};

class Ball {
private:
    Vector2 Position_;
    const float Speed_ = 5.0f;
    Vector2 Current_Speed_;
    int Radius_;
	bool Moving_Right_ = true;
	bool Moving_Down_ = true;
    int ScreenHeight;
	int ScreenWidth;

public:
    Ball(Vector2 Pos, int Rad, int GetScreenHeight, int GetScreenWidth) {
        Position_ = Pos;
        Current_Speed_.x = Speed_;
		Current_Speed_.y = Speed_;
        Radius_ = Rad;
		ScreenHeight = GetScreenHeight;
        ScreenWidth = GetScreenWidth;
    }
    void SetDirection() {
		Moving_Right_ = !Moving_Right_;
    }
    void Draw() {
        DrawCircle(Position_.x, Position_.y, Radius_, RED);
    }
    void Update() {
        if (Moving_Right_) Position_.x += Current_Speed_.x;
            else Position_.x -= Current_Speed_.x;
        if (Moving_Down_) Position_.y += Current_Speed_.y;
            else Position_.y -= Current_Speed_.y;

        if (Position_.x <= Radius_) Moving_Right_ = true;
        if (Position_.x >= ScreenWidth - Radius_) Moving_Right_ = false;
        if (Position_.y <= Radius_) Moving_Down_ = true;
        if (Position_.y >= ScreenHeight - Radius_) Moving_Down_ = false;
    }
    void AddSpeed() {
        Current_Speed_.x += 0.1f;
        Current_Speed_.y += 0.1f;
	}
    Vector2 GetPosition() {
        return Position_;
	}
    int GetRadius() {
        return Radius_;
	}
};
class Enemy {
private:
    const float Speed_ = 5.0f;
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
    void Update(int ballY) {
        float center = Position_.y + Rect_Height_ / 2;

        if (ballY > center && Position_.y < ScreenHeight - Rect_Height_)
            Position_.y += Speed_;
        else if (ballY < center && Position_.y > 0)
            Position_.y -= Speed_;
    }
    void Draw() {
        DrawRectangle(Position_.x, Position_.y, Rect_Width_, Rect_Height_, GREEN);
	}

    Rectangle GetRec() {
        Rectangle rec;
        rec.x = Position_.x;
        rec.y = Position_.y;
        rec.width = Rect_Width_;
        rec.height = Rect_Height_;
        return rec;
    }

};
int main()
{
    
    // Initialization
    //--------------------------------------------------------------------------------------
    bool paused = false;
    Player Player(Vector2(screenWidth / 2 - 450, screenHeight / 2), screenHeight, 20, 80);
	Ball Ball(Vector2(screenWidth / 2, screenHeight / 2), 10, screenHeight, screenWidth);
	Enemy Enemy(Vector2(screenWidth / 2 + 450, screenHeight / 2), screenHeight, screenWidth, 20, 80);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		// Update
        if (IsKeyPressed(KEY_P)) paused = !paused;
        if (!paused) {
            if (CheckCollisionCircleRec(Ball.GetPosition(), Ball.GetRadius(), Player.GetRec())) {
                Ball.SetDirection();
				Ball.AddSpeed();
            }
            else if (CheckCollisionCircleRec(Ball.GetPosition(), Ball.GetRadius(), Enemy.GetRec())) {
                Ball.SetDirection();
				Ball.AddSpeed();
            }
                
            Player.Update();
			Enemy.Update(Ball.GetPosition().y);
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
