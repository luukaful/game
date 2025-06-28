#pragma once

#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>


class Enemy {
    std::string name;
    int health;
    int damage;
    float speed;
    sf::Vector2f pos;

public:
    Enemy(std::string name, int health, int damage, float speed)
        : name(std::move(name)), health(health), damage(damage), speed(speed) {}

    sf::Vector2f move(float x, float y);

    sf::Vector2f moveTo(sf::Vector2f pos);
};
