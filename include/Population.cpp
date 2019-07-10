#include "Population.h"

Population::Population(int numRaces, int numCellsPerRace, sf::Vector2u windowSize) {
    for (int i = 0; i < numRaces; i++) {
        for (int j = 0; j < numCellsPerRace; j++) {
            cells.emplace_back(i, windowSize);
        }
    }

}

void Population::markHappy() {
    // Find 10 closest cells for each cell
    for (Cell cell : cells) {
        findClosestCells(cell);
    }
}

void Population::findClosestCells(Cell currentCell) {
    // Create 10 cells to store minimum distance
    std::array<std::shared_ptr<CellContainer>, 10> closest;
    for (auto newCell : closest) {
        newCell = std::make_shared<CellContainer>();
    }

    for (Cell cell : cells) {

    }
}

int Population::calculateDistance(sf::Vector2f cellOne, sf::Vector2f cellTwo) {

}

void Population::moveUnhappyToRandom() {

}

std::vector<Cell> Population::getCells() {
    return cells;
}