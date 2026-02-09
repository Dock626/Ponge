// Pong.cpp : Defines the entry point for the application.
// Updated to use separated classes.

#include "Ponge.h"
#include "Player.h"
#include "Ball.h"
#include "Enemy_AI_1.h"
#include <cmath>

using namespace std;

const int screenHeight = 700;
const int screenWidth = 1000;

int main() {
    float serveTimer = 0.0f;
    bool waitingToServe = false;
    bool paused = false;
    int playerScore = 0;
    int enemyScore = 0;

    Player Player(Vector2{ (float)screenWidth / 2 - 450.0f, (float)screenHeight / 2 }, screenHeight, 20, 80);
    Ball Ball(Vector2{ (float)screenWidth / 2 , (float)screenHeight / 2 }, 10, screenHeight, screenWidth);
    Enemy_AI_Type_1 Enemy(Vector2{ (float)screenWidth / 2 + 430.0f, (float)screenHeight / 2 }, screenHeight, screenWidth, 20, 80);

    InitWindow(screenWidth, screenHeight, "Pong");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Check scoring
        if (Ball.GetPosition().x < 10) {
            enemyScore++;
            waitingToServe = true;
            serveTimer = 0.0f;
            Ball.SetPosition(Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 });
        }
        else if (Ball.GetPosition().x > screenWidth - 10) {
            playerScore++;
            waitingToServe = true;
            serveTimer = 0.0f;
            Ball.SetPosition(Vector2{ (float)screenWidth / 2, (float)screenHeight / 2 });
        }

        if (!waitingToServe) {
            // Collisions
            if (CheckCollisionCircleRec(Ball.GetPosition(), Ball.GetRadius(), Player.GetRec())) {
                float paddleCenter = Player.GetPosition().y + Player.GetHeight() / 2;
                float relativeY = Ball.GetPosition().y - paddleCenter;
                float normalizedY = relativeY / (Player.GetHeight() / 2);
                float maxAngle = 60 * (PI / 180);
                float angle = normalizedY * maxAngle;
                Ball.SetAngle(angle, false);
                Ball.AddSpeed();
            }

            if (CheckCollisionCircleRec(Ball.GetPosition(), Ball.GetRadius(), Enemy.GetRec())) {
                float paddleCenter = Enemy.GetPosition().y + Enemy.GetHeight() / 2;
                float relativeY = Ball.GetPosition().y - paddleCenter;
                float normalizedY = relativeY / (Enemy.GetHeight() / 2);
                float maxAngle = 60 * (PI / 180);
                float angle = normalizedY * maxAngle;
                Ball.SetAngle(angle, true);
                Ball.AddSpeed();
            }

            // Normal updates
            Ball.Update();
        }
        else {
            // Serve pause
            serveTimer += GetFrameTime();
            if (serveTimer >= 2.0f) {
                Ball.Reset(screenWidth, screenHeight);
                waitingToServe = false;
            }
        }

        Player.Update();
        Enemy.Update(Ball.GetPosition());

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText(TextFormat("%i", playerScore), screenWidth / 4, 20, 40, BLUE);
        DrawText(TextFormat("%i", enemyScore), screenWidth * 3 / 4, 20, 40, GREEN);

        Player.Draw();
        Enemy.Draw();
        Ball.Draw();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}