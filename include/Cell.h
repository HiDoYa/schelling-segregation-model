#include <SFML/Graphics.hpp>

#ifndef CELL
#define CELL

class Cell {
    private:
        sf::CircleShape circle;
        int race;
        bool happy;

        CellContainer closest[10];

        friend class Population;
        friend int main();
        friend bool operator== (Cell &lhs, Cell &rhs);
    public:
        Cell(int, sf::Vector2u);
};

// Container to hold cell and calculate distance to each cell
// More memory used per cell but runs quicker computation
struct CellContainer {
    CellContainer() : cell(std::make_shared<Cell>(-1, sf::Vector2u(0,0))), distance(INT_MAX), isClosest(false) {};
    std::shared_ptr<Cell> cell;
    int distance;
    bool isClosest;
};

#endif