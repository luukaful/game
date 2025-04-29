#include <SFML/Graphics.hpp>
#include "player.h"

int main(int argc, char **argv) {
    // Maak een SFML venster
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Laad de speler
    Player player;
    player.loadTexture("path/to/your/image.png"); // Load the texture for the player
    player.setPosition(400, 300); // Set the initial position of the player

    // Hoofdlus
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            // Sluit het venster als de sluitknop is ingedrukt
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Vul de achtergrond met zwart
        window.clear(sf::Color::Black);

        // Teken de speler
        player.draw(window);

        // Teken het scherm
        window.display();
    }

    return 0; // succes
}