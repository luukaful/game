#include <Player.h>

Player::Player() {
    huidigeRichting = OMLAAG; // Standaard richting
}

bool Player::laadTexture(const std::string& bestandsPad) {
    if (!texture.loadFromFile(bestandsPad)) {
        return false; // Failed to load texture
    }
    sprite.setTexture(texture);
    return true; // Texture loaded successfully
}

void Player::setPositie(float x, float y) {
    sprite.setPosition(x, y);
}

void Player::setPositieTile(int tileX, int tileY, int tileSize) {
    float x = tileX * tileSize;
    float y = tileY * tileSize;
    setPositie(x, y);
}

void Player::teken(sf::RenderWindow& scherm) const {
    scherm.draw(sprite);
}

void Player::beweeg(float offsetX, float offsetY) {
    sprite.move(offsetX, offsetY);
}

void Player::updateRichting(const std::string& richting) {
    if (richting == "OMHOOG") {
        huidigeRichting = OMHOOG;
    } else if (richting == "OMLAAG") {
        huidigeRichting = OMLAAG;
    } else if (richting == "LINKS") {
        huidigeRichting = LINKS;
    } else if (richting == "RECHTS") {
        huidigeRichting = RECHTS;
    }
}

sf::Vector2f Player::getPositie() const {
    return sprite.getPosition();
}
