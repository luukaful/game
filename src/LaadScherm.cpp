#include "LaadScherm.h"
#include "SaveParser.h"
#include <iostream>

LaadScherm::LaadScherm() : currentSelection(0) {
    // Laad font
    if (!font.loadFromFile("assets/font/Interior Finishing.otf")) {
        std::cerr << "Error loading font for LaadScherm" << std::endl;
    }
    
    // Probeer achtergrond te laden (Je kunt een eigen afbeelding gebruiken)
    if (!backgroundTexture.loadFromFile("assets/background/load_background.png")) {
        // Fallback to a generated background if image doesn't exist
        backgroundTexture.create(800, 600);
        sf::Image bgImage;
        bgImage.create(800, 600, sf::Color(30, 30, 60, 255)); // Dark blue background
        backgroundTexture.update(bgImage);
    }
    backgroundSprite.setTexture(backgroundTexture);
    
    // Stel titeltekst in
    titleText.setFont(font);
    titleText.setString("Laad Opgeslagen Spel");
    titleText.setCharacterSize(36);
    titleText.setFillColor(sf::Color::White);
    titleText.setPosition(200, 50);
    
    // Stel selectiehighlight in
    selectionHighlight.setFillColor(sf::Color(100, 100, 200, 100));
    selectionHighlight.setOutlineColor(sf::Color(150, 150, 255));
    selectionHighlight.setOutlineThickness(2);
    selectionHighlight.setSize(sf::Vector2f(300, 50));
    
    // Stel previewbox in
    previewBox.setFillColor(sf::Color(50, 50, 80, 200));
    previewBox.setOutlineColor(sf::Color(100, 100, 150));
    previewBox.setOutlineThickness(2);
    previewBox.setSize(sf::Vector2f(350, 200));
    previewBox.setPosition(400, 150);
    
    // Laad beschikbare save files
    laadBeschikbareSaveFiles();

    // Verwijder-knop instellen
    deleteButton.setSize(sf::Vector2f(200, 40));
    deleteButton.setFillColor(sf::Color(180, 60, 60, 220));
    deleteButton.setOutlineColor(sf::Color(255, 120, 120));
    deleteButton.setOutlineThickness(2);
    deleteButton.setPosition(120, 350);

    deleteButtonText.setFont(font);
    deleteButtonText.setString("Verwijder Spel");
    deleteButtonText.setCharacterSize(22);
    deleteButtonText.setFillColor(sf::Color::White);
    deleteButtonText.setPosition(140, 355);
}


void LaadScherm::laadBeschikbareSaveFiles() {
    saveFiles.clear();
    saveOptions.clear();
    
    // Zoek alle save*.json bestanden
    for (int i = 0; i < 3; i++) {
        std::string bestandsnaam = "save" + std::to_string(i) + ".json";
        if (std::filesystem::exists(bestandsnaam)) {
            saveFiles.push_back(bestandsnaam);
            
            // Maak text object voor de optie
            sf::Text optie;
            optie.setFont(font);
            optie.setString("Opgeslagen spel " + std::to_string(i + 1));
            optie.setCharacterSize(24);
            optie.setFillColor(sf::Color::White);
            optie.setPosition(100, 150 + i * 60);
            
            saveOptions.push_back(optie);
        }
    }
    
    if (saveFiles.empty()) {
        // Geen save bestanden gevonden
        sf::Text geenSaves;
        geenSaves.setFont(font);
        geenSaves.setString("Geen opgeslagen spellen gevonden!");
        geenSaves.setCharacterSize(24);
        geenSaves.setFillColor(sf::Color(255, 100, 100));
        geenSaves.setPosition(100, 150);
        saveOptions.push_back(geenSaves);
    }
}

void LaadScherm::toonSavePreview(sf::RenderWindow& scherm, const std::string& bestand, int selectedIndex) {
    // Teken preview box
    scherm.draw(previewBox);
    
    // Als er geen saves zijn, toon niets
    if (saveFiles.empty()) return;
    
    // Laad save data
    SaveParser saveParser(bestand);
    if (saveParser.loadSaveFile()) {
        std::string spelerNaam = saveParser.getValue("speler_naam");
        
        // Toon save details
        sf::Text details;
        details.setFont(font);
        details.setCharacterSize(20);
        details.setFillColor(sf::Color::White);
        details.setPosition(420, 170);
        
        std::string detailsStr = "Bestand: " + bestand + 
                               "\nSpeler: " + spelerNaam;
        details.setString(detailsStr);
        
        scherm.draw(details);
    }
}

std::string LaadScherm::toonLaadScherm(sf::RenderWindow& scherm) {
    // Update de lijst met saves
    laadBeschikbareSaveFiles();
    
    if (saveFiles.empty()) {
        // Toon een bericht en wacht even
        scherm.clear();
        scherm.draw(backgroundSprite);
        
        sf::Text geenSaves;
        geenSaves.setFont(font);
        geenSaves.setString("Geen opgeslagen spellen gevonden!\nDruk op ESC om terug te gaan.");
        geenSaves.setCharacterSize(28);
        geenSaves.setFillColor(sf::Color::White);
        geenSaves.setPosition(200, 250);
        
        scherm.draw(titleText);
        scherm.draw(geenSaves);
        scherm.display();
        
        // Wacht op toets
        while (scherm.isOpen()) {
            sf::Event event;
            while (scherm.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    scherm.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        return ""; // Terug naar menu
                    }
                }
            }
        }
        return "";
    }
    
    int menuMode = 0; // 0 = normaal, 1 = delete-menu
    int deleteSelection = 0;
    // Interactieve selectie van save bestand
    while (scherm.isOpen()) {
        sf::Event event;
        while (scherm.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                scherm.close();
            }
            if (menuMode == 0) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        return "";
                    } else if (event.key.code == sf::Keyboard::Up) {
                        if (currentSelection > 0) currentSelection--;
                        else currentSelection = saveFiles.size(); // laatste optie is delete
                    } else if (event.key.code == sf::Keyboard::Down) {
                        if (currentSelection < (int)saveFiles.size()) currentSelection++;
                        else currentSelection = 0;
                    } else if (event.key.code == sf::Keyboard::Return) {
                        if (currentSelection == (int)saveFiles.size()) {
                            // Delete-menu openen
                            menuMode = 1;
                            deleteSelection = 0;
                        } else {
                            return saveFiles[currentSelection];
                        }
                    }
                }
            } else if (menuMode == 1) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        menuMode = 0;
                    } else if (event.key.code == sf::Keyboard::Up) {
                        if (deleteSelection > 0) deleteSelection--;
                        else deleteSelection = saveFiles.size() - 1;
                    } else if (event.key.code == sf::Keyboard::Down) {
                        if (deleteSelection < (int)saveFiles.size() - 1) deleteSelection++;
                        else deleteSelection = 0;
                    } else if (event.key.code == sf::Keyboard::Return) {
                        verwijderSaveFile(deleteSelection);
                        if (saveFiles.empty()) {
                            menuMode = 0;
                            currentSelection = 0;
                        } else if (deleteSelection >= (int)saveFiles.size()) {
                            deleteSelection = std::max(0, (int)saveFiles.size() - 1);
                        }
                    }
                }
            }
        }
        // Teken alles
        scherm.clear();
        scherm.draw(backgroundSprite);
        scherm.draw(titleText);
        sf::Text instructies;
        instructies.setFont(font);
        if (menuMode == 0) {
            instructies.setString("Gebruik pijltjestoetsen om te navigeren en Enter om te selecteren");
        } else {
            instructies.setString("Kies een spel om te verwijderen (Enter = verwijderen, ESC = terug)");
        }
        instructies.setCharacterSize(16);
        instructies.setFillColor(sf::Color(200, 200, 200));
        instructies.setPosition(150, 100);
        scherm.draw(instructies);
        if (menuMode == 0) {
            // Highlight
            if (!saveFiles.empty() && currentSelection < (int)saveFiles.size()) {
                selectionHighlight.setPosition(80, 145 + currentSelection * 60);
                scherm.draw(selectionHighlight);
            } else if (currentSelection == (int)saveFiles.size()) {
                // Highlight delete-knop
                selectionHighlight.setPosition(deleteButton.getPosition().x - 20, deleteButton.getPosition().y - 5);
                selectionHighlight.setSize(sf::Vector2f(deleteButton.getSize().x + 40, deleteButton.getSize().y + 10));
                scherm.draw(selectionHighlight);
                selectionHighlight.setSize(sf::Vector2f(300, 50)); // reset
            }
            // Opties
            for (const auto& optie : saveOptions) {
                scherm.draw(optie);
            }
            scherm.draw(deleteButton);
            scherm.draw(deleteButtonText);
            if (!saveFiles.empty() && currentSelection < (int)saveFiles.size()) {
                toonSavePreview(scherm, saveFiles[currentSelection], currentSelection);
            }
        } else if (menuMode == 1) {
            // Delete-menu
            for (size_t i = 0; i < saveFiles.size(); ++i) {
                sf::Text optie;
                optie.setFont(font);
                optie.setString("Verwijder: " + saveFiles[i]);
                optie.setCharacterSize(24);
                optie.setFillColor(i == (size_t)deleteSelection ? sf::Color(255, 100, 100) : sf::Color::White);
                optie.setPosition(120, 180 + (int)i * 50);
                scherm.draw(optie);
            }
        }
        sf::Text terugKnop;
        terugKnop.setFont(font);
        terugKnop.setString("ESC - Terug naar menu");
        terugKnop.setCharacterSize(18);
        terugKnop.setFillColor(sf::Color(180, 180, 180));
        terugKnop.setPosition(30, 550);
        scherm.draw(terugKnop);
        scherm.display();
    }
    return "";
}

void LaadScherm::verwijderSaveFile(int index) {
    if (index >= 0 && index < static_cast<int>(saveFiles.size())) {
        std::string bestand = saveFiles[index];
        if (std::filesystem::exists(bestand)) {
            std::filesystem::remove(bestand);
        }
        laadBeschikbareSaveFiles();
        if (currentSelection >= static_cast<int>(saveFiles.size())) {
            currentSelection = std::max(0, static_cast<int>(saveFiles.size()) - 1);
        }
    }
}

