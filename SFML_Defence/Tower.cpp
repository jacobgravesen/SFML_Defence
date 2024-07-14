#include "Tower.h"
#include <iostream>

Tower::Tower(sf::Vector2f position, float range, float fireRate, int damage, float projectileSpeed)
    : range(range), fireRate(fireRate), damage(damage), projectileSpeed(projectileSpeed) {
    shape.setRadius(20.f);
    shape.setFillColor(sf::Color::Blue); // Default color for the first tower
    shape.setOrigin(shape.getRadius(), shape.getRadius()); // Center the shape
    shape.setPosition(position);

    // Load the archer texture and set it to the sprite
    if (!texture.loadFromFile("C:/Users/ProgrammerJ/source/repos/SFML_Defence/SFML_Defence/Resources/archer.png")) {
        std::cerr << "Error loading texture" << std::endl;
    }
    else {
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2); // Center the sprite
        setSpriteSize(32.f, 32.f); // Set default size to 32x32
    }

    setPosition(position); // Set the initial position and update the sprite position
}

void Tower::update(std::vector<std::shared_ptr<Enemy>>& enemies) {
    if (fireClock.getElapsedTime().asSeconds() >= fireRate) {
        for (auto& enemy : enemies) {
            if (isInRange(enemy)) {
                std::cout << "Tower firing at enemy! Distance: " << getDistance(enemy) << std::endl;
                // Create a new projectile targeting the enemy
                projectiles.push_back(Projectile(shape.getPosition(), enemy.get(), projectileSpeed, damage));
                fireClock.restart();
                rotateSpriteTowards(enemy->shape.getPosition()); // Rotate sprite towards the enemy
                break;
            }
        }
    }

    // Update projectiles
    for (auto it = projectiles.begin(); it != projectiles.end();) {
        if (it->update()) {
            std::cout << "Projectile hit enemy! Target health: " << it->target->getHealth() << std::endl;
            it = projectiles.erase(it); // Erase the projectile if it hit the target
        }
        else {
            ++it;
        }
    }
}

void Tower::render(sf::RenderWindow& window) {
    window.draw(shape);
    if (sprite.getTexture()) {
        window.draw(sprite); // Draw the sprite on top of the shape
    }
    for (auto& projectile : projectiles) {
        projectile.render(window);
    }
}

bool Tower::isInRange(const std::shared_ptr<Enemy>& enemy) {
    float distance = getDistance(enemy);
    return distance <= range;
}

float Tower::getDistance(const std::shared_ptr<Enemy>& enemy) {
    sf::Vector2f towerPos = shape.getPosition();
    sf::Vector2f enemyPos = enemy->shape.getPosition();
    float distance = std::sqrt(std::pow(towerPos.x - enemyPos.x, 2) + std::pow(towerPos.y - enemyPos.y, 2));
    return distance;
}

void Tower::setSpriteSize(float width, float height) {
    if (sprite.getTexture()) {
        float originalWidth = static_cast<float>(texture.getSize().x);
        float originalHeight = static_cast<float>(texture.getSize().y);
        sprite.setScale(width / originalWidth, height / originalHeight);
    }
    else {
        std::cerr << "Error: Attempted to set size of a sprite without a texture" << std::endl;
    }
}

void Tower::setPosition(const sf::Vector2f& position) {
    shape.setPosition(position);
    updateSpritePosition(); // Ensure sprite follows the tower shape
}

void Tower::updateSpritePosition() {
    sprite.setPosition(shape.getPosition());
}

void Tower::rotateSpriteTowards(const sf::Vector2f& targetPosition) {
    sf::Vector2f direction = targetPosition - shape.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159f; // Convert radians to degrees

    if (angle > 90 || angle < -90) {
        sprite.setScale(sprite.getScale().x, -std::abs(sprite.getScale().y)); // Mirror the sprite
        sprite.setRotation(angle); // Adjust for the mirroring
    }
    else {
        sprite.setScale(sprite.getScale().x, std::abs(sprite.getScale().y)); // Ensure it's not mirrored
        sprite.setRotation(angle);
    }
}
