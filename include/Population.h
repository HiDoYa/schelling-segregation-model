#include <SFML/Graphics.hpp>
#include <vector>
#include <array>
#include <memory>
#include <iostream>
#include <thread>
#include <cmath>
#include <algorithm>

#include "GlobalSettings.h"
#include "Cell.h"

#ifndef POPULATION

#define POPULATION

// Container to hold cell and calculate distance from the current cell
struct CellContainer {
    CellContainer() : race(-1), distance(INT_MAX) {}
    int race;
    float distance;
    friend bool operator< (const CellContainer& lhs, const CellContainer& rhs) {
        return lhs.distance < rhs.distance;
    }
    CellContainer& operator= (const CellContainer& cellCont) {
        race = cellCont.race;
        distance = cellCont.distance;
        return *this;
    }
};

class Population {
    private:
        std::vector<Cell> cells;
        std::array<CellContainer, GlobalSettings::NumCellsPerRace * GlobalSettings::NumRaces> cellContainers;

    public:
        Population(int, int, sf::Vector2u);
        void tick(sf::Vector2u);
        std::vector<Cell> getCells();

    private:
        void parallelClosest(int, int, Cell);
        std::array<CellContainer, GlobalSettings::NumNeighbors> findClosestCells(Cell);
        float calculateDistance(sf::Vector2f, sf::Vector2f);
};

#endif
