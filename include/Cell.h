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
        Closest closest[GlobalSettings::NumNeighbors];

    public:
        Cell(int, sf::Vector2u);
        void resetClosest();
        void newRandomPosition(sf::Vector2u);

    friend class Population;
    friend int main();
    friend bool operator== (Cell &lhs, Cell &rhs);
    friend bool operator!= (Cell &lhs, Cell &rhs);
};

#endif