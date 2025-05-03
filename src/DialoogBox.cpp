#include <iostream>

#include "dialoogbox.h"

DialoogBox::DialoogBox(const sf::Font& font, const unsigned int windowWidth, const unsigned int windowHeight) {
    // Stel het lettertype in
    this->font = font;

    // Stel de hoofd dialoogbox in
    box.setSize(sf::Vector2f(windowWidth * 0.8f, windowHeight * 0.2f));
    box.setPosition(windowWidth * 0.1f, windowHeight * 0.75f);
    box.setFillColor(sf::Color(0, 0, 0, 200));
    box.setOutlineThickness(2);
    box.setOutlineColor(sf::Color(255, 255, 255, 255));

    // Stel de sprekerbox in
    speakerBox.setSize(sf::Vector2f(windowWidth * 0.2f, 30));
    speakerBox.setPosition(windowWidth * 0.1f, windowHeight * 0.75f - 30);
    speakerBox.setFillColor(sf::Color(0, 0, 0, 200));
    speakerBox.setOutlineThickness(2);
    speakerBox.setOutlineColor(sf::Color(255, 255, 255, 255));

    // Stel de dialoogtekst in
    dialoogTekst.setFont(font);
    dialoogTekst.setCharacterSize(20);
    dialoogTekst.setPosition(windowWidth * 0.1f + 10, windowHeight * 0.75f + 10);
    dialoogTekst.setFillColor(sf::Color::White);

    // Stel de sprekertekst in
    speakerTekst.setFont(font);
    speakerTekst.setCharacterSize(18);
    speakerTekst.setPosition(windowWidth * 0.1f + 10, windowHeight * 0.75f - 28);
    speakerTekst.setFillColor(sf::Color::White);

    // Initialiseer de willekeurige getallengenerator
    rng.seed(std::random_device()());
    pitchDistributie = std::uniform_real_distribution<float>(0.8f, 1.2f);

    // Laad de Geluideneffecten
    sprekerGeluidBuffers["Spreker"].loadFromFile("assets/audio/dialoog.wav");
    sprekerGeluiden["Spreker"].setBuffer(sprekerGeluidBuffers["Spreker"]);

    sprekerGeluidBuffers["Spreker 2"].loadFromFile("assets/audio/dialoog2.wav");
    sprekerGeluiden["Spreker 2"].setBuffer(sprekerGeluidBuffers["Spreker 2"]);

    sprekerGeluidBuffers["Spreker 3"].loadFromFile("assets/audio/dialoog3.wav");
    sprekerGeluiden["Spreker 3"].setBuffer(sprekerGeluidBuffers["Spreker 3"]);

    // Laad het selectgeluid
    if (!selectGeluidBuffer.loadFromFile("assets/audio/select.wav")) {
        std::cerr << "Failed to load select Geluid" << std::endl;
    }
    selectGeluid.setBuffer(selectGeluidBuffer);
    selectGeluid.setVolume(60.0f);

    // Initialiseer andere variabelen
    huidigeRegel = 0;
    isActive = false;
    tekstAnimatieTimer = 0;
    tekstAnimatieSnelheid = 0.04f;
    isTekstVolledigZichtbaar = false;
}

void DialoogBox::setDialoog(Dialoog &dialoog) {
    dialoogRegels = dialoog.dialoog;
    sprekers = dialoog.sprekers;
    huidigeRegel = 0;

    if (!dialoogRegels.empty()) {
        huidigVolledigeTekst = dialoogRegels[0];
        huidigZichtbareTekst = "";
        isTekstVolledigZichtbaar = false;

        if (!sprekers.empty()) {
            speakerTekst.setString(sprekers[0]);
        } else {
            speakerTekst.setString("");
        }
    }
}

void DialoogBox::toon() {
    isActive = true;
}

void DialoogBox::verberg() {
    isActive = false;
}

bool DialoogBox::isZichtbaar() const {
    return isActive;
}

void DialoogBox::update(const float deltaTime) {
    if (!isActive || isTekstVolledigZichtbaar) return;

    // Laat tekst geleidelijk verschijnen (animatie)
    tekstAnimatieTimer += deltaTime;

    if (tekstAnimatieTimer >= tekstAnimatieSnelheid) {
        tekstAnimatieTimer = 0;

        if (huidigZichtbareTekst.length() < huidigVolledigeTekst.length()) {
            huidigZichtbareTekst = huidigVolledigeTekst.substr(0, huidigZichtbareTekst.length() + 1);
            dialoogTekst.setString(huidigZichtbareTekst);

            // Speel geluid met willekeurige toonhoogte voor elk karakter
            if (huidigZichtbareTekst.back() != ' ') {  // Geen geluid voor spaties
                auto it = sprekerGeluiden.find(speakerTekst.getString());
                if (it != sprekerGeluiden.end()) {
                    it->second.setPitch(pitchDistributie(rng));
                    it->second.play();
                } else {
                    dialoogGeluid.setPitch(pitchDistributie(rng));
                    dialoogGeluid.play();
                }
            }
        } else {
            isTekstVolledigZichtbaar = true;
        }
    }
}

void DialoogBox::draw(sf::RenderWindow& window) const {
    if (!isActive) return;

    window.draw(box);
    window.draw(speakerBox);
    window.draw(dialoogTekst);
    window.draw(speakerTekst);
}

bool DialoogBox::verwerkGebeurtenis(const sf::Event& gebeurtenis) {
    if (!isActive) return false;

    // Bij muisklik of spatie, ga naar volgende dialoog
    if ((gebeurtenis.type == sf::Event::MouseButtonPressed &&
         gebeurtenis.mouseButton.button == sf::Mouse::Left) ||
        (gebeurtenis.type == sf::Event::KeyPressed &&
         gebeurtenis.key.code == sf::Keyboard::Space)) {

        if (isTekstVolledigZichtbaar) {
            // Ga naar volgende regel
            huidigeRegel++;
            selectGeluid.play();

            if (huidigeRegel < dialoogRegels.size()) {
                huidigVolledigeTekst = dialoogRegels[huidigeRegel];
                huidigZichtbareTekst = "";
                isTekstVolledigZichtbaar = false;

                if (huidigeRegel < sprekers.size()) {
                    speakerTekst.setString(sprekers[huidigeRegel]);
                } else {
                    speakerTekst.setString("");
                }
            } else {
                verberg();  // Geen dialoog meer, verberg de box
                return true;
            }
        } else {
            // Toon direct alle tekst
            huidigZichtbareTekst = huidigVolledigeTekst;
            dialoogTekst.setString(huidigZichtbareTekst);
            isTekstVolledigZichtbaar = true;
        }

        return true;
    }
    if (gebeurtenis.type == sf::Event::MouseButtonPressed &&
        gebeurtenis.mouseButton.button == sf::Mouse::Right) {
        tekstAnimatieSnelheid = 0.01f; // Versnel de tekstanimatie
        return true;
    }
    if (gebeurtenis.type == sf::Event::MouseButtonReleased &&
        gebeurtenis.mouseButton.button == sf::Mouse::Right) {
        tekstAnimatieSnelheid = 0.04f; // Herstel de tekstanimatie snelheid
    }

    return false;
}

bool DialoogBox::heeftMeerDialoog() const {
    return huidigeRegel < dialoogRegels.size();
}