#include <SFML/Graphics.hpp>
#include "player.h"
#include "map.h"

int main() {
    // Create a window with a title and size
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

    // Load the player texture
    Player player;
    player.setPosition(400, 300); // Set the initial position of the player

    // Load the map
    Map map;
    if (!map.loadFromFile("assets/maps/standaard.json")) {
        return -1; // Exit if the map fails to load
    }

    // Main loop to keep the window open
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close the window when the close event is triggered
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Clear the window with a black color
        window.clear(sf::Color::Black);

        // Render the map
        map.render(window);

        // Draw the player sprite
        player.draw(window);

        // Display the contents of the window
        window.display();
    }

    return 0;
}