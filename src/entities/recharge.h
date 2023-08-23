//
// Created by 06jcu on 8/18/2023.
//

#pragma once

#include <vector>
#include <string>
#include "raylib.h"

class Recharge {
public:
    bool m_used = false;

    std::vector<std::string> sources;
    Rectangle rect;
    Texture2D texture = LoadTexture(ASSETS_PATH "/sprites/recharge.png");

    void draw();
    bool check_collision(Rectangle player_rect);
};