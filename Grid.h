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
private:
    const int cellSize = 10; 
    const int gridWidth = 80; 
    const int gridHeight = 80; 
    vector<vector<Cell*>> cellules; // Déclaration correcte
public:
    vector<vector<int>> grid;

    Grid() : cellules(gridWidth, vector<Cell*>(gridHeight, nullptr)) {} // Initialisation

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
                if (rand() % 2 == 0) {
                    cellules[x][y] = new DeathCell();
                } else {
                    cellules[x][y] = new LifeCell();
                }
            }
        }
    }

   int compterVoisinsVivants(int i, int j) {
    int nombre_voisin = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue; // Ignore la cellule elle-même
            int nx = i + dx;
            int ny = j + dy;

            // Vérifie que les indices sont valides
            if (nx >= 0 && nx < gridWidth && ny >= 0 && ny < gridHeight) {
                if (cellules[nx][ny] && cellules[nx][ny]->estVivante()) {
                    nombre_voisin++;
                }
            }
        }
    }
    return nombre_voisin;
    }

    void update(){
    vector<vector<Cell*>> cellules_maj(gridWidth, vector<Cell*>(gridHeight, nullptr));
        for (int i=0; i < gridWidth;i++){
            for (int j = 0; j < gridHeight; j++){
                if (cellules[i][j]->estVivante()){
                    if (compterVoisinsVivants(i,j)==2 || compterVoisinsVivants(i,j)==3){
                        cellules_maj[i][j]=new LifeCell();
                    } 
                    else {
                        cellules_maj[i][j]=new DeathCell();
                    } 
                }
                else {
                    if (compterVoisinsVivants(i,j)==3){
                        cellules_maj[i][j]=new LifeCell();
                    } 
                    else {
                        cellules_maj[i][j]=new DeathCell();
                    }                
                }
            }
                
        }
        for (int i=0; i < gridWidth;i++){
            for (int j = 0; j < gridHeight; j++){
            cellules[i][j]=cellules_maj[i][j];
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


void writeToFile(const string &filename) {
    ofstream file(filename);  // Ouvrir le fichier
    if (!file.is_open()) {    // Vérifier si l'ouverture a échoué
        cout << "Impossibilité d'ouvrir  le fichier" << endl;
        exit(1);
    } else {
        for (int i = 0; i < gridWidth; i++) {
            for (int j = 0; j < gridHeight; j++) {
                // Vérifier l'état de la cellule et écrire dans le fichier
                if (cellules[i][j] && cellules[i][j]->estVivante()) {
                    file << "1 ";  
                } else {
                    file << "0 ";  
                }
            }
            file << endl;  
        }
    }
}



};
