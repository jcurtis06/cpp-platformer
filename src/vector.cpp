#include "vector.hpp"

Vector2i::Vector2i(int x, int y) : x(x), y(y) {}

Vector2i Vector2i::add(Vector2i other) {
    return { x + other.x, y + other.y };
}

Vector2i Vector2i::sub(Vector2i other) {
    return { x - other.x, y - other.y };
}

Vector2i Vector2i::mul(Vector2i other) {
    return { x * other.x, y * other.y };
}

Vector2i Vector2i::div(Vector2i other) {
    return { x / other.x, y / other.y };
}

Vector2i Vector2i::mod(Vector2i other) {
    return { x % other.x, y % other.y };
}

Vector2i Vector2i::distance_to(Vector2i other) {
    return { x - other.x, y - other.y };
}

Vector2 Vector2i::to_vector2() {
    return { (float)x, (float)y };
}

Vector2i Vector2i::from_vector2(Vector2 vector) {
    return { (int)vector.x, (int)vector.y };
}
