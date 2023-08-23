//
// Created by 06jcu on 8/18/2023.
//

#include "game.hpp"
#include <cmath>
#include "GameManager.h"
#include "levels/level_1.hpp"
#include "raymath.h"
#include "scenes/levels/level_2.hpp"
#include "scenes/levels/level_3.h"

bool Game::m_is_enlarging = false;
bool Game::m_is_loading = false;
int Game::m_current_level = 0;
std::vector<Scene*> Game::m_levels;

float Game::m_time = 0;
float Game::m_shrink_speed = 0.2f;
float Game::m_vignette_size = 1.5f;
Vector2 Game::m_render_size = { 0, 0 };

Sound Game::m_next_level = LoadSound(ASSETS_PATH "/audio/next_level.wav");

void Game::on_enter() {
    m_next_level = LoadSound(ASSETS_PATH "/audio/next_level.wav");
    m_music = LoadMusicStream(ASSETS_PATH "/audio/music/level_1.wav");
    m_working_screen = LoadRenderTexture(GameManager::working_width, GameManager::working_height);

    m_levels.push_back(new Level1());
    m_levels.push_back(new Level2());
    m_levels.push_back(new Level3());

    m_levels[m_current_level]->on_enter();

    m_vignette = LoadShader(nullptr, ASSETS_PATH "/shaders/vignette.frag");

    Vector2 screen_size = { (float) GetScreenWidth(), (float) GetScreenHeight() };
    Vector2 working_size = { GameManager::working_width, GameManager::working_height };

    SetShaderValue(m_vignette, GetShaderLocation(m_vignette, "screenSize"), &screen_size, SHADER_UNIFORM_VEC2);
    SetShaderValue(m_vignette, GetShaderLocation(m_vignette, "logicalSize"), &working_size, SHADER_UNIFORM_VEC2);

    SetShaderValue(m_vignette, GetShaderLocation(m_vignette, "shrinkSpeed"), &m_shrink_speed, SHADER_UNIFORM_FLOAT);
    SetShaderValue(m_vignette, GetShaderLocation(m_vignette, "vignetteSize"), &m_vignette_size, SHADER_UNIFORM_FLOAT);

    PlayMusicStream(m_music);
}

void Game::update() {
    UpdateMusicStream(m_music);
    m_levels[m_current_level]->update();

    // --- SHADER UPDATE ---
    if (m_is_enlarging) {
        m_time = Lerp(m_time, 0, 0.1f);

        if (m_time < 0.01) {
            m_is_enlarging = false;
        }
    } else {
        if (m_is_loading) {
            m_time = Lerp(m_time, 50, 0.01f);
        } else {
            m_time += GetFrameTime();
        }
    }

    if (is_vignette_empty() && !m_is_loading) {
        m_is_enlarging = true;
        m_levels[m_current_level]->reload();
    }

    SetShaderValue(m_vignette, GetShaderLocation(m_vignette, "time"), &m_time, SHADER_UNIFORM_FLOAT);
}

void Game::draw() {
    BeginTextureMode(m_working_screen);
    ClearBackground(BLACK);
    m_levels[m_current_level]->draw();
    EndTextureMode();

    BeginDrawing();
    ClearBackground(BLACK);
    float scale = std::fmax(1.0f, floorf((float) GetRenderWidth() / (float) m_working_screen.texture.width));

    Rectangle src = { 0, 0, (float) m_working_screen.texture.width, (float) -m_working_screen.texture.height };
    Rectangle dest = { 0, 0, (float) src.width * scale, (float) -src.height * scale };

    dest.x = (float) GetRenderWidth() / 2 - dest.width / 2;
    dest.y = (float) GetRenderHeight() / 2 - dest.height / 2;

    m_render_size = { (float) dest.width, (float) dest.height };

    SetShaderValue(m_vignette, GetShaderLocation(m_vignette, "screenSize"), &m_render_size, SHADER_UNIFORM_VEC2);

    BeginShaderMode(m_vignette);
    DrawTexturePro(m_working_screen.texture, src, dest, { 0, 0 }, 0, WHITE);
    EndShaderMode();
    EndDrawing();
}

void Game::reload() {
    m_levels[m_current_level]->reload();
}

void Game::on_exit() {
    UnloadRenderTexture(m_working_screen);
    UnloadMusicStream(m_music);

    for (auto level : m_levels) {
        level->on_exit();
        delete level;
    }

}

bool Game::is_vignette_empty() {
    return ((m_vignette_size - (m_time * m_shrink_speed))/m_render_size.x < 0);
}

void Game::load_level(int level) {
    m_is_loading = true;
    m_levels[m_current_level]->on_exit();
    m_current_level = level;
    m_levels[m_current_level]->on_enter();
    PlaySound(m_next_level);
}
