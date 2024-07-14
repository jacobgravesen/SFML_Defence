#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Path {
public:
    std::vector<sf::Vector2f> waypoints;
    sf::VertexArray line;

    Path();
    void addWaypoint(const sf::Vector2f& point);
    const std::vector<sf::Vector2f>& getWaypoints() const;
    void render(sf::RenderWindow& window);
};
