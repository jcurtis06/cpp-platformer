//
// Created by 06jcu on 8/15/2023.
//

#pragma once

#include "ray_utils.hpp"

struct GameManager {
    static std::vector<BoxCollider*> colliders;

    bool main_menu = true;
};