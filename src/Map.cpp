#include <Map.h>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/Property.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <filesystem>
#include <tinyxml2.h>

Map::Map() {}

bool Map::loadFromFile(const std::string& tmxFile) {
    if (!std::filesystem::exists(tmxFile)) {
        std::cerr << "TMX file does not exist: " << tmxFile << std::endl;
        return false;
    }
    if (!m_map.load(tmxFile)) {
        std::cerr << "Failed to load TMX map: " << tmxFile << std::endl;
        return false;
    }
    m_mapWidth = m_map.getTileCount().x;
    m_mapHeight = m_map.getTileCount().y;
    m_tileWidth = m_map.getTileSize().x;
    m_tileHeight = m_map.getTileSize().y;

    // Parse TMX file with tinyxml2 to get the correct TSX path for each tileset
    tinyxml2::XMLDocument tmxDoc;
    if (tmxDoc.LoadFile(tmxFile.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to parse TMX file with tinyxml2: " << tmxFile << std::endl;
        return false;
    }
    std::unordered_map<unsigned, std::string> firstGidToTsxPath;
    auto* mapElem = tmxDoc.FirstChildElement("map");
    if (mapElem) {
        for (auto* tilesetElem = mapElem->FirstChildElement("tileset"); tilesetElem; tilesetElem = tilesetElem->NextSiblingElement("tileset")) {
            unsigned firstgid = tilesetElem->UnsignedAttribute("firstgid");
            const char* sourceAttr = tilesetElem->Attribute("source");
            if (sourceAttr) {
                std::string tmxDir = std::filesystem::path(tmxFile).parent_path().string();
                std::string tsxPath = std::filesystem::weakly_canonical(std::filesystem::path(tmxDir) / sourceAttr).string();
                firstGidToTsxPath[firstgid] = tsxPath;
            }
        }
    }

    // Load tileset collections
    m_tileTextures.clear();
    for (const auto& tileset : m_map.getTilesets()) {
        auto it = firstGidToTsxPath.find(tileset.getFirstGID());
        if (it == firstGidToTsxPath.end()) {
            std::cerr << "Could not find TSX path for tileset with firstgid=" << tileset.getFirstGID() << std::endl;
            continue;
        }
        std::string tsxPath = it->second;
        std::string tsxDir = std::filesystem::path(tsxPath).parent_path().string();
        if (!loadTilesetCollection(tsxPath, tileset.getFirstGID(), tsxDir)) {
            std::cerr << "Failed to load tileset collection: " << tsxPath << std::endl;
            return false;
        }
    }
    buildSprites();
    return true;
}

bool Map::loadTilesetCollection(const std::string& tsxPath, unsigned firstGid, const std::string& tmxDir) {
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(tsxPath.c_str()) != tinyxml2::XML_SUCCESS) {
        std::cerr << "Failed to load TSX file: " << tsxPath << std::endl;
        return false;
    }
    auto* tilesetElem = doc.FirstChildElement("tileset");
    if (!tilesetElem) return false;
    for (auto* tileElem = tilesetElem->FirstChildElement("tile"); tileElem; tileElem = tileElem->NextSiblingElement("tile")) {
        int id = tileElem->IntAttribute("id");
        auto* imageElem = tileElem->FirstChildElement("image");
        if (!imageElem) continue;
        std::string imgSource = imageElem->Attribute("source");
        std::string imgPath = tmxDir + "/" + imgSource;
        sf::Texture tex;
        if (!tex.loadFromFile(imgPath)) {
            std::cerr << "Failed to load tile image: " << imgPath << std::endl;
            continue;
        }
        m_tileTextures[firstGid + id] = std::move(tex);
    }
    return true;
}

void Map::buildSprites() {
    m_tileSprites.clear();
    for (const auto& layer : m_map.getLayers()) {
        if (layer->getType() == tmx::Layer::Type::Tile) {
            const auto& tileLayer = layer->getLayerAs<tmx::TileLayer>();
            const auto& tiles = tileLayer.getTiles();
            for (unsigned y = 0; y < m_mapHeight; ++y) {
                for (unsigned x = 0; x < m_mapWidth; ++x) {
                    std::size_t idx = x + y * m_mapWidth;
                    tmx::TileLayer::Tile tile = tiles[idx];
                    if (tile.ID == 0) continue; // empty tile
                    auto it = m_tileTextures.find(tile.ID);
                    if (it == m_tileTextures.end()) continue;
                    sf::Sprite sprite;
                    sprite.setTexture(it->second);
                    sprite.setPosition(static_cast<float>(x * m_tileWidth), static_cast<float>(y * m_tileHeight));
                    m_tileSprites.push_back(sprite);
                }
            }
        }
    }
}

void Map::draw(sf::RenderWindow& window, const sf::View& view) {
    // Only draw tiles visible in the current view for performance
    for (const auto& sprite : m_tileSprites) {
        window.draw(sprite);
    }
}
