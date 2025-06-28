#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <filesystem>

class LaadScherm {
public:
    LaadScherm();
    
    // Displays the loading screen and returns the selected save file
    std::string toonLaadScherm(sf::RenderWindow& scherm);
    
private:
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    
    // UI elements
    sf::Text titleText;
    std::vector<sf::Text> saveOptions;
    std::vector<std::string> saveFiles;
    sf::RectangleShape selectionHighlight;
    sf::RectangleShape previewBox;
    
    // Load save files from directory
    void laadBeschikbareSaveFiles();
    
    // Display save file details in the preview box
    void toonSavePreview(sf::RenderWindow& scherm, const std::string& bestand, int selectedIndex);
    
    // Verwijder een save file op basis van index
    void verwijderSaveFile(int index);

    int currentSelection;
};
