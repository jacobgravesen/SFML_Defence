#include "Enemy.h"
#include <cmath>
#include <iostream>

Enemy::Enemy(const Path& path, float speed, int health)
    : path(path), currentWaypoint(0), speed(speed), health(health), maxHealth(health) {
    shape.setRadius(10.f);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(shape.getRadius(), shape.getRadius());
    shape.setPosition(path.getWaypoints()[0]);

    healthShape.setFillColor(sf::Color::Black);
    healthShape.setPosition(shape.getPosition());
    healthShape.setRadius(0.f);
    healthShape.setOrigin(healthShape.getRadius(), healthShape.getRadius());
}

void Enemy::update() {
    if (currentWaypoint < path.getWaypoints().size()) {
        sf::Vector2f direction = path.getWaypoints()[currentWaypoint] - shape.getPosition();
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length < speed) {
            shape.setPosition(path.getWaypoints()[currentWaypoint]);
            currentWaypoint++;
        }
        else {
            direction /= length;
            shape.move(direction * speed);
        }
        sprite.setPosition(shape.getPosition());
    }

    updateHealthShape();
    healthShape.setPosition(shape.getPosition());
}

void Enemy::render(sf::RenderWindow& window) {
    window.draw(shape);
    window.draw(sprite);
    window.draw(healthShape);
}

void Enemy::changeHealth(int amount) {
    health += amount;
    if (health <= 0) {
        health = 0;
        shape.setFillColor(sf::Color::Transparent);
        healthShape.setFillColor(sf::Color::Transparent);
        sprite.setColor(sf::Color(255, 255, 255, 0));
        std::cout << "Enemy died!" << std::endl;
    }
}

int Enemy::getHealth() const {
    return health;
}

bool Enemy::isDead() const {
    return health <= 0;
}

void Enemy::updateHealthShape() {
    float healthRatio = static_cast<float>(health) / maxHealth;
    float innerRadius = shape.getRadius() * (1 - healthRatio);
    healthShape.setRadius(innerRadius);
    healthShape.setOrigin(innerRadius, innerRadius);
}

void Enemy::setSpriteSize(float width, float height) {
    float originalWidth = static_cast<float>(texture.getSize().x);
    float originalHeight = static_cast<float>(texture.getSize().y);
    sprite.setScale(width / originalWidth, height / originalHeight);
}
