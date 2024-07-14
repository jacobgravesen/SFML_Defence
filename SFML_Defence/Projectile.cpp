#include "Projectile.h"
#include <cmath>

Projectile::Projectile(const sf::Vector2f& position, Enemy* target, float speed, int damage)
    : target(target), speed(speed), damage(damage) {
    shape.setRadius(5.f);
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition(position);
}

bool Projectile::update() {
    if (target == nullptr || target->getHealth() <= 0) {
        return true; // Target is dead or null
    }

    sf::Vector2f direction = target->shape.getPosition() - shape.getPosition();
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length < speed) {
        target->changeHealth(-damage); // Deal damage
        return true; // Hit the target
    }
    else {
        direction /= length; // Normalize the direction vector
        shape.move(direction * speed);
        return false; // Still in motion
    }
}

void Projectile::render(sf::RenderWindow& window) {
    window.draw(shape);
}
