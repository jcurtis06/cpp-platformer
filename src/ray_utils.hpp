//
// Created by 06jcu on 8/14/2023.
//

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

struct Animation {
    Texture2D texture;
    int h_frames, v_frames;
    int start_frame, end_frame;
    int current_frame;

    float frame_duration;
    float timer = 0;

    Animation(const Texture2D& texture,
               int h_frames, int v_frames,
               int start_frame, int end_frame,
               float frame_duration);

    void draw(Vector2i pos);
};

struct Tile {
    int x, y;
    int variant;
    std::string type;

    nlohmann::json to_json();

    static Tile from_json(nlohmann::json json);
};

struct TileMap {
    int tile_size;
    std::map<std::string, Texture2D> tile_textures;
    std::vector<Tile> loaded_tiles;

    void load(const std::string &path);
    void draw();
    void add_collisions(std::string type, std::vector<BoxCollider*>& colliders);
    bool is_loaded();
};

namespace RayUtils {
    Rectangle make_swept_box(Vector2i from, Vector2i to, int width, int height);

    void move_box_collider(BoxCollider& collider, Vector2i& vel, std::vector<BoxCollider*>& colliders);
}
