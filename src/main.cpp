#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <Player.h>
#include <DialoogBox.h>
#include <start.h>
#include <nieuwspel.h>
#include <filesystem>
#include <LaadScherm.h>
#include <SaveParser.h>
#include "Map.h"// Added Map include

#include "proloog.h"


int main(int argc, char **argv) {
    // Maak een SFML-scherm
    sf::RenderWindow scherm(sf::VideoMode(800, 600), "Game");
    scherm.setFramerateLimit(60);

    // Laad de icoon
    sf::Image icon;
    if (!icon.loadFromFile("assets/player/player_backwards_a.png")) {
        std::cerr << "Error loading icon" << std::endl;
        return -1; // fout
    }

    // Plaats scherm icoon
    scherm.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    GameState keuze = toonBeginscherm(scherm);

    std::string laadBestand = "";
    std::unique_ptr<SaveParser> save;

    if (keuze == AFSLUITEN) {
        return 0; // Afsluiten
    }
    if (keuze == LAAD_SPEL) {
        // Toon laadscherm om een save te selecteren
        LaadScherm laadScherm;
        laadBestand = laadScherm.toonLaadScherm(scherm);

        if (laadBestand.empty()) {
            // Gebruiker heeft geannuleerd, terug naar beginscherm
        } else {
            // Laad het geselecteerde bestand
            save = std::make_unique<SaveParser>(laadBestand);
            save->loadSaveFile();
        }
    }
    if (keuze == INSTELLINGEN) {
        // instellingen
    }
    if (keuze == NIEUW_SPEL) {
        std::string spelerNaam = vraagNaam(scherm);

        // Dynamically determine the next save file name, limited to 3 saves
        int saveIndex = 0;
        std::string saveFileName;
        bool saveSlotFound = false;

        while (saveIndex < 3) {
            saveFileName = "save" + std::to_string(saveIndex++) + ".json";
            if (!std::filesystem::exists(saveFileName)) {
                saveSlotFound = true;
                break;
            }
        }

        if (!saveSlotFound) {
            std::cerr << "Maximum number of save files reached (3)." << std::endl;
            return 1; // Exit or handle the error as needed
        }

        save = std::make_unique<SaveParser>(saveFileName);
        save->createSaveFile();
        save->setValue("speler_naam", spelerNaam);
    }

    // Load the map
    Map gameMap;
    if (!gameMap.loadFromFile("assets/maps/bios_garden.tmx")) {
        std::cerr << "Error loading map" << std::endl;
        return -1;
    }

    // Set up the camera/view
    sf::View gameView(sf::FloatRect(0, 0, 800, 600));
    scherm.setView(gameView);

    // Laad de speler
    Player player;
    player.laadTexture("assets/player/player_backwards_a.png");
    player.setPositieTile(1, 1, 32);

    // Laad een font
    sf::Font font;
    if (!font.loadFromFile("assets/font/Interior Finishing.otf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1; // fout
    }

    // Laad de dialoogbox
    DialoogBox dialoogBox(font, 800, 600);

    const float movementSpeed = 100.f; //  snelheid van de speler
    sf::Clock clock;

    bool proloogSet = false;
    bool playerActive = false;

    if (save->getValue("proloog") != "1") {
        dialoogBox.setDialoog(proloogDialoog);
        dialoogBox.toon();
        playerActive = false;
    } else {
        proloogSet = true;
        playerActive = true;
    }

    bool pauzeMenu = false;
    int pauzeSelectie = 0;
    const std::vector<std::string> pauzeOpties = {"option", "leave", "continue"};

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

            if (pauzeMenu) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        if (pauzeSelectie > 0) pauzeSelectie--;
                        else pauzeSelectie = pauzeOpties.size() - 1;
                    } else if (event.key.code == sf::Keyboard::Down) {
                        if (pauzeSelectie < (int)pauzeOpties.size() - 1) pauzeSelectie++;
                        else pauzeSelectie = 0;
                    } else if (event.key.code == sf::Keyboard::Return) {
                        if (pauzeOpties[pauzeSelectie] == "continue") {
                            pauzeMenu = false;
                        } else if (pauzeOpties[pauzeSelectie] == "leave") {
                            scherm.close();
                        } else if (pauzeOpties[pauzeSelectie] == "option") {
                            // Hier kun je opties toevoegen
                        }
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        pauzeMenu = false;
                    }
                }
            } else {
                // Verwerk de gebeurtenissen in de dialoogbox
                if (dialoogBox.isZichtbaar()) {
                    dialoogBox.verwerkGebeurtenis(event);
                }
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && !dialoogBox.isZichtbaar()) {
                    pauzeMenu = true;
                    pauzeSelectie = 0;
                }
            }
        }

        if (pauzeMenu) {
            // Pauzemenu tekenen
            // Gebruik UI view zodat het menu niet meebeweegt met de camera
            sf::View oldView = scherm.getView();
            scherm.setView(scherm.getDefaultView());
            const float menuWidth = 400;
            const float menuHeight = 300;
            const float menuX = (800 - menuWidth) / 2;
            const float menuY = (600 - menuHeight) / 2;
            sf::RectangleShape menuBg;
            menuBg.setSize(sf::Vector2f(menuWidth, menuHeight));
            menuBg.setFillColor(sf::Color(40, 40, 60, 230));
            menuBg.setOutlineColor(sf::Color(120, 120, 180));
            menuBg.setOutlineThickness(3);
            menuBg.setPosition(menuX, menuY);
            scherm.draw(menuBg);
            for (size_t i = 0; i < pauzeOpties.size(); ++i) {
                sf::Text optie;
                optie.setFont(font);
                optie.setString(pauzeOpties[i]);
                optie.setCharacterSize(32);
                optie.setFillColor(i == (size_t)pauzeSelectie ? sf::Color(255, 200, 100) : sf::Color::White);
                // Centreer de tekst horizontaal in het menu
                sf::FloatRect bounds = optie.getLocalBounds();
                float textX = menuX + (menuWidth - bounds.width) / 2 - bounds.left;
                float textY = menuY + 60 + (int)i * 70;
                optie.setPosition(textX, textY);
                scherm.draw(optie);
            }
            scherm.setView(oldView);
            scherm.display();
            continue;
        }

        // Bereken de tijd sinds de laatste frame (deltaTime / dt)
        float deltaTime = clock.restart().asSeconds();

        // Update de dialoogbox
        dialoogBox.update(deltaTime);

        // Zet proloog op 1 als de proloog net is afgelopen
        if (!proloogSet && !dialoogBox.isZichtbaar() && save->getValue("proloog") != "1") {
            save->setValue("proloog", "1");
            proloogSet = true;
            playerActive = true;
        }

        // Beweeg de speler op basis van toetsenbordinvoer
        if (playerActive && !dialoogBox.isZichtbaar()) {
            float offsetX = 0.f, offsetY = 0.f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                offsetY -= movementSpeed * deltaTime;
                player.updateRichting("OMHOOG");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                offsetY += movementSpeed * deltaTime;
                player.updateRichting("OMLAAG");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                offsetX -= movementSpeed * deltaTime;
                player.updateRichting("LINKS");
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                offsetX += movementSpeed * deltaTime;
                player.updateRichting("RECHTS");
            }

            player.beweeg(offsetX, offsetY);

            // Update camera to follow player
            sf::Vector2f playerPos = player.getPositie();
            gameView.setCenter(playerPos);
            scherm.setView(gameView);
        }

        // Draw the map
        gameMap.draw(scherm, gameView);

        // Teken de speler
        if (playerActive) {
            player.teken(scherm);
        }

        // Teken de dialoogbox (using UI view)
        sf::View uiView = scherm.getDefaultView();
        scherm.setView(uiView);
        dialoogBox.teken(scherm);

        // Return to game view
        scherm.setView(gameView);

        // Teken het scherm
        scherm.display();
    }

    return 0; // succes
}
