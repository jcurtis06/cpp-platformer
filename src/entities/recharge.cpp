//
// Created by 06jcu on 8/18/2023.
//

#include <cmath>
#include "recharge.h"

void Recharge::draw() {
    if (m_used) return;
    rect.y = rect.y + 0.05f * sinf(GetTime() * 5.0f);

    DrawTexturePro(texture, {0, 0, (float) texture.width, (float) texture.height},
                   {rect.x, rect.y, rect.width, rect.height}, {3, 3}, 0.0f, WHITE);
}

bool Recharge::check_collision(Rectangle player_rect) {
    if (m_used) return false;
    return CheckCollisionRecs(rect, player_rect);
}
