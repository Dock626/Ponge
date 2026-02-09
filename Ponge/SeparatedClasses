#include "Player.h"

Player::Player(Vector2 Pos, int Game_Screen_Height, int Width, int Height) {
    Position_ = Pos;
    Current_Speed_ = Speed_;
    Screen_Height_ = Game_Screen_Height;
    Rect_Height_ = Height;
    Rect_Width_ = Width;
}

void Player::Draw() {
    DrawRectangle(Position_.x, Position_.y, Rect_Width_, Rect_Height_, BLUE);
}

void Player::Update() {
    if (IsKeyDown(KEY_LEFT_SHIFT)) Current_Speed_ = Speed_ * 2;
    else Current_Speed_ = Speed_;
    if (IsKeyDown(KEY_UP) && Position_.y >= 0) {
        Position_.y -= Current_Speed_;
        is_moving_ = true;
    }
    else is_moving_ = false;
    if (IsKeyDown(KEY_DOWN) && Position_.y <= Screen_Height_ - Rect_Height_) Position_.y += Current_Speed_;
}

Vector2 Player::GetPosition() { return Position_; }
float Player::GetSpeed() { return Current_Speed_; }

Rectangle Player::GetRec() {
    Rectangle rec;
    rec.x = Position_.x;
    rec.y = Position_.y;
    rec.width = Rect_Width_;
    rec.height = Rect_Height_;
    return rec;
}
int Player::GetHeight() { return Rect_Height_; }