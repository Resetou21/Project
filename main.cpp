#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <Cell.h>
using namespace std;


// Configuration globale
const int cellSize = 10;
const int gridWidth = 80;
const int gridHeight = 80;

// Grille de cellules
vector<vector<int>> grid(gridWidth, vector<int>(gridHeight));

// Fonction d'initialisation de la grille
void initializeGrid() {
    srand(time(0));
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            grid[x][y] = rand() % 2;  // Initialise aléatoirement les cellules comme vivantes ou mortes
        }
    }
}

// Fonction de rendu de la grille
void renderGrid(sf::RenderWindow &window) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));
    cell.setFillColor(sf::Color::White);

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (grid[x][y] == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                window.draw(cell);
            }
        }
    }
    window.display();
}

int main() {
    // Fenêtre SFML
    sf::RenderWindow window(sf::VideoMode(gridWidth * cellSize, gridHeight * cellSize), "Game of Life");

    // Initialiser la grille
    initializeGrid();

    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Afficher la grille
        renderGrid(window);

        // Pause entre les frames
        sf::sleep(sf::milliseconds(100));
    }

    return 0;
}
