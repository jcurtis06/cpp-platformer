//
// Created by 06jcu on 8/15/2023.
//

#include "ray_utils.hpp"

Rectangle RayUtils::make_swept_box(Vector2i from, Vector2i to, int width, int height) {
    float x = std::min(from.x, to.x);
    float y = std::min(from.y, to.y);

    float w = std::abs(to.x - from.x) + (float) width;
    float h = std::abs(to.y - from.y) + (float) height;

    return { x, y, w, h };
}

void RayUtils::move_box_collider(BoxCollider& collider, Vector2i& vel, std::vector<BoxCollider*>& colliders) {
    Vector2i old_pos = collider.pos;

    Vector2 f_vel = vel.to_vector2();
    f_vel.x = roundf(f_vel.x * GetFrameTime());
    f_vel.y = roundf(f_vel.y * GetFrameTime());

    Vector2i new_pos = old_pos.add({(int) f_vel.x, 0});

    Rectangle horizontal = make_swept_box(old_pos, new_pos, collider.size.x, collider.size.y);
    int closest_valid_x = new_pos.x;

    collider.on_ground = false;
    bool collided_h = false;
    bool collided_y = false;

    for (auto& rect : colliders) {
        if (CheckCollisionRecs(rect->to_rect(), horizontal)) {
            if (vel.x > 0) {
                closest_valid_x = rect->left() - collider.size.x;
            } else {
                closest_valid_x = rect->right();
            }

            collided_h = true;
            break;
        }
    }

    new_pos = old_pos.add({ 0, (int) f_vel.y });
    Rectangle vertical = make_swept_box(old_pos, new_pos, collider.size.x, collider.size.y);
    int closest_valid_y = new_pos.y;

    for (auto& rect : colliders) {
        if (CheckCollisionRecs(rect->to_rect(), vertical)) {
            if (vel.y > 0) {
                closest_valid_y = rect->top() - collider.size.y;
                collider.on_ground = true;
            } else {
                closest_valid_y = rect->bottom();
            }

            collided_y = true;
            break;
        }
    }

    if (collided_h && collided_y) {
        collider.pos.x = closest_valid_x;
        collider.pos.y = old_pos.y;
    } else {
        collider.pos.x = closest_valid_x;
        collider.pos.y = closest_valid_y;
    }
}