#pragma once
#pragma once
#include "Enemy.h"

class Enemy_AI_Type_1 : public Enemy {
public:
    using Enemy::Enemy;
    void Update(Vector2 ball) override;
};