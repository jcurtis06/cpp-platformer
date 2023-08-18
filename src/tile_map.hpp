#pragma once

#include <fstream>
#include <iostream>
#include "raylib.h"
#include "nlohmann/json.hpp"
#include "box_collider.hpp"
#include "tile.hpp"

struct TileMap {
    int tile_size;
    std::map<std::string, Texture2D> tile_textures;
    std::vector<Tile> loaded_tiles;

    void load(const std::string &path);
    void draw();
    void add_collisions(std::string type, std::vector<BoxCollider*>& colliders);
    bool is_loaded();
};
