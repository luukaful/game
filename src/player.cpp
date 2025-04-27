//
// Created by marku on 27-4-2025.
//

#include "player.h"

Player::Player() {
    // Constructor implementation
}

bool Player::loadTexture(const std::string& filePath) {
    if (!texture.loadFromFile(filePath)) {
        return false; // Failed to load texture
    }
    sprite.setTexture(texture);
    return true; // Texture loaded successfully
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}
