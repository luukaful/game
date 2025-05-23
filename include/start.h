//
// Created by marku on 22-5-2025.
//

#ifndef START_H
#define START_H





#include <SFML/Graphics.hpp>

enum GameState { NIEUW_SPEL, LAAD_SPEL, INSTELLINGEN, AFSLUITEN };

GameState toonBeginscherm(sf::RenderWindow& window);

#endif //START_H