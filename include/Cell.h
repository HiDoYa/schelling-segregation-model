#include <SFML/Graphics.hpp>
#include <iostream>

#include "GlobalSettings.h"

#ifndef CELL
#define CELL

// Container to hold cell and calculate distance to each cell
// More memory used per cell but runs quicker computation
struct Closest {
    Closest() : race(-1), distance(INT_MAX), isClosest(false) {};
    int race;
    int distance;
    bool isClosest; // To signal that computation for that cell has been done
};

class Cell {
    private:
        sf::CircleShape circle;
        int race;

    public:
        Cell(int, sf::Vector2u);
        void newRandomPosition(sf::Vector2u);

    friend class Population;
    friend int main();
};

#endif