#pragma once

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    enum Richting {
        OMHOOG,
        OMLAAG,
        LINKS,
        RECHTS
    } huidigeRichting;


public:
    Player();
    void beweeg(float offsetX, float offsetY);
    bool laadTexture(const std::string& bestandsPad);
    void setPositie(float x, float y);
    void setPositieTile(int tileX, int tileY, int tileSize);
    void teken(sf::RenderWindow& scherm) const;
    void updateRichting(const std::string& richting);
    sf::Vector2f getPositie() const;
};