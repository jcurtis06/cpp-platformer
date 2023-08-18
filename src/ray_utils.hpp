//
// Created by 06jcu on 8/14/2023.
//

#pragma once

#include <cmath>
#include <map>
#include <fstream>
#include <iostream>
#include "raylib.h"
#include "vector.hpp"
#include "box_collider.hpp"

namespace RayUtils {
    Rectangle make_swept_box(Vector2i from, Vector2i to, int width, int height);

    void move_box_collider(BoxCollider& collider, Vector2i& vel, std::vector<BoxCollider*>& colliders);
}
