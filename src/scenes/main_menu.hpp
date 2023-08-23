//
// Created by 06jcu on 8/18/2023.
//

#include "ray_utils.hpp"
#include "GameManager.h"

class MainMenu : public Scene {
public:
    void on_enter() override {

    }

    void update() override {

    }

    void draw() override {
        DrawText("Press ENTER to start", 10, 10, 20, WHITE);
    }

    void on_exit() override {

    }
};
