#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "player.h"
#include "dialoogbox.h"


int main(int argc, char **argv) {
    // Maak een SFML-venster
    sf::RenderWindow venster(sf::VideoMode(800, 600), "Game");
    venster.setFramerateLimit(60);

    // Laad de icoon
    sf::Image icon;
    if (!icon.loadFromFile("assets/player/player_backwards_a.png")) {
        std::cerr << "Error loading icon" << std::endl;
        return -1; // fout
    }

    // Plaats venster icoon
    venster.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Laad de speler
    Player player;
    player.loadTexture("assets/player/player_backwards_a.png");
    player.setPosition(400, 300);

    // Laad een font
    sf::Font font;
    if (!font.loadFromFile("assets/font/Interior Finishing.otf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1; // fout
    }

    // Laad de dialoogbox
    DialoogBox dialogBox(font, 800, 600);

    auto dialoog = Dialoog{
        {"Hallo, ik ben de suprieure leider van de negerslaven.", "Dit is mijn eerste katoen plukker.", "En dit is de derde regel."},
        {"Spreker", "Spreker 2", "Spreker 3"}
    };

    const float movementSpeed = 100.f; //  snelheid van de speler
    sf::Clock clock;

    // Hoofdlus
    while (venster.isOpen()) {
        // Reset het venster
        venster.clear();

        sf::Event event{};
        while (venster.pollEvent(event)) {
            // Sluit het venster als de gebruiker op het kruisje klikt
            if (event.type == sf::Event::Closed) {
                venster.close();
            }

            // Verwerk de gebeurtenissen in de dialoogbox
            if (dialogBox.isZichtbaar()) {
                dialogBox.verwerkGebeurtenis(event);
            }

            // Druk op 'T' om de dialoogbox te activeren
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T && !dialogBox.isZichtbaar()) {
                dialogBox.setDialoog(dialoog);
                dialogBox.toon();
            }
        }

        // Bereken de tijd sinds de laatste frame (deltaTime / dt)
        float deltaTime = clock.restart().asSeconds();

        // Update de dialoogbox
        dialogBox.update(deltaTime);

        // Beweeg de speler op basis van toetsenbordinvoer
        if (!dialogBox.isZichtbaar()) {
            float offsetX = 0.f, offsetY = 0.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                offsetY -= movementSpeed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                offsetY += movementSpeed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                offsetX -= movementSpeed * deltaTime;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                offsetX += movementSpeed * deltaTime;
            }

            player.move(offsetX, offsetY);
        }

        // Teken de speler
        player.draw(venster);

        // Teken de dialoogbox
        dialogBox.draw(venster);

        // Teken het venster
        venster.display();
    }

    return 0; // succes
}