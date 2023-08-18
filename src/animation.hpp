#pragma once

#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include "raylib.h"
#include "vector.hpp"

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