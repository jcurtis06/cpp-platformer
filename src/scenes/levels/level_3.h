//
// Created by 06jcu on 8/18/2023.
//

#pragma once

#include "ray_utils.hpp"
#include "entities/player.h"
#include "entities/finish.h"
#include "entities/recharge.h"
#include "entities/enemy.h"

class Level3 : public Scene {
public:
    void on_enter() override;
    void update() override;
    void draw() override;
    void reload() override;
    void on_exit() override;
private:
    Player m_player;
    TileMap m_tile_map;
    Camera2D m_camera = { 0 };
    Finish m_finish;
    Recharge m_recharge;
};