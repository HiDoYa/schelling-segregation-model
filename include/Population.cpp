#include "Population.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////
Population::Population(int numRaces, int numCellsPerRace, sf::Vector2u windowSize) {
    for (int i = 0; i < numRaces; i++) {
        for (int j = 0; j < numCellsPerRace; j++) {
            cells.emplace_back(i, windowSize);
        }
    }
}

void Population::tick(sf::Vector2u windowSize) {
    // Find NumNeighbors closest cells for each cell
    for (Cell& cell : cells) {
        bool isHappy = false;
        // Repeat until happy
        while (!isHappy) {
            isHappy = true;

            // If too many foreign, unhappy
            std::array<CellContainer, GlobalSettings::NumNeighbors> closest = findClosestCells(cell);
            int numForeign = 0;
            for (auto eachCellCont : closest) {
                if (cell.race != eachCellCont.race) {
                    numForeign++;
                }
            }
            if (numForeign > GlobalSettings::NumNeighbors * GlobalSettings::Tolerance) {   
                isHappy = false;
            }

            // Move if unhappy
            if (!isHappy) {
                cell.newRandomPosition(windowSize);
            }
        }
    }
}

std::vector<Cell> Population::getCells() {
    return cells;
}

// Collect all distances in cellContainers
void Population::parallelClosest(int start, int end, Cell currentCell) {
    for (int i = start; i < end; i++) {
        cellContainers[i].distance = calculateDistance(currentCell.circle.getPosition(), cells[i].circle.getPosition());
        cellContainers[i].race = cells[i].race;
    }
}

// Called by markhappy
std::array<CellContainer, GlobalSettings::NumNeighbors> Population::findClosestCells(Cell currentCell) {
    // Create threads to compute Euclidean distance
    std::thread t[GlobalSettings::NumThreads];
    int increment = std::floor(cells.size() / GlobalSettings::NumThreads);
    for (int i = 0; i < GlobalSettings::NumThreads; i++) {
        if (i == GlobalSettings::NumThreads - 1) {
            // For the last thread, make sure to include the last cell (prevent off by one error)
            t[i] = std::thread(&Population::parallelClosest, this, increment * i, cells.size(), currentCell);
        } else {
            t[i] = std::thread(&Population::parallelClosest, this, increment * i, increment * (i + 1), currentCell);
        }
    }

    // Wait for all computations
    for (int i = 0; i < GlobalSettings::NumThreads; i++) {
        t[i].join();
    }

    // Sort cell containers and keep the lowest 10
    std::array<CellContainer, GlobalSettings::NumNeighbors> closest;
    std::sort(cellContainers.begin(), cellContainers.end());
    int selfOffset = 0;
    for (int i = 0; i < closest.size(); i++) {
        if (cellContainers[i].distance == 0 && cellContainers[i].race == currentCell.race) {
            // Don't want to store the distance to itself
            selfOffset = 1;
        }
        closest[i] = cellContainers[i + selfOffset];
    }

    return closest;
}

float Population::calculateDistance(sf::Vector2f cellOne, sf::Vector2f cellTwo) {
    sf::Vector2f diff = cellOne - cellTwo;
    return diff.x * diff.x + diff.y * diff.y; // Note: don't need to sqrt
}