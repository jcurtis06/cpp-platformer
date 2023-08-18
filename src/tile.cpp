#include "tile.hpp"

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