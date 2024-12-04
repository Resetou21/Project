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

    Grid(); // Constructeur
    ~Grid(); // Destructeur

    // Getters
    int get_gridWidth() const;
    int get_cellSize() const;
    int get_gridHeight() const;
    const std::vector<std::vector<Cell*>>& getCells() const;
    string test(int x, int y,int nombre_voisin);
    // Méthodes principales
    void initializeGrid(); // initialisation de la grille
    void test_unitaire();
    void placeObstacle(int x, int y); // placement d'obstacle sur la grille
    void placeLifeCell(int x, int y); // placement de celulle vivante sur la grille
    void placePattern(int x, int y, const vector<vector<int>>& pattern); 
    int compterVoisinsVivants(int i, int j); // Methode permettant de compter le nombre de voisins
    void update(); // met a jour la grille
    void renderGrid(sf::RenderWindow& window);
    void resutlat_test_unitaire();
};
