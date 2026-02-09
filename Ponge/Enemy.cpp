#include "Enemy.h"

Enemy::Enemy(Vector2 Pos, int Game_Screen_Height, int Game_Screen_Width, int Width, int Height)
    : reactionDelay(0.1f), reactionTimer(0.0f), targetY(0.0f), Speed_(4.95f) {
    Position_ = Pos;
    ScreenHeight = Game_Screen_Height;
    ScreenWidth = Game_Screen_Width;
    Rect_Height_ = Height;
    Rect_Width_ = Width;
}

void Enemy::Update(Vector2 ball) {
    float center = Position_.y + Rect_Height_ / 2;
    if (ball.y > center && Position_.y < ScreenHeight - Rect_Height_) Position_.y += Speed_;
    else if (ball.y < center && Position_.y > 0) Position_.y -= Speed_;
}

Enemy::~Enemy() = default;

void Enemy::Draw() { DrawRectangle(Position_.x, Position_.y, Rect_Width_, Rect_Height_, GREEN); }
Vector2 Enemy::GetPosition() { return Position_; }
int Enemy::GetHeight() { return Rect_Height_; }

Rectangle Enemy::GetRec() {
    Rectangle rec;
    rec.x = Position_.x;
    rec.y = Position_.y;
    rec.width = Rect_Width_;
    rec.height = Rect_Height_;
    return rec;
}