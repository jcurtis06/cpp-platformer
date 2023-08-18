#include "tile_map.hpp"

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