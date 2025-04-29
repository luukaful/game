//
// Created by marku on 27-4-2025.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::IntRect currentFrame;
    float animationTimer;
    float animationSpeed;
    int frameCount;
    int currentFrameIndex;


public:
    Player();
    bool loadTexture(const std::string& filePath);
    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window);
};




#endif //PLAYER_H
