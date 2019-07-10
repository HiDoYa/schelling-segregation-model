#include <SFML/Graphics.hpp>

#ifndef CELL
#define CELL

class Cell {
    private:
        sf::CircleShape circle;
        int race;
        bool happy;
        Closest closest[10];

    public:
        Cell(int, sf::Vector2u);
        void resetClosest();
        void checkIfClosest(int, float);

    friend class Population;
    friend int main();
    friend bool operator== (Cell &lhs, Cell &rhs);
    friend bool operator!= (Cell &lhs, Cell &rhs);
};

// Container to hold cell and calculate distance to each cell
// More memory used per cell but runs quicker computation
struct Closest {
    Closest() : race(-1), distance(INT_MAX), isClosest(false) {};
    int race;
    int distance;
    bool isClosest; // To signal that computation for that cell has been done
};

#endif