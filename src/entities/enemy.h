//
// Created by 06jcu on 8/18/2023.
//

#pragma once

#include "raylib.h"

class Enemy {
public:
    bool m_is_alive = true;

    Rectangle rect;

    void update();
    void draw();
    void on_death();
    bool check_collision(Rectangle player_rect);

    Vector2 start_point;
    Vector2 end_point;

    Sound m_death_sound = LoadSound(ASSETS_PATH "/audio/dead.wav");
};