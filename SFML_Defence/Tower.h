#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Enemy.h"
#include "Projectile.h"

class Tower {
public:
    sf::CircleShape shape;
    sf::Sprite sprite; // Add sprite for the image
    sf::Texture texture; // Add texture for the sprite
    float range;
    float fireRate;
    int damage;
    float projectileSpeed;
    sf::Clock fireClock;
    std::vector<Projectile> projectiles;

    Tower(sf::Vector2f position, float range, float fireRate, int damage, float projectileSpeed);
    void update(std::vector<std::shared_ptr<Enemy>>& enemies);
    void render(sf::RenderWindow& window);
    bool isInRange(const std::shared_ptr<Enemy>& enemy);
    void setSpriteSize(float width, float height);
    void setPosition(const sf::Vector2f& position);

private:
    float getDistance(const std::shared_ptr<Enemy>& enemy);
    void updateSpritePosition();
    void rotateSpriteTowards(const sf::Vector2f& targetPosition);
};
