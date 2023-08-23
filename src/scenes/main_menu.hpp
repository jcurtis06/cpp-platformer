//
// Created by 06jcu on 8/18/2023.
//

#include "ray_utils.hpp"
#include "GameManager.h"

class MainMenu : public Scene {
public:
    Music music;

    void on_enter() override {
        m_title_width = MeasureText("Long Walk Home", 30);
        SetTextureFilter(GetFontDefault().texture, TEXTURE_FILTER_POINT);

        music = LoadMusicStream(ASSETS_PATH "/audio/music/main_menu.wav");

        PlayMusicStream(music);
    }

    void update() override {
        UpdateMusicStream(music);

        if (IsKeyPressed(KEY_ENTER)) {
            GameManager::set_current_scene("game");
        }
    }

    void draw() override {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawText("Long Walk Home", GetScreenWidth() / 2 - m_title_width / 2, 100, 30, WHITE);
        DrawText("Press ENTER", GetScreenWidth() / 2 - MeasureText("Press ENTER", 20) / 2, 200, 20, WHITE);
        EndDrawing();
    }

    void reload() override {

    }

    void on_exit() override {
        UnloadMusicStream(music);
    }
private:
    int m_title_width = 0;
};
