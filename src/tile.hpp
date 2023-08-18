#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "raylib.h"
#include "nlohmann/json.hpp"

struct Tile {
    int x, y;
    int variant;
    std::string type;

    nlohmann::json to_json();

    static Tile from_json(nlohmann::json json);
};