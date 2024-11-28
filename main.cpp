#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Cell.h"
using namespace std;

const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

// Grille de cellules
vector<vector<Cell*>> grid(gridWidth, vector<Cell*>(gridHeight));

void initializeGrid() {
    srand(time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            // Initialiser aléatoirement les cellules
            int randomCellType = rand() % 3;
            if (randomCellType == 0) {
                grid[x][y] = new LifeCell();  // Cellule vivante
            } else if (randomCellType == 1) {
                grid[x][y] = new CelluleMorte();  // Cellule morte
            } else {
                grid[x][y] = new CelluleObstacle();  // Cellule obstacle
            }
        }
    }
}

void renderGrid(sf::RenderWindow &window) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            // Vérifier si la cellule est vivante
            if (grid[x][y]->estVivante()) {
                cell.setFillColor(sf::Color::White);  // Cellule vivante en blanc
            } else {
                cell.setFillColor(sf::Color::Black);  // Cellule morte en noir
            }

            cell.setPosition(x * cellSize, y * cellSize);
            window.draw(cell);
        }
    }

    window.display();
}

int main() {

    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");


    initializeGrid();


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        renderGrid(window);

 
        sf::sleep(sf::milliseconds(100));
    }


    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            delete grid[x][y];  
        }
    }

    return 0;
}