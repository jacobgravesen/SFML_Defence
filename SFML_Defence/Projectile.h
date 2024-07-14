#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"

class Projectile {
public:
    sf::CircleShape shape;
    Enemy* target;
    float speed;
    int damage;

    Projectile(const sf::Vector2f& position, Enemy* target, float speed, int damage);
    bool update();
    void render(sf::RenderWindow& window);
};
