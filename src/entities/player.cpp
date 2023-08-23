//
// Created by 06jcu on 8/15/2023.
//

#include "player.h"
#include "GameManager.h"
#include "raymath.h"

void Player::update() {
    if (froze) {
        return;
    }

    if (!m_collider.on_ground) {
        if (m_coyote_counter > 0) {
            m_coyote_counter--;
        }

        m_vel.y += m_gravity;

        if (m_vel.y > 2000) {
            m_vel.y = 2000;
        }

        std::cout << m_vel.y << std::endl;
    } else {
        m_coyote_counter = m_coyote_time;
        m_vel.y = 1;
    }

    if (!dashing) {
        if (IsKeyDown(KEY_RIGHT)) {
            m_vel.x += m_acceleration;
        } else if (IsKeyDown(KEY_LEFT)) {
            m_vel.x -= m_acceleration;
        } else {
            m_vel.x = Lerp(m_vel.x, 0, m_deceleration);
        }

        m_vel.x = Clamp(m_vel.x, -m_max_speed, m_max_speed);
    }

    if (IsKeyPressed(KEY_SPACE)) {
        m_jump_buffer_counter = m_jump_buffer_time;
    }

    if (m_jump_buffer_counter > 0) {
        m_jump_buffer_counter--;
    }

    if (m_jump_buffer_counter > 0 && m_coyote_counter > 0) {
        PlaySound(m_jump_sound);
        m_vel.y = -m_jump_force;
        m_jump_buffer_counter = 0;
        m_coyote_counter = 0;
    }

    if (IsKeyReleased(KEY_SPACE)) {
        if (m_vel.y < 0) {
            m_vel.y = 50;
        }
    }

    if (IsKeyPressed(KEY_LEFT_SHIFT)) {
        PlaySound(m_dash_sound);
        dashing = true;
    }

    if (dashing) {
        m_dash_counter += GetFrameTime();

        m_vel.x *= m_dash_multiplier;

        if (m_dash_counter > m_dash_time) {
            dashing = false;
            m_dash_counter = 0;
        }
    }

    std::cout << m_pos.x << ", " << m_pos.y << std::endl;

    RayUtils::move_box_collider(m_collider, m_vel, GameManager::colliders);
}

void Player::draw() {
    if (m_vel.x > 10) {
        m_run_anim.flip_h = false;
        m_run_anim.draw({m_pos.x, m_pos.y-1});
    } else if (m_vel.x < -10) {
        m_run_anim.flip_h = true;
        m_run_anim.draw({m_pos.x, m_pos.y-1});
    } else {
        m_idle_anim.flip_h = m_run_anim.flip_h;
        m_idle_anim.draw({m_pos.x, m_pos.y-1});
    }
}

void Player::on_death() {
    PlaySound(m_death_sound);
}
