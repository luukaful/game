#include <iostream>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <Player.h>
#include <DialoogBox.h>
#include <start.h>
// #include <Map.h>



int main(int argc, char **argv) {
    // Maak een SFML-scherm
    sf::RenderWindow scherm(sf::VideoMode(800, 600), "Game");
    scherm.setFramerateLimit(60);

    GameState keuze = toonBeginscherm(scherm);

    if (keuze == AFSLUITEN) {
        return 0; // Afsluiten
    }
    if (keuze == LAAD_SPEL) {
        // laad opgeslagen spel
    }
    if (keuze == INSTELLINGEN) {
        // instellingen
    }
    if (keuze == NIEUW_SPEL) {
        // nieuw spel
    }

    std::vector<std::string> opties = {
        "Nieuw Spel",
        "Laad Spel",
        "Instellingen",
        "Afsluiten"

    };


    // Laad de icoon
    sf::Image icon;
    if (!icon.loadFromFile("assets/player/player_backwards_a.png")) {
        std::cerr << "Error loading icon" << std::endl;
        return -1; // fout
    }


    // Plaats scherm icoon
    scherm.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    // Laad de speler
    Player player;
    player.laadTexture("assets/player/player_backwards_a.png");
    player.setPositie(400, 300);

    // Laad een font
    sf::Font font;
    if (!font.loadFromFile("assets/font/Interior Finishing.otf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1; // fout
    }

    // Laad de dialoogbox
    DialoogBox dialoogBox(font, 800, 600);

    auto dialoog = Dialoog{
        {"Hallo, ik ben de suprieure leider van de negerslaven.", "Dit is mijn eerste katoen plukker.", "En dit is de derde regel."},
        {"Spreker", "Spreker 2", "Spreker 3"}
    };

    const float movementSpeed = 100.f; //  snelheid van de speler
    sf::Clock clock;

    // Map gameMap;
    // if (!gameMap.laadMap("assets/maps/bios_garden.tmx")) {
    //     std::cerr << "Error loading map" << std::endl;
    //     return -1;
    // }


    // Hoofdlus
    while (scherm.isOpen()) {
        // Reset het scherm
        scherm.clear();

        sf::Event event{};
        while (scherm.pollEvent(event)) {
            // Sluit het scherm als de gebruiker op het kruisje klikt
            if (event.type == sf::Event::Closed) {
                scherm.close();
            }




            // Verwerk de gebeurtenissen in de dialoogbox
            if (dialoogBox.isZichtbaar()) {
                dialoogBox.verwerkGebeurtenis(event);
            }

            // Druk op 'T' om de dialoogbox te activeren
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::T && !dialoogBox.isZichtbaar()) {
                dialoogBox.setDialoog(dialoog);
                dialoogBox.toon();
            }
        }

        // Bereken de tijd sinds de laatste frame (deltaTime / dt)
        float deltaTime = clock.restart().asSeconds();

        // Update de dialoogbox
        dialoogBox.update(deltaTime);

        // Beweeg de speler op basis van toetsenbordinvoer
        if (!dialoogBox.isZichtbaar()) {
            float offsetX = 0.f, offsetY = 0.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ) {
                offsetY -= movementSpeed * deltaTime;
                player.updateRichting("OMHOOG");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ) {
                offsetY += movementSpeed * deltaTime;
                player.updateRichting("OMLAAG");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                offsetX -= movementSpeed * deltaTime;
                player.updateRichting("LINKS");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ) {
                offsetX += movementSpeed * deltaTime;
                player.updateRichting("RECHTS");
            }

            player.beweeg(offsetX, offsetY);
        }

        // Teken de kaart
        // gameMap.teken(scherm);

        // Teken de speler
        player.teken(scherm);

        // Teken de dialoogbox
        dialoogBox.teken(scherm);



        // Teken het scherm
        scherm.display();
    }

    return 0; // succes
}