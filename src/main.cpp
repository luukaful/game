#include <SFML/Graphics.hpp>
#include "player.h"
#include <iostream>
#include <SFML/Window.hpp> // SFMLWindow is not a standard SFML header, so this line may cause an error


int main(int argc, char **argv) {
    // Maak een SFML-venster
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
    window.setFramerateLimit(60);

    // laad een lettertype
    sf::Font font;
    if (!font.loadFromFile("assets/font/Interior Finishing.otf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1; // fout
    }

    // maak een tekst object
    sf::Text text;
    text.setFont(font);
    text.setString("Hello world!!");
    text.setCharacterSize(24); // grootte in pixels
    text.setFillColor(sf::Color::White); // tekst kleur
    text.setPosition(300, 250); // positie in pixels



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

    const float movementSpeed = 100.f; //  snelheid van de speler
    sf::Clock clock;

    // Hoofdlus
    while (window.isOpen()) {
        window.clear();

        sf::Event event{};
        while (window.pollEvent(event)) {
            // Sluit het venster als de sluitknop is ingedrukt
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        //berekend delta tijd
        float deltaTime = clock.restart().asSeconds();

        // Beweeg speler met WASD en pijltjes toetsen
        float offsetX = 0.f, offsetY = 0.f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            offsetY -= movementSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            offsetY += movementSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            offsetX -= movementSpeed * deltaTime;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            offsetX += movementSpeed * deltaTime;
        }

        player.move(offsetX, offsetY);

        // Vul de achtergrond met zwart
       // Teken de speler
        player.draw(window);
        window.draw(text);

        // Teken het scherm
        window.display();
    }

    return 0; // succes
}