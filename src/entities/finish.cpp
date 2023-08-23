//
// Created by 06jcu on 8/15/2023.
//

#include "finish.h"

void Finish::draw() {
    DrawRectanglePro({ rect.x + 4, rect.y + 4, rect.width/2, rect.height/2 }, { 4, 4 }, GetTime()*4 * RAD2DEG, WHITE);
}

bool Finish::check_collision(Rectangle player_rect) {
    return CheckCollisionRecs(rect, player_rect);
}
