//
// Created by 06jcu on 8/15/2023.
//

#pragma once

#include "ray_utils.hpp"

class Player {
public:
    bool froze = false;
    BoxCollider m_collider = { { 248, 300 }, { 8, 8 } };

    Vector2i& m_pos = m_collider.pos;
    Vector2i m_vel = { 0, 0 };

    void update();
    void draw();
private:
    float m_max_speed = 200;
    float m_gravity = 12;
    float m_jump_force = 200;

    float m_acceleration = 50;
    float m_deceleration = 0.2;

    float m_jump_buffer_time = 15;
    float m_jump_buffer_counter = 0;

    float m_coyote_time = 15;
    float m_coyote_counter = 0;
};
