#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>

#include "Cell.h"

#ifndef POPULATION

#define POPULATION

class Population {
    private:
        std::vector<Cell> cells;

    public:
        Population(int, int, sf::Vector2u);
        
        void markHappy();
        void findClosestCells(Cell);
        int calculateDistance(sf::Vector2f, sf::Vector2f);
        void moveUnhappyToRandom();
        std::vector<Cell> getCells();
};

#endif
