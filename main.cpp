#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>


#include "include/GlobalSettings.h"
#include "include/Population.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Schelling Segregation Model");
    sf::Vector2u windowSize = window.getSize();
    window.setFramerateLimit(60);
    sf::Event event;
    srand(time(NULL));

    Population population(GlobalSettings::NumRaces, GlobalSettings::NumCellsPerRace, windowSize);

    while (window.isOpen()) {
        while(window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    population.tick(windowSize);
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