#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

class Grid {
private:
    const int cellSize = 10; 
    const int gridWidth = 80; 
    const int gridHeight = 80; 

public:
    vector<vector<int>> grid;

    Grid() : grid(gridWidth, vector<int>(gridHeight)) {}

    int get_griWidth(){
    return gridWidth;
    }

    int get_cellSize(){
    return cellSize;
    }

    int get_gridHeight(){
    return gridHeight;
    }
   
    void initializeGrid() {
        srand(time(0));
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                grid[x][y] = rand() % 2;  
            }
        }
    }


    void renderGrid(sf::RenderWindow &window) {
        window.clear();
        sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f)); 


        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                if (grid[x][y] == 1) {  
                    cell.setPosition(x * cellSize, y * cellSize);
                    cell.setFillColor(sf::Color::White);  
                    window.draw(cell);
                }
            }
        }
        window.display();
    }
};
