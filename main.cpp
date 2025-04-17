#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Main Menu");
    sf::Font font;

    // Load a font (ensure the font file is in your project directory)
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font\n";
        return -1;
    }

    // Menu options
    std::vector<sf::Text> menuOptions;
    std::vector<std::string> options = {"Start Game", "Options", "Exit"};
    int selectedIndex = 0;

    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text text;
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(40);
        text.setPosition(300, 200 + i * 60);
        text.setFillColor(i == selectedIndex ? sf::Color::Red : sf::Color::White);
        menuOptions.push_back(text);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up) {
                    selectedIndex = (selectedIndex - 1 + options.size()) % options.size();
                } else if (event.key.code == sf::Keyboard::Down) {
                    selectedIndex = (selectedIndex + 1) % options.size();
                } else if (event.key.code == sf::Keyboard::Enter) {
                    if (options[selectedIndex] == "Start Game") {
                        std::cout << "Starting game...\n";
                        // Add game start logic here
                    } else if (options[selectedIndex] == "Options") {
                        std::cout << "Opening options...\n";
                        // Add options logic here
                    } else if (options[selectedIndex] == "Exit") {
                        window.close();
                    }
                }
            }
        }

        // Update menu colors
        for (size_t i = 0; i < menuOptions.size(); ++i) {
            menuOptions[i].setFillColor(i == selectedIndex ? sf::Color::Red : sf::Color::White);
        }

        window.clear();
        for (const auto& option : menuOptions) {
            window.draw(option);
        }
        window.display();
    }

    return 0;
}