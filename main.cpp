#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "Story1.h"

// ...existing code...

void showStoryScreen(const std::string& name) {
    std::cout << "\n--- Story ---\n";
    std::cout << "Welcome, " << name << "! Your adventure begins here...\n";
    std::cout << "Once upon a time, in a land far away, you set out on a quest.\n";
    // ...add more story text as needed...
}

int main() {
    std::string name;
    std::cout << "Enter your name: ";
    std::getline(std::cin, name);

    // Open een SFML window en toon het story scherm
    sf::RenderWindow window(sf::VideoMode(800, 600), "Story");
    Story1(window);

    // ...existing code...
    return 0;
}
