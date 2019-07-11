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
    markHappy();
    moveUnhappyToRandom(windowSize);
}

std::vector<Cell> Population::getCells() {
    return cells;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////
void Population::markHappy() {
    // Find NumNeighbors closest cells for each cell
    for (Cell& cell : cells) {
        std::array<CellContainer, GlobalSettings::NumNeighbors> closest = findClosestCells(cell);

        // If all races match, happy
        bool isHappy = true;
        int numForeign = 0;
        for (auto eachCellCont : closest) {
            if (cell.race != eachCellCont.race) {
                numForeign++;
                if (numForeign > GlobalSettings::NumNeighbors * GlobalSettings::Tolerance) {   
                    isHappy = false;
                    break;
                }
            }
        }
        cell.happy = isHappy;
    }
}

// Called by markhappy
std::array<CellContainer, GlobalSettings::NumNeighbors> Population::findClosestCells(Cell currentCell) {
    // Create NumNeighbors cells to store minimum distance
    std::array<CellContainer, GlobalSettings::NumNeighbors> closest;

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
    return closest;
}

float Population::calculateDistance(sf::Vector2f cellOne, sf::Vector2f cellTwo) {
    sf::Vector2f diff = cellOne - cellTwo;
    return diff.x * diff.x + diff.y * diff.y; // Note: don't need to sqrt
}

void Population::moveUnhappyToRandom(sf::Vector2u windowSize) {
    for (auto& cell : cells) {
        if (!cell.happy) {
            cell.newRandomPosition(windowSize);
        }
        // Mark each cell as unhappy after (not necessarily happy for two turns in a row)
        cell.happy = false;
    }
}
