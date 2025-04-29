#include <SFML/Graphics.hpp>
#include "player.h"
#include <iostream>
#include <SFML/Window.hpp> // SFMLWindow is not a standard SFML header, so this line may cause an error


int main(int argc, char **argv) {
    // Maak een SFML-venster
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    window.setFramerateLimit(60);

    //laad de icon
    sf::Image icon;
    if (!icon.loadFromFile("assets/player/player_backwards_a.png")) {
        std::cerr << "Error loading icon" << std::endl;
        return -1; // fout
    }

    // plaats window icon
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Laad de speler
    Player player;
    player.loadTexture("assets/player/player_backwards_a.png");
    player.setPosition(400, 300);

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
       // Teken de speler
        player.draw(window);

        // Teken het scherm
        window.display();
    }

    return 0; // succes
}