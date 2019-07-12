#include "Cell.h"

Cell::Cell(int _race, sf::Vector2u windowSize) : race(_race) {
    // Get random start position
    newRandomPosition(windowSize);
    circle.setRadius(3);

    // Change color based on race
    sf::Color color;
    switch (_race) {
        case 0: color = sf::Color::Red; break;
        case 1: color = sf::Color::Blue; break;
        case 2: color = sf::Color::Green; break;
        case 3: color = sf::Color::Blue; break;
        case 4: color = sf::Color::Black; break;
        case 5: color = sf::Color::White; break;
        case 6: color = sf::Color::Yellow; break;
        case 7: color = sf::Color::Magenta; break;
        default: color = sf::Color::Cyan; break;
    }

    circle.setFillColor(color);
    circle.setOutlineColor(sf::Color::White);
    circle.setOutlineThickness(1);
}

bool operator== (Cell &lhs, Cell &rhs) {
    return (lhs == rhs); // Only true if both are pointers to same thing (don't care about the value)
}

bool operator!= (Cell&lhs, Cell &rhs) {
    return (lhs != rhs);
}

void Cell::newRandomPosition(sf::Vector2u windowSize) {
    int xPos = rand() % (int)windowSize.x + 1;
    int yPos = rand() % (int)windowSize.y + 1;

    circle.setPosition(sf::Vector2f(xPos, yPos));
}