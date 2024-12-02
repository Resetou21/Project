#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <filesystem>
#include "Grid.h"
#include "FileManagement.h"
#include "Patern.h"

namespace fs = std::filesystem;
using namespace std;

int main() {
    vector<vector<int>> glider = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };

    int iteration = 0;

    bool isPaused = false; 
    Grid grid;

    sf::RenderWindow window(sf::VideoMode(grid.get_gridWidth() * grid.get_cellSize(), grid.get_gridHeight() * grid.get_cellSize()), "Game of Life");
    grid.initializeGrid();
    
    string outputFolder = "output";
    if (!filesystem::exists(outputFolder)) {
        filesystem::create_directory(outputFolder);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                FileManagement::deleteTxtFilesInDirectory(outputFolder);  
                window.close();  
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::G) {
                    grid.placePattern(10, 10, glider);  
                }
                if (event.key.code == sf::Keyboard::Space) {
                    isPaused = !isPaused; 
                }
            }
        }
        if (!isPaused) {
            grid.update();  
            FileManagement::writeToFile(outputFolder + "/iteration_" + to_string(iteration) + ".txt", "Some content to write");
            iteration++;
        }
        grid.renderGrid(window);
        FileManagement::writeToFile(outputFolder + "/iteration_" + to_string(iteration) + ".txt", "Some content to write");
        iteration++;
        sf::sleep(sf::milliseconds(100));
    }
    return 0;
};
