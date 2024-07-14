#include "Path.h"

Path::Path() : line(sf::LinesStrip) {}

void Path::addWaypoint(const sf::Vector2f& point) {
    waypoints.push_back(point);
    line.append(sf::Vertex(point, sf::Color::White));
}

const std::vector<sf::Vector2f>& Path::getWaypoints() const {
    return waypoints;
}

void Path::render(sf::RenderWindow& window) {
    window.draw(line);
}
