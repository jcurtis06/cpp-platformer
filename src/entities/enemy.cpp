//
// Created by 06jcu on 8/18/2023.
//

#include "enemy.h"
#include "raymath.h"

void Enemy::update() {
    if (!m_is_alive) return;
    if (Vector2Distance({rect.x, rect.y}, end_point) <= 1) {
        Vector2 temp = end_point;
        end_point = start_point;
        start_point = temp;
    }

    // move towards end point
    Vector2 dir = Vector2Normalize(Vector2Subtract(end_point, {rect.x, rect.y}));
    rect.x += dir.x * 2;
    rect.y += dir.y * 2;
}

void Enemy::draw() {
    if (!m_is_alive) return;
    DrawRectanglePro({ rect.x + 4, rect.y + 4, rect.width/2, rect.height/2 }, { 4, 4 }, 0, WHITE);
}

void Enemy::on_death() {
    PlaySound(m_death_sound);
}

bool Enemy::check_collision(Rectangle player_rect) {
    if (!m_is_alive) return false;
    return CheckCollisionRecs(rect, player_rect);
}
