#include "Cell.h"

Cell::Cell(int _race, sf::Vector2u windowSize) : race(_race), happy(false) {
    // Get random start position
    int xPos = rand() % (int)windowSize.x + 1;
    int yPos = rand() % (int)windowSize.y + 1;

    circle.setPosition(sf::Vector2f(xPos, yPos));
    circle.setRadius(3);

    // TODO Change color based on race
    sf::Color color = _race == 0 ? sf::Color::Blue : (_race == 1 ? sf::Color::Red : sf::Color::Green);
    circle.setFillColor(color);
}

bool operator== (Cell &lhs, Cell &rhs) {
    return (lhs.circle.getPosition() == rhs.circle.getPosition() &&
            lhs.circle.getFillColor() == rhs.circle.getFillColor() &&
            lhs.race == rhs.race);
}