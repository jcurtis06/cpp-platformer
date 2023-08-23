//
// Created by 06jcu on 8/15/2023.
//

#pragma once

#include "ray_utils.hpp"

class Player {
public:
    bool froze = false;
    bool dashing = false;

    BoxCollider m_collider = { { 248, 300 }, { 8, 8 } };

    Vector2i& m_pos = m_collider.pos;
    Vector2i m_vel = { 0, 0 };

    void update();
    void draw();
    void on_death();
private:
    float m_max_speed = 100;
    float m_gravity = 12;
    float m_jump_force = 200;

    float m_acceleration = 40;
    float m_deceleration = 0.2;

    float m_jump_buffer_time = 15;
    float m_jump_buffer_counter = 0;

    float m_coyote_time = 15;
    float m_coyote_counter = 0;

    float m_dash_time = 0.2;
    float m_dash_counter = 0;
    float m_dash_multiplier = 1.2;

    Animation m_idle_anim = {
            LoadTexture(ASSETS_PATH "/sprites/player_idle.png"),
            4,
            1,
            0,
            3,
            0.1
    };

    Animation m_run_anim = {
            LoadTexture(ASSETS_PATH "/sprites/player_run.png"),
            3,
            1,
            0,
            2,
            0.1
    };

    Sound m_jump_sound = LoadSound(ASSETS_PATH "/audio/jump.wav");
    Sound m_death_sound = LoadSound(ASSETS_PATH "/audio/dead.wav");
    Sound m_dash_sound = LoadSound(ASSETS_PATH "/audio/dash.wav");
};
