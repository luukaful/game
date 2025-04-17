#include <SFML/Graphics.hpp>

int main() {
    // Create a window with a title and size
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");

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

        // Display the contents of the window
        window.display();
    }

    return 0;
}