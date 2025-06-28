#include "Enemy.h"

sf::Vector2f Enemy::move(float x, float y) {
    pos.x += x * speed;
    pos.y += y * speed;
    return pos;
}

sf::Vector2f Enemy::moveTo(sf::Vector2f targetPos) {
    sf::Vector2f direction = targetPos - pos;
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction /= length; // Normalize the direction vector
        pos += direction * speed; // Move towards the target position
    }
    return pos;
}