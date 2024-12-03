#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include "Cell.h"

using namespace std;

class Grid {
protected:
    const int cellSize = 10; 
    const int gridWidth = 80; 
    const int gridHeight = 80; 
    vector<vector<Cell*>> cellules; 
public:
    vector<vector<int>> grid;

    Grid() : cellules(gridWidth, vector<Cell*>(gridHeight, nullptr)) {}

    int get_gridWidth() const{
    return gridWidth;
    }

    int get_cellSize() const{
    return cellSize;
    }

    int get_gridHeight()const {
    return gridHeight;
    }
    const std::vector<std::vector<Cell*>>& getCells() const {
        return cellules;
    }

    void initializeGrid() {
        srand(time(0));
        char type;
        cout << "|R|andom ou |G|rille"<< endl; 
        cin >> type;
        if (type=='R'){ 
            for (int x = 0; x < gridWidth; ++x) {
                for (int y = 0; y < gridHeight; ++y) {
                    if (rand() % 2 == 0) {
                        cellules[x][y] = new DeathCell();
                    } 
                    else {
                        cellules[x][y] = new LifeCell();
                    }
                }
            }
        }
        else if (type == 'G'){
            char caractere;
            ifstream fichier("Grille.txt");
            fichier.get(caractere);
            for (int x = 0; x < gridWidth; ++x) {
                for (int y = 0; y < gridHeight; ++y) {
                    if (fichier.get(caractere)) {
                        if (caractere == '0'){
                            cellules[x][y] = new DeathCell();
                        } 
                        else {
                            cellules[x][y] = new LifeCell();
                        }
                    }
                }
            }
            fichier.close();
        }    
    }
        
            
    
    
    void placePattern(int x, int y, const vector<vector<int>>& pattern) {
            for (int i = 0; i < pattern.size(); ++i) {
                for (int j = 0; j < pattern[i].size(); ++j) {
                    if (pattern[i][j] == 1) {
                        cellules[x + i][y + j] = new LifeCell();
                    } else {
                        cellules[x + i][y + j] = new DeathCell();
                    }
                }
            }
        }
        vector<vector<int>> glider = {
            {0, 1, 0},
            {0, 0, 1},
            {1, 1, 1}
        };
   int compterVoisinsVivants(int i, int j) {
    int nombre_voisin = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Ignore la cellule elle-même
            int nx = i + dx;
            int ny = j + dy;
            if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                if (cellules[nx][ny] && cellules[nx][ny]->estVivante()) {
                    nombre_voisin++;
                }
            }
        }
    }
    return nombre_voisin;
    }

void update() {
    vector<vector<Cell*>> cellules_maj(gridWidth, vector<Cell*>(gridHeight, nullptr));
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            if (dynamic_cast<CelluleObstacle*>(cellules[i][j])) {
              
                cellules_maj[i][j] = cellules[i][j];
                continue;
            }

            if (cellules[i][j]->estVivante()) {
                if (compterVoisinsVivants(i, j) == 2 || compterVoisinsVivants(i, j) == 3) {
                    cellules_maj[i][j] = new LifeCell();
                } else {
                    cellules_maj[i][j] = new DeathCell();
                }
            } else {
                if (compterVoisinsVivants(i, j) == 3) {
                    cellules_maj[i][j] = new LifeCell();
                } else {
                    cellules_maj[i][j] = new DeathCell();
                }
            }
        }
    }
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            delete cellules[i][j];  
            cellules[i][j] = cellules_maj[i][j];
        }
    }
}


    ~Grid() {
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                delete cellules[i][j];
            }
        }
    }
 
void renderGrid(sf::RenderWindow &window) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (cellules[x][y] && cellules[x][y]->estVivante()) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color::White);  
                window.draw(cell);
            }
        }
    }
    window.display();
}
};
