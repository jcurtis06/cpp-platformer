//
// Created by 06jcu on 8/18/2023.
//

#include "level_2.hpp"
#include "GameManager.h"
#include "raymath.h"
#include "scenes/game.hpp"

void Level2::on_enter() {
    Texture2D tiles = LoadTexture(ASSETS_PATH "/sprites/tiles.png");

    m_tile_map.tile_size = 8;
    m_tile_map.tile_textures["tiles"] = tiles;
    m_tile_map.load(ASSETS_PATH "/levels/level_2.json");
    m_tile_map.add_collisions("tiles", GameManager::colliders);

    m_camera.zoom = 1.0f;
    m_camera.offset = {
            GameManager::working_width / 2,
            GameManager::working_height / 2
    };

    m_player.froze = true;

    m_finish.rect = {807, 320, 16, 16};
}

void Level2::update() {
    std::cout << m_tile_map.is_loaded() << std::endl;
    if (m_tile_map.is_loaded() && Game::is_vignette_empty()) {
       Game::m_is_loading = false;
       m_player.froze = false;
   }

    m_player.update();

    m_camera.target.x = Lerp(m_camera.target.x, (float) m_player.m_pos.x, 0.1f);
    m_camera.target.y = Lerp(m_camera.target.y, (float) m_player.m_pos.y, 0.1f);

    m_camera.offset = {
            GameManager::working_width / 2,
            GameManager::working_height / 2
    };

    if (m_player.m_pos.y > 500) {
        reload();
    }

    if (m_finish.check_collision(m_player.m_collider.to_rect())) {
        Game::load_level(2);
    }
}

void Level2::draw() {
    BeginMode2D(m_camera);
    m_player.draw();
    m_tile_map.draw();
    m_finish.draw();
    EndMode2D();
}

void Level2::reload() {
    m_player.m_pos = {248, 300};

    Game::m_is_enlarging = true;
    m_player.on_death();
}

void Level2::on_exit() {
    GameManager::colliders.clear();
}