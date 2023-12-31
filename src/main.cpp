#include "entities/player.h"
#include "tile_map.hpp"
#include "box_collider.hpp"
#include "GameManager.h"
#include "raymath.h"
#include "entities/finish.h"

std::vector<BoxCollider*> GameManager::colliders = std::vector<BoxCollider*>();

int main() {
    SetTraceLogLevel(LOG_WARNING);

    const int window_width = 800;
    const int window_height = 450;

    const int logical_width = 400;
    const int logical_height = 225;

    float shrink_speed = 0.1f;
    float vignette_size = 1.5f;

    InitWindow(window_width, window_height, "Long Walk Home");
    SetTargetFPS(60);

    Camera2D camera = {0};
    camera.target = (Vector2){0, 100};
    camera.offset = (Vector2){logical_width / 2, logical_height / 2};
    camera.zoom = 1.0f;

    Camera2D screen_camera = {0};
    screen_camera.target = {0, 0};
    screen_camera.offset = {0, 0};
    screen_camera.zoom = 1.0f;

    RenderTexture2D target = LoadRenderTexture(logical_width, logical_height);

    Shader vignette = LoadShader(nullptr, "vignette.frag");

    Vector2 screenSize = {(float)window_width, (float)window_height};
    SetShaderValue(vignette, GetShaderLocation(vignette, "screenSize"), &screenSize, SHADER_UNIFORM_VEC2);

    Vector2 logicalSize = {(float)logical_width, (float)logical_height};
    SetShaderValue(vignette, GetShaderLocation(vignette, "logicalSize"), &logicalSize, SHADER_UNIFORM_VEC2);

    SetShaderValue(vignette, GetShaderLocation(vignette, "shrinkSpeed"), &shrink_speed, SHADER_UNIFORM_FLOAT);
    SetShaderValue(vignette, GetShaderLocation(vignette, "vignetteSize"), &vignette_size, SHADER_UNIFORM_FLOAT);

    SetTextureFilter(target.texture, TEXTURE_FILTER_POINT);

    bool main_menu = false;

    // --- ENTITY CREATION ---
    Player player;
    Finish finish;
    finish.rect = {562, 320, 16, 16};

    // --- TILE MAP CREATION ---
    TileMap tile_map;
    tile_map.tile_size = 8;
    tile_map.tile_textures["tiles"] = LoadTexture("tiles.png");
    tile_map.load("level1.json");
    tile_map.add_collisions("tiles", GameManager::colliders);

    float time = 0;
    int selection = 0;
    bool is_enlarging = false;
    bool loading = false;

    // -- GAME LOOP ---
    while (!WindowShouldClose()) {
        if (!main_menu) {
           if (is_enlarging) {
               time = Lerp(time, 0, 0.1f);
               SetShaderValue(vignette, GetShaderLocation(vignette, "time"), &time, SHADER_UNIFORM_FLOAT);

               if (time < 0.01) {
                   is_enlarging = false;
               }
           } else {
               if (loading) {
                   time = Lerp(time, 50, 0.01f);
               } else {
                   time += GetFrameTime();
               }
               SetShaderValue(vignette, GetShaderLocation(vignette, "time"), &time, SHADER_UNIFORM_FLOAT);
           }

           // --- UPDATE ---
           player.update();

           camera.target.x = Lerp(camera.target.x, (float) player.m_pos.x, 0.1f);
           camera.target.y = Lerp(camera.target.y, (float) player.m_pos.y, 0.1f);

           if (CheckCollisionRecs(player.m_collider.to_rect(), finish.rect) && !loading) {
               loading = true;
               player.froze = true;

               GameManager::colliders.clear();
               tile_map.load("level2.json");
               tile_map.add_collisions("tiles", GameManager::colliders);
           }

           if (tile_map.is_loaded() && (((vignette_size - (time * shrink_speed))/screenSize.x < 0))) {
               loading = false;
               player.froze = false;
           }

           if (player.m_pos.y > 500 || (((vignette_size - (time * shrink_speed))/screenSize.x < 0) && !loading)) {
               is_enlarging = true;
               player.m_pos = {248, 300};
           }
        }

        BeginTextureMode(target);
        ClearBackground({24, 20, 37, 255});
        BeginMode2D(camera);

        // --- DRAWING ---
        if (!main_menu) {
            if (!loading) {
                tile_map.draw();
                finish.draw();
            }

            player.draw();
        }

        EndMode2D();
        EndTextureMode();

        BeginDrawing();
        ClearBackground({24, 20, 37, 255});
        BeginShaderMode(vignette);
        Rectangle sourceRec = {0, 0, (float)target.texture.width, (float)-target.texture.height};
        Rectangle destRec = {0, 0, (float)window_width, (float)window_height};
        Vector2 origin = {0, 0};
        DrawTexturePro(target.texture, sourceRec, destRec, origin, 0, WHITE);

        EndShaderMode();

        // --- UI ---
        if (main_menu) {
            DrawText("Long Walk Home", 10, 10, 20, WHITE);
        }

        EndDrawing();
    }

    UnloadShader(vignette);
    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}