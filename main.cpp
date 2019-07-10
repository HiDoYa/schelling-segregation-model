#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>

#include "include/Population.h"

const int numRaces = 3;
const int numCellsPerRace = 5;

int main() {
    sf::RenderWindow window(sf::VideoMode(1024, 768), "Schelling Segregation Model");
    window.setFramerateLimit(60);
    sf::Event event;
    srand(time(NULL));

    Population population(numRaces, numCellsPerRace, window.getSize());

    while (window.isOpen()) {
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    break;
                default:
                    break;
            }
        }

        window.clear(sf::Color(100, 100, 100));

        std::vector<Cell> cells = population.getCells();
        for (Cell cell : cells) {
            window.draw(cell.circle);
        }

        window.display();
    }
    return 0;
}