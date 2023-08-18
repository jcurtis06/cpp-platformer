#include "box_collider.hpp"

BoxCollider::BoxCollider(Vector2i pos, Vector2i size)
    : pos(pos), size(size) {}

Rectangle BoxCollider::to_rect() {
    return { (float)pos.x, (float)pos.y, (float)size.x, (float)size.y };
}

int BoxCollider::left() {
    return pos.x;
}

int BoxCollider::right() {
    return pos.x + size.x;
}

int BoxCollider::top() {
    return pos.y;
}

int BoxCollider::bottom() {
    return pos.y + size.y;
}
