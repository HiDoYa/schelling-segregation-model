#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <iostream>


#include "include/GlobalSettings.h"
#include "include/Population.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(800, 800), "Schelling Segregation Model");
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
                    if (event.key.code == sf::Keyboard::R) {
                        population = Population(GlobalSettings::NumRaces, GlobalSettings::NumCellsPerRace, windowSize);
                    } else {
                        population.tick(windowSize);
                    }
                    break;
                default:
                    break;
            }
        }

        /*
        // Save to file
        sf::Texture texture;
        texture.create(windowSize.x, windowSize.y);
        texture.update(window);
        sf::Image image = texture.copyToImage();
        image.saveToFile("/Users/hidoya/Downloads/Test/image" + std::to_string(fileCounter) + ".jpg");
        } */


        window.clear(sf::Color(50, 50, 50));

        std::vector<Cell> cells = population.getCells();
        for (Cell cell : cells) {
            window.draw(cell.circle);
        }

        window.display();
    }
    return 0;
}