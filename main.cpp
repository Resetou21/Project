#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <filesystem>


#include "Grid.h"

using namespace std;

int main() {
    Grid grid;
    sf::RenderWindow window(sf::VideoMode(grid.get_griWidth() * grid.get_cellSize(), grid.get_gridHeight() * grid.get_cellSize()), "Game of Life");
    grid.initializeGrid();

    string outputFolder = "output";
    if (!filesystem::exists(outputFolder)) {
        filesystem::create_directory(outputFolder);
    }

    int iteration = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        iteration++;

        grid.renderGrid(window);


        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}



