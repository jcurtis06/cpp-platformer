//
// Created by 06jcu on 8/15/2023.
//

#include "ray_utils.hpp"

// --- VECTOR2I ---
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

// --- BOX COLLIDER ---
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

// --- ANIMATION ---
Animation::Animation(const Texture2D& texture, int h_frames, int v_frames, int start_frame, int end_frame, float frame_duration)
        : texture(texture), h_frames(h_frames), v_frames(v_frames), start_frame(start_frame), end_frame(end_frame), frame_duration(frame_duration) { current_frame = start_frame; }
void Animation::draw(Vector2i pos) {
    timer += GetFrameTime();

    if (timer >= frame_duration) {
        current_frame++;
        timer = 0;
    }

    if (current_frame > end_frame) {
        current_frame = start_frame;
    }

    int x = current_frame % h_frames;
    int y = current_frame / h_frames;

    Rectangle source{
            (float)(texture.width / h_frames * x),
            (float)(texture.height / v_frames * y),
            (float)(texture.width / h_frames),
            (float)(texture.height / v_frames)
    };

    DrawTextureRec(texture, source, { (float)pos.x, (float)pos.y }, WHITE);
}

// --- TILE ---
nlohmann::json Tile::to_json() {
    return {
        {"x", x},
        {"y", y},
        {"variant", variant},
        {"type", type}
    };
}

Tile Tile::from_json(nlohmann::json json) {
    Tile tile;
    tile.x = json["x"];
    tile.y = json["y"];
    tile.variant = json["variant"];
    tile.type = json["type"];
    return tile;
}

// --- TILE MAP ---
void TileMap::load(const std::string &path) {
    std::ifstream file(path);

    if (!file.is_open()) {
        std::cerr << "Failed to load TileMap: " << path << std::endl;
    }

    nlohmann::json json;

    file >> json;
    file.close();

    loaded_tiles.clear();

    for (const auto &item: json) {
        loaded_tiles.push_back(Tile::from_json(item));
    }

    std::cout << "Loaded " << loaded_tiles.size() << " tiles" << std::endl;
}

bool TileMap::is_loaded() {
    return !loaded_tiles.empty();
}

void TileMap::draw() {
    for (const auto &tile: loaded_tiles) {
        if (tile_textures.find(tile.type) == tile_textures.end()) {
            std::cerr << "Tile type " << tile.type << " not found in tile textures" << std::endl;
            continue;
        }

        const Texture2D &texture = tile_textures.at(tile.type);

        const int t_size = tile_size;
        int h_tiles = texture.width / tile_size;

        Rectangle source{
                (float)(t_size * (tile.variant % h_tiles)),
                (float)(t_size * (tile.variant / h_tiles)),
                (float)t_size, (float)t_size };

        DrawTextureRec(texture, source, Vector2{ (float)tile.x, (float)(tile.y) }, WHITE);
    }
}

void TileMap::add_collisions(std::string type, std::vector<BoxCollider *> &colliders) {
    for (auto& tile : loaded_tiles) {
        if (tile.type == type) {
            Vector2i pos{ tile.x, tile.y };

            colliders.push_back(new BoxCollider{
                pos,
                Vector2i{ tile_size, tile_size }
            });
        }
    }
}

// --- RAY UTILS ---
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