#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>
#include <iostream>

#include "GlobalSettings.h"
#include "Cell.h"

#ifndef POPULATION

#define POPULATION

// Container to hold cell and calculate distance from the current cell
struct CellContainer {
    CellContainer() : race(-1), distance(INT_MAX) {}
    int race;
    int distance;
};

struct Max {
    Max() : itr(0), dist(0) {}
    void findNewMax(std::array<CellContainer, GlobalSettings::NumNeighbors> cellCont) {
        dist = 0;
        for (int i = 0; i < cellCont.size(); i++) {
            if (cellCont[i].distance > dist) {
                itr = i;
                dist = cellCont[i].distance;
            }
        }
    }
    int itr;
    float dist;
};

class Population {
    private:
        std::vector<Cell> cells;

    public:
        Population(int, int, sf::Vector2u);
        void tick(sf::Vector2u);
        std::vector<Cell> getCells();

    private:
        void markHappy();
        std::array<CellContainer, GlobalSettings::NumNeighbors> findClosestCells(Cell);
        float calculateDistance(sf::Vector2f, sf::Vector2f);
        void moveUnhappyToRandom(sf::Vector2u);
};

#endif
