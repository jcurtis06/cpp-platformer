//
// Created by 06jcu on 8/18/2023.
//
#pragma once

#include "ray_utils.hpp"

class Game : public Scene {
public:
    static bool m_is_enlarging;
    static bool m_is_loading;
    static int m_current_level;
public:
    void on_enter() override;

    void update() override;

    void draw() override;

    void reload() override;

    void on_exit() override;

    static void load_level(int level);
    static bool is_vignette_empty();
private:
    RenderTexture m_working_screen;
    static std::vector<Scene*> m_levels;
    Shader m_vignette;
    Music m_music;

    static Sound m_next_level;
    static Vector2 m_render_size;
    static float m_time;
    static float m_shrink_speed;
    static float m_vignette_size;
};
