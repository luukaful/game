//
// Created by marku on 23-5-2025.
//

#include "nieuwspel.h"

std::string vraagNaam(sf::RenderWindow& window) {
    sf::Font font;
    font.loadFromFile("assets/font/Interior Finishing.otf");

    sf::Text titel("Voer je naam in:", font, 30);
    titel.setPosition(100, 30);
    titel.setFillColor(sf::Color::White);

    std::string naam;

    std::vector<std::string> toetsen = {
        "A","B","C","D","E","F","G","H","I","J",
        "K","L","M","N","O","P","Q","R","S","T",
        "U","V","W","X","Y","Z","<-","OK"
    };

    const int kolommen = 10;
    const int rijen = 3;

    sf::Text grid[rijen][kolommen];
    int geselecteerdRij = 0;
    int geselecteerdKol = 0;

    int index = 0;
    for (int r = 0; r < rijen; r++) {
        for (int c = 0; c < kolommen; c++) {
            if (index < toetsen.size()) {
                grid[r][c].setFont(font);
                grid[r][c].setString(toetsen[index]);
                grid[r][c].setCharacterSize(24);
                grid[r][c].setPosition(80 + c * 60, 100 + r * 60);
                grid[r][c].setFillColor(sf::Color::White);
                index++;
            }
        }
    }

    sf::Text naamText("", font, 30);
    naamText.setPosition(100, 300);
    naamText.setFillColor(sf::Color::Yellow);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                return "";

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Up)
                    geselecteerdRij = (geselecteerdRij - 1 + rijen) % rijen;
                else if (event.key.code == sf::Keyboard::Down)
                    geselecteerdRij = (geselecteerdRij + 1) % rijen;
                else if (event.key.code == sf::Keyboard::Left)
                    geselecteerdKol = (geselecteerdKol - 1 + kolommen) % kolommen;
                else if (event.key.code == sf::Keyboard::Right)
                    geselecteerdKol = (geselecteerdKol + 1) % kolommen;
                else if (event.key.code == sf::Keyboard::Enter) {
                    int index = geselecteerdRij * kolommen + geselecteerdKol;
                    if (index < toetsen.size()) {
                        std::string keuze = toetsen[index];
                        if (keuze == "<-") {
                            if (!naam.empty()) naam.pop_back();
                        } else if (keuze == "OK") {
                            return naam;
                        } else {
                            if (naam.length() < 20)
                                naam += keuze;
                        }
                    }
                }
            }
        }

        // Kleuren updaten
        for (int r = 0; r < rijen; r++) {
            for (int c = 0; c < kolommen; c++) {
                int idx = r * kolommen + c;
                if (idx < toetsen.size()) {
                    grid[r][c].setFillColor((r == geselecteerdRij && c == geselecteerdKol) ? sf::Color::Green : sf::Color::White);
                }
            }
        }

        naamText.setString("Naam: " + naam);

        window.clear(sf::Color::Black);
        window.draw(titel);
        for (int r = 0; r < rijen; r++) {
            for (int c = 0; c < kolommen; c++) {
                int idx = r * kolommen + c;
                if (idx < toetsen.size()) {
                    window.draw(grid[r][c]);
                }
            }
        }
        window.draw(naamText);
        window.display();
    }

    return "";
}