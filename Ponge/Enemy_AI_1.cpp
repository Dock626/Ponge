#include "Enemy_AI_1.h"
#include <cmath>

void Enemy_AI_Type_1::Update(Vector2 ball) {
    float center = Position_.y + Rect_Height_ / 2;
    float screenCenter = ScreenHeight / 2;

    if (ball.x < ScreenWidth / 2) {  // ball on left → go to center immediately
        if (center > screenCenter + 5) Position_.y -= Speed_ * 0.6f;
        else if (center < screenCenter - 5) Position_.y += Speed_ * 0.6f;
    }
    else {  // ball on right → track ball with reaction delay
        // increment timer only on right side
        reactionTimer += GetFrameTime();
        if (reactionTimer >= reactionDelay) {
            targetY = ball.y;
            reactionTimer = 0.0f;
        }

        float moveSpeed = Speed_ * 0.8f;
        if (targetY > center + 30 && Position_.y < ScreenHeight - Rect_Height_) Position_.y += moveSpeed;
        else if (targetY < center - 30 && Position_.y > 0) Position_.y -= moveSpeed;
    }
}