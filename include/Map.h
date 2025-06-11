#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <unordered_map>

class Map {
public:
    Map();
    bool loadFromFile(const std::string& tmxFile);
    void draw(sf::RenderWindow& window, const sf::View& view);

private:
    tmx::Map m_map;
    std::unordered_map<unsigned, sf::Texture> m_tileTextures; // tileId -> texture
    std::vector<sf::Sprite> m_tileSprites;
    unsigned m_mapWidth = 0;
    unsigned m_mapHeight = 0;
    unsigned m_tileWidth = 0;
    unsigned m_tileHeight = 0;
    void buildSprites();
    bool loadTilesetCollection(const std::string& tsxPath, unsigned firstGid, const std::string& tmxDir);
};
