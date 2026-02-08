// Pong.cpp : Defines the entry point for the application.
//

#include "Ponge.h"

using namespace std;

class Player {
private:
    Vector2 Position_;
    float Speed_ = 5.0f;
    float Current_Speed_;
    int Screen_Height_;
	int Rect_Height_;
	int Rect_Width_;

public:
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
        if (IsKeyDown(KEY_LEFT_SHIFT)) Current_Speed_ = Speed_ * 4;
        else Current_Speed_ = Speed_;
        if (IsKeyDown(KEY_UP) and Position_.y >= 0) Position_.y -= Current_Speed_;
        if (IsKeyDown(KEY_DOWN) and Position_.y <= Screen_Height_ - Rect_Height_) { Position_.y += Current_Speed_; cout << Position_.y << "\n"; };
    }
};

int main()
{

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    bool paused = false;
    Player Test(Vector2(screenWidth / 2 - 400, screenHeight / 2), screenHeight, 20, 80);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
		// Update
        Test.Update();


		// Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);
        Test.Draw();
        EndDrawing();
    }
    return 0;
}
