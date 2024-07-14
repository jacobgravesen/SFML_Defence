#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Tower.h"
#include "WaveManager.h"  // Add this line

class Sidebar {
public:
    Sidebar(float width, float height, WaveManager& waveManager); // Add WaveManager reference
    void render(sf::RenderWindow& window);
    bool handleMouseClick(sf::Vector2f position, std::unique_ptr<Tower>& selectedTower);
    bool handleNextWaveClick(sf::Vector2f position);

private:
    float width;
    float height;
    sf::RectangleShape background;
    std::vector<sf::CircleShape> towerIcons;
    sf::RectangleShape nextWaveButton;
    sf::Font font;
    sf::Text nextWaveButtonText;
    WaveManager& waveManager;  // Add this member
};
