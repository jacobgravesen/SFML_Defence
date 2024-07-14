#include "Sidebar.h"
#include <iostream>

Sidebar::Sidebar(float width, float height, WaveManager& waveManager) : width(width), height(height), waveManager(waveManager) {
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(sf::Color(200, 200, 200));
    background.setPosition(sf::Vector2f(600, 0)); // Position the sidebar at the right edge of the window

    // Add tower icons
    sf::CircleShape towerIcon1(20.f);
    towerIcon1.setFillColor(sf::Color::Blue);
    towerIcon1.setPosition(620, 50);
    towerIcons.push_back(towerIcon1);

    sf::CircleShape towerIcon2(20.f);
    towerIcon2.setFillColor(sf::Color::Green);
    towerIcon2.setPosition(620, 100);
    towerIcons.push_back(towerIcon2);

    // Load font
    if (!font.loadFromFile("arial.ttf")) {
        // Handle error
    }

    // Add next wave button
    nextWaveButton.setSize(sf::Vector2f(160, 40));
    nextWaveButton.setFillColor(sf::Color::Red);
    nextWaveButton.setPosition(620, 500);

    nextWaveButtonText.setFont(font);
    nextWaveButtonText.setString("Next Wave");
    nextWaveButtonText.setCharacterSize(24);
    nextWaveButtonText.setFillColor(sf::Color::White);
    nextWaveButtonText.setPosition(630, 510);
}

void Sidebar::render(sf::RenderWindow& window) {
    window.draw(background);
    for (const auto& icon : towerIcons) {
        window.draw(icon);
    }
    window.draw(nextWaveButton);
    window.draw(nextWaveButtonText);
}

bool Sidebar::handleMouseClick(sf::Vector2f position, std::unique_ptr<Tower>& selectedTower) {
    if (background.getGlobalBounds().contains(position)) {
        for (size_t i = 0; i < towerIcons.size(); ++i) {
            if (towerIcons[i].getGlobalBounds().contains(position)) {
                // Select tower
                selectedTower = std::make_unique<Tower>(sf::Vector2f(0, 0), 150.f, 1.0f, 10, 5.0f);
                if (i == 0) {
                    selectedTower->shape.setFillColor(sf::Color::Blue);
                }
                else {
                    selectedTower->shape.setFillColor(sf::Color::Green);
                }
                return true;
            }
        }
    }
    return false;
}

bool Sidebar::handleNextWaveClick(sf::Vector2f position) {
    bool clicked = nextWaveButton.getGlobalBounds().contains(position);
    if (clicked) {
        std::cout << "Next wave button clicked!" << std::endl;
        waveManager.startNextWave(); // Add this line
    }
    return clicked;
}
