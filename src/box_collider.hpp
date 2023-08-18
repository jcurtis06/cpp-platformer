#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "vector.hpp"
#include "raylib.h"

struct BoxCollider {
    BoxCollider(Vector2i pos, Vector2i size);

    Vector2i pos;
    Vector2i size;
    bool on_ground = false;

    Rectangle to_rect();

    int left();

    int right();

    int top();

    int bottom();
};