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
                    int random = rand();
                    if (random % 101 == 0) {
                        cellules[x][y] = new CelluleObstacle();
                    } 
                    else if(random % 5 == 0){
                        cellules[x][y] = new LifeCell();
                    }
                    else
                    {
                        cellules[x][y] = new DeathCell();
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
                        else if(caractere == '1'){
                            cellules[x][y] = new LifeCell();
                        }
                        else if (caractere == '2'){
                            cellules[x][y] = new CelluleObstacle();
                        }
                        else{
                             cellules[x][y] = new DeathCell();
                        }
                    }
                }
            }
            fichier.close();
        }    
    }
            
      void placeObstacle(int x, int y) {
            if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                if (!dynamic_cast<CelluleObstacle*>(cellules[x][y])) {
                    cellules[x][y] = new CelluleObstacle();
                    cout << "Cellule obstacle placée à (" << x << ", " << y << ")" << endl;
                }
            }
        }
        void placeLifeCell(int x, int y){
             if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
                if (!dynamic_cast<LifeCell*>(cellules[x][y])) {
                    delete cellules[x][y];
                    cellules[x][y] = new LifeCell();
                    cout << "Cellule Vivante placée à (" << x << ", " << y << ")" << endl;
                }
            }
        }

            void placePattern(int x, int y, const vector<vector<int>>& pattern) {
                for (int i = 0; i < pattern.size(); ++i) {
                    for (int j = 0; j < pattern[i].size(); ++j) {
                        if (x + i >= 0 && x + i < gridWidth && y + j >= 0 && y + j < gridHeight) {
                            if (pattern[i][j] == 1) {
                                if (dynamic_cast<CelluleObstacle*>(cellules[x + i][y + j]) == nullptr) {
                                    cellules[x + i][y + j] = new LifeCell();
                                }
                            } else {
                                if (dynamic_cast<CelluleObstacle*>(cellules[x + i][y + j]) == nullptr) {
                                    cellules[x + i][y + j] = new DeathCell();
                                }
                            }
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
                if (dx == 0 && dy == 0) continue; 

                int nx = (i + dx + gridWidth) % gridWidth;  
                int ny = (j + dy + gridHeight) % gridHeight;

                if (cellules[nx][ny] && cellules[nx][ny]->estVivante()==1) {
                    nombre_voisin++;
                }
            }
        }
        return nombre_voisin;
    }

    void update() {
        vector<vector<Cell*>> cellules_maj(gridWidth, vector<Cell*>(gridHeight, nullptr));
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {

                if (cellules[i][j]->estVivante()==2) {
                    cellules_maj[i][j] = new CelluleObstacle();
                } 
                if (cellules[i][j]->estVivante()==1) {
                    if (compterVoisinsVivants(i, j) == 2 || compterVoisinsVivants(i, j) == 3) {
                        cellules_maj[i][j] = new LifeCell();
                    } else {
                        cellules_maj[i][j] = new DeathCell();
                    }

                } 
                else if (cellules[i][j]->estVivante()==0) {
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
                if (cellules[x][y] && cellules[x][y]->estVivante()==1) {
                    cell.setPosition(x * cellSize, y * cellSize);
                    cell.setFillColor(sf::Color::White);  
                    window.draw(cell);
                }
                else if (cellules[x][y] && cellules[x][y]->estVivante()==2) {
                    cell.setPosition(x * cellSize, y * cellSize);
                    cell.setFillColor(sf::Color::Red);  
                    window.draw(cell);
                }
            }
        }
        window.display();
    }
};