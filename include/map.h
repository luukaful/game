//
// Created by luukd on 27/04/2025.
//

#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Map {
    std::vector<std::vector<int>> map_data;
    int breedte;
    int hoogte;
    sf::Texture tileTexture;
    sf::Sprite tileSprite;

public:
    Map();
    bool loadFromFile(const std::string& filePath);
    void render(sf::RenderWindow& window);
};



#endif //MAP_H
