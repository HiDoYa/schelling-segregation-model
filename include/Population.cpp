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
        //while (!isHappy) {
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

            // Move
            if (!isHappy) {
                cell.newRandomPosition(windowSize);
            }
        //}

    }
}

std::vector<Cell> Population::getCells() {
    return cells;
}

void Population::parallelClosest(int start, int end, Cell currentCell) {
    for (int i = start; i < end; i++) {
        float curDist = calculateDistance(currentCell.circle.getPosition(), cells[i].circle.getPosition());
        int race = cells[i].race;

        // TODO: Create struct to store curDist and race together. After joinig threads, combine these structs together and sort
        // Note: should operator overload for the struct to have comparisons (should only consider distance for comparisons)
    }
}

// Called by markhappy
std::array<CellContainer, GlobalSettings::NumNeighbors> Population::findClosestCells(Cell currentCell) {
    // Create NumNeighbors cells to store minimum distance
    std::array<CellContainer, GlobalSettings::NumNeighbors> closest;

    const int numThreads = 3;
    std::thread t[numThreads];
    int increment = std::floor(cells.size() / numThreads);
    for (int i = 0; i < numThreads; i++) {
        if (i = numThreads - 1) {
            t[i] = std::thread(parallelClosest, increment * i, cells.size(), currentCell);
        } else {
            t[i] = std::thread(parallelClosest, increment * i, increment * (i + 1), currentCell);
        }
    }

    for (int i = 0; i < numThreads; i++) {
        t[i].join();
    }

    /* Unparallelized closest
    // To keep track of max element in array of NumNeighbors
    Max max;
    for (Cell& cell : cells) {
        float curDist = calculateDistance(currentCell.circle.getPosition(), cell.circle.getPosition());
        if (curDist < max.dist) {
            // Replace the max distance cell with this new closer cell
            closest[max.itr].race = cell.race;
            closest[max.itr].distance = curDist;
            max.findNewMax(closest);
        }
    }
    */

    return closest;
}

float Population::calculateDistance(sf::Vector2f cellOne, sf::Vector2f cellTwo) {
    sf::Vector2f diff = cellOne - cellTwo;
    return diff.x * diff.x + diff.y * diff.y; // Note: don't need to sqrt
}