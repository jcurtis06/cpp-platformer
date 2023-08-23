//
// Created by 06jcu on 8/15/2023.
//

#pragma once

#include <vector>
#include <string>
#include "raylib.h"

class Finish {
public:
    std::vector<std::string> sources;
    Rectangle rect;

    void draw();
    bool check_collision(Rectangle player_rect);
};
