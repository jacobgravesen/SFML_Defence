#pragma once
#include <SFML/Graphics.hpp>
#include "Path.h"
#include <iostream>

class Enemy {
public:
    sf::CircleShape shape;
    sf::CircleShape healthShape;
    sf::Sprite sprite;
    sf::Texture texture;
    const Path& path;
    size_t currentWaypoint;
    float speed;
    int health;
    int maxHealth;

    Enemy(const Path& path, float speed, int health);
    virtual void update();
    void render(sf::RenderWindow& window);
    void changeHealth(int amount);
    void setSpriteSize(float width, float height);
    int getHealth() const;
    bool isDead() const;

protected:
    virtual void setTexture() = 0;
    void updateHealthShape();
};

// Derived classes
class BasicEnemy : public Enemy {
public:
    BasicEnemy(const Path& path) : Enemy(path, 0.1f, 100) {
        setTexture();
    }
protected:
    void setTexture() override {
        if (!texture.loadFromFile("C:/Users/ProgrammerJ/source/repos/SFML_Defence/SFML_Defence/Resources/zombie.png")) {
            std::cerr << "Error loading texture" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.setPosition(shape.getPosition());
        setSpriteSize(24.f, 24.f);
    }
};

class FastEnemy : public Enemy {
public:
    FastEnemy(const Path& path) : Enemy(path, 0.2f, 75) {
        setTexture();
    }
protected:
    void setTexture() override {
        if (!texture.loadFromFile("C:/Users/ProgrammerJ/source/repos/SFML_Defence/SFML_Defence/Resources/devil.png")) {
            std::cerr << "Error loading texture" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.setPosition(shape.getPosition());
        setSpriteSize(24.f, 24.f);
    }
};

class StrongEnemy : public Enemy {
public:
    StrongEnemy(const Path& path) : Enemy(path, 0.05f, 200) {
        setTexture();
    }
protected:
    void setTexture() override {
        if (!texture.loadFromFile("C:/Users/ProgrammerJ/source/repos/SFML_Defence/SFML_Defence/Resources/slime.png")) {
            std::cerr << "Error loading texture" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
        sprite.setPosition(shape.getPosition());
        setSpriteSize(24.f, 24.f);
    }
};
