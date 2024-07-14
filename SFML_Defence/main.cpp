#include <SFML/Graphics.hpp>
#include "Path.h"
#include "Enemy.h"
#include "Tower.h"
#include "Sidebar.h"
#include "WaveManager.h"
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

bool isValidPlacement(sf::Vector2f position);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Tower Defense Game");

    // Load the background texture
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    bool backgroundLoaded = backgroundTexture.loadFromFile("C:/Users/ProgrammerJ/source/repos/SFML_Defence/SFML_Defence/Resources/background.png");

    if (backgroundLoaded) {
        backgroundSprite.setTexture(backgroundTexture);

        // Output texture size for debugging
        sf::Vector2u textureSize = backgroundTexture.getSize();
        std::cout << "Background texture loaded: " << textureSize.x << "x" << textureSize.y << std::endl;

        // Scale the background to fit the window
        sf::Vector2u windowSize = window.getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
        backgroundSprite.setPosition(0, 0); // Ensure the background is at the top left corner
    }
    else {
        std::cerr << "Background not found, using black color" << std::endl;
    }

    Path path;
    path.addWaypoint({ 489.f, 259.f });
    path.addWaypoint({ 288.f, 259.f });
    path.addWaypoint({ 217.f, 299.f });
    path.addWaypoint({ 156.f, 259.f });
    path.addWaypoint({ 406.f, 116.f });
    path.addWaypoint({ 575.f, 203.f });
    path.addWaypoint({ 581.f, 294.f });
    path.addWaypoint({ 583.f, 389.f });
    path.addWaypoint({ 396.f, 480.f });
    path.addWaypoint({ 181.f, 372.f });

    std::vector<std::shared_ptr<Enemy>> enemies;
    std::vector<std::shared_ptr<Tower>> towers;
    std::unique_ptr<Tower> selectedTower = nullptr;

    // Initialize wave manager with multiple waves
    std::vector<Wave> waves = {
        Wave({ {EnemyType::Basic, 5} }, 2.5f), // Spawn interval for first wave
        Wave({ {EnemyType::Basic, 10}, {EnemyType::Fast, 5} }, 2.3f), // Adjusted spawn interval for second wave
        Wave({ {EnemyType::Basic, 15}, {EnemyType::Strong, 3} }, 1.5f), // Adjusted spawn interval for third wave
        Wave({ {EnemyType::Basic, 20}, {EnemyType::Fast, 10}, {EnemyType::Strong, 5} }, 2.0f), // Adjusted spawn interval for fourth wave
    };

    WaveManager waveManager(waves);
    Sidebar sidebar(200.0f, 600.0f, waveManager); // Pass the WaveManager reference

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (sidebar.handleMouseClick(mousePos, selectedTower)) {
                    continue;
                }
                if (sidebar.handleNextWaveClick(mousePos)) {
                    if (waveManager.isWaveCompleted(enemies)) {
                        waveManager.startNextWave();
                        std::cout << "Next wave started!" << std::endl;
                    }
                    continue;
                }
                if (selectedTower != nullptr) {
                    if (isValidPlacement(mousePos)) {
                        selectedTower->setPosition(mousePos);
                        towers.push_back(std::move(selectedTower));

                        std::cout << "Placed tower at position: " << mousePos.x << ", " << mousePos.y << std::endl;
                        selectedTower.reset();
                        std::cout << "Reset selectedTower" << std::endl;

                        std::cout << "Towers vector size: " << towers.size() << std::endl;
                        for (size_t i = 0; i < towers.size(); ++i) {
                            std::cout << "Tower " << i << " at position: " << towers[i]->shape.getPosition().x << ", " << towers[i]->shape.getPosition().y << std::endl;
                        }
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        waveManager.update(deltaTime, enemies, path);

        if (selectedTower != nullptr) {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            selectedTower->setPosition(mousePos);
        }

        for (auto& enemy : enemies) {
            enemy->update();
        }

        for (auto& tower : towers) {
            tower->update(enemies);
        }

        enemies.erase(std::remove_if(enemies.begin(), enemies.end(),
            [](const std::shared_ptr<Enemy>& enemy) { return enemy->isDead(); }), enemies.end());

        window.clear();

        if (backgroundLoaded) {
            window.draw(backgroundSprite); // Draw the background if loaded
        }
        else {
            window.clear(sf::Color::Black); // Use black background if not loaded
        }

        path.render(window); // Render the path
        for (auto& enemy : enemies) {
            enemy->render(window);
        }
        for (auto& tower : towers) {
            tower->render(window);
        }
        sidebar.render(window); // Render the sidebar
        if (selectedTower != nullptr) {
            selectedTower->render(window); // Render the selected tower preview
        }
        window.display();
    }

    return 0;
}

bool isValidPlacement(sf::Vector2f position) {
    // Add your valid placement logic here
    // For simplicity, return true for now
    return true;
}
