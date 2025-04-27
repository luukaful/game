//
// Created by luukd on 27/04/2025.
//

#include "map.h"
#include <json.hpp>
#include <fstream>
#include <iostream>

Map::Map() : breedte(0), hoogte(0) {}

bool Map::loadFromFile(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open map file: " << filePath << std::endl;
        return false;
    }

    nlohmann::json jsonData;
    file >> jsonData;

    map_data = jsonData["mapdata"].get<std::vector<std::vector<int>>>();
    hoogte = map_data.size();
    breedte = map_data[0].size();

    if (!tileTexture.loadFromFile("assets/tiles/tile.png")) {
        std::cerr << "Failed to load tile texture." << std::endl;
        return false;
    }
    tileSprite.setTexture(tileTexture);

    return true;
}

void Map::render(sf::RenderWindow& window) {
    for (int y = 0; y < hoogte; ++y) {
        for (int x = 0; x < breedte; ++x) {
            int tileValue = map_data[y][x];
            if (tileValue != 0x00) { // Skip empty tiles
                tileSprite.setPosition(x * 32.0f, y * 32.0f); // Assuming 32x32 tiles
                window.draw(tileSprite);
            }
        }
    }
}
