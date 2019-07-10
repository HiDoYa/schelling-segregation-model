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
    for (Cell cell : cells) {
        if (currentCell != cell) {
            float dist = calculateDistance(currentCell.circle.getPosition(), cell.circle.getPosition());
            currentCell.checkIfClosest(cell.race, dist);
        }
    }
}

float Population::calculateDistance(sf::Vector2f cellOne, sf::Vector2f cellTwo) {
    sf::Vector2f diff = cellOne - cellTwo;
    return diff.x * diff.x + diff.y * diff.y; // Note: don't need to sqrt
}

void Population::moveUnhappyToRandom() {

}

std::vector<Cell> Population::getCells() {
    return cells;
}