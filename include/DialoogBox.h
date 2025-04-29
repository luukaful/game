#ifndef DIALOOGBOX_H
#define DIALOOGBOX_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <random>

struct Dialoog {
    std::vector<std::string> dialoog;
    std::vector<std::string> sprekers;
};

class DialoogBox {
private:
    sf::RectangleShape box;          // Hoofd dialoogbox
    sf::RectangleShape speakerBox;   // Kleine box voor sprekernaam
    sf::Text dialoogTekst;           // Tekstinhoud
    sf::Text speakerTekst;           // Sprekernaam
    sf::Font font;                   // Lettertype

    sf::SoundBuffer dialoogGeluidBuffer;
    sf::Sound dialoogGeluid;
    sf::SoundBuffer selectGeluidBuffer;
    sf::Sound selectGeluid;
    std::mt19937 rng;
    std::uniform_real_distribution<float> pitchDistributie;

    std::vector<std::string> dialoogRegels;  // Alle dialoogregels
    std::vector<std::string> sprekers;       // Spreker voor elke regel

    unsigned int huidigeRegel;        // Huidige dialoogregel index
    bool isActive;                    // Is dialoogbox zichtbaar
    float tekstAnimatieTimer;         // Voor tekstanimatie
    float tekstAnimatieSnelheid;      // Hoe snel tekst verschijnt
    std::string huidigVolledigeTekst; // Volledige tekst van huidige regel
    std::string huidigZichtbareTekst; // Momenteel zichtbare deel van tekst
    bool isTekstVolledigZichtbaar;    // Is alle tekst getoond

public:
    DialoogBox(const sf::Font& font, unsigned int windowWidth, unsigned int windowHeight);

    void setDialoog(Dialoog &dialoog);
    void toon();
    void verberg();
    bool isZichtbaar() const;

    void update(float deltaTime);
    void draw(sf::RenderWindow& window) const;
    bool verwerkGebeurtenis(const sf::Event& gebeurtenis);
    bool heeftMeerDialoog() const;
};

#endif // DIALOOGBOX_H