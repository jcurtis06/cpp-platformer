#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "raylib.h"

struct Vector2i {
    int x, y;
    Vector2i(int x, int y);

    Vector2i add(Vector2i other);

    Vector2i sub(Vector2i other);

    Vector2i mul(Vector2i other);

    Vector2i div(Vector2i other);

    Vector2i mod(Vector2i other);

    Vector2i distance_to(Vector2i other);

    Vector2 to_vector2();

    static Vector2i from_vector2(Vector2 vec);
};