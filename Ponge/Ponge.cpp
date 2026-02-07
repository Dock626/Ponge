// Pong.cpp : Defines the entry point for the application.
//

#include "Ponge.h"

using namespace std;

class Player {
private:
    Vector2 Position_;
    float Speed_ = 5.0f;
    float Current_Speed_;
public:
    Player(Vector2 Pos) {
        Position_ = Pos;
		Current_Speed_ = Speed_;
    }

    void Draw() {
        DrawRectangle(Position_.x, Position_.y, 20, 80, BLUE);
    }


    float GetY() {
        return Position_.y;
    }

    void Update() {
        if (IsKeyDown(KEY_LEFT_SHIFT)) Current_Speed_ = Speed_ * 4;
        else Current_Speed_ = Speed_;
        if (IsKeyDown(KEY_UP)) Position_.y -= Current_Speed_;
        if (IsKeyDown(KEY_DOWN)) { Position_.y += Current_Speed_; cout << Position_.y << "\n"; };
    }
};

int main()
{

    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    bool paused = false;
    Player Test(Vector2(screenWidth / 2 - 400, screenHeight / 2));
    InitWindow(screenWidth, screenHeight, "raylib [core] example - input keys");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        Test.Update();


        BeginDrawing();
        ClearBackground(RAYWHITE);
        Test.Draw();
        EndDrawing();
    }
    return 0;
}
