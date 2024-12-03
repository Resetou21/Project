#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <filesystem>
#include "Grid.h"
#include "FileManagement.h"


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
                 if (event.key.code == sf::Keyboard::Space) {
                    isPaused = !isPaused; 
                    if (isPaused) {
                        cout << "Jeu mis en pause" << endl; 
                    }
                }
                if (event.key.code == sf::Keyboard::O) {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                    int X = mousePos.x / grid.get_cellSize();
                    int Y = mousePos.y / grid.get_cellSize();
                    grid.placeObstacle(X, Y); 
                }
            }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                    cout << "Glidder implémenté " << endl;
                    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                         int X = mousePos.x / grid.get_cellSize();
                         int Y = mousePos.y / grid.get_cellSize();

                    grid.placePattern(X, Y, glider);
            }
        }
        if (!isPaused) {
            grid.update();  
            FileManagement::writeToFile(outputFolder + "/iteration_" + to_string(iteration) + ".txt", grid);

            iteration++;
        }
        grid.renderGrid(window);
        iteration++;
        sf::sleep(sf::milliseconds(0));
    }
    return 0;
};
