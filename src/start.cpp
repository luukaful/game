 #include "start.h"

#include <string>
#include <vector>

#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"

GameState toonBeginscherm(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("assets/font/Interior Finishing.otf");

    std::vector<std::string> opties = {"Nieuw Spel", "Laad Spel", "Instellingen", "Afsluiten"};
    std::vector<sf::Text> menuItems;
    int geselecteerd = 0;

    for (int i = 0; i < opties.size(); i++) {
        sf::Text tekst;
        tekst.setFont(font);
        tekst.setString(opties[i]);
        tekst.setCharacterSize(36);
        tekst.setPosition(100, 150 + i * 60);
        tekst.setFillColor(i == geselecteerd ? sf::Color::Yellow : sf::Color::White);
        menuItems.push_back(tekst);
    }

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return AFSLUITEN;

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    geselecteerd = (geselecteerd - 1 + opties.size()) % opties.size();
                else if (event.key.code == sf::Keyboard::Down)
                    geselecteerd = (geselecteerd + 1) % opties.size();
                else if (event.key.code == sf::Keyboard::Enter)
                    switch (static_cast<GameState>(geselecteerd)) {
                    case GameState::NIEUW_SPEL: return GameState::NIEUW_SPEL;
                    case GameState::LAAD_SPEL: return GameState::LAAD_SPEL;
                    case GameState::INSTELLINGEN: return GameState::INSTELLINGEN;
                    case GameState::AFSLUITEN: return GameState::AFSLUITEN;
                    }
            }
        }

        // Update kleuren
        for (int i = 0; i < menuItems.size(); i++) {
            menuItems[i].setFillColor(i == geselecteerd ? sf::Color::Yellow : sf::Color::White);
        }

        window.clear(sf::Color::Black);
        for (auto& tekst : menuItems)
            window.draw(tekst);
        window.display();
    }

    return GameState::AFSLUITEN;
}
