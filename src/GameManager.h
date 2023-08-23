//
// Created by 06jcu on 8/15/2023.
//

#pragma once

#include "ray_utils.hpp"
#include <string>

struct GameManager {
    static std::vector<BoxCollider*> colliders;
    static std::map<std::string, Scene*> scenes;
    static Scene* current_scene;

    constexpr static float working_width = 320;
    constexpr static float working_height = 180;

    static void set_current_scene(std::string scene_name) {
        current_scene = scenes[scene_name];
        current_scene->on_enter();
    }

    static void cleanup() {
        for (auto& collider : colliders) {
            delete collider;
        }
        for (auto& scene : scenes) {
            delete scene.second;
        }
    }
};