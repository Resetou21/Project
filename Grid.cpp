#include "Grid.h"
#include "Cell.h"

Grid::Grid() : cellules(gridWidth, vector<Cell*>(gridHeight, nullptr)) {}

Grid::~Grid() {
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            delete cellules[i][j];
        }
    }
}

int Grid::get_gridWidth() const {
    return gridWidth;
}

int Grid::get_cellSize() const {
    return cellSize;
}

int Grid::get_gridHeight() const {
    return gridHeight;
}

const std::vector<std::vector<Cell*>>& Grid::getCells() const {
    return cellules;
}

void Grid::initializeGrid() {
    srand(time(0));
    char type;
    cout << "|R|andom ou |G|rille" << endl;
    cin >> type;
    if (type == 'R') {
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                int random = rand();
                if (random % 101 == 0) {
                    cellules[x][y] = new ObstacleCell();
                } else if (random % 5 == 0) {
                    cellules[x][y] = new LifeCell();
                } else {
                    cellules[x][y] = new DeathCell();
                }
            }
        }
    } else if (type == 'G') {
        string gril;
        char caractere;
        cout << "Chemin vers le fichier"<<endl;
        cin>> gril;
        ifstream fichier(gril);
        fichier.get(caractere);
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                if (fichier.get(caractere)) {
                    if (caractere == '0') {
                        cellules[x][y] = new DeathCell();
                    } else if (caractere == '1') {
                        cellules[x][y] = new LifeCell();
                    } else if (caractere == '2') {
                        cellules[x][y] = new ObstacleCell();
                    } else {
                        cellules[x][y] = new DeathCell();
                    }
                }
            }
        }
        fichier.close();
    }
}



void Grid::placeObstacle(int x, int y) {
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        if (!dynamic_cast<ObstacleCell*>(cellules[x][y])) {
            cellules[x][y] = new ObstacleCell();
            cout << "Cellule obstacle placée à (" << x << ", " << y << ")" << endl;
        }
    }
}

void Grid::placeLifeCell(int x, int y) {
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        if (!dynamic_cast<LifeCell*>(cellules[x][y])) {
            delete cellules[x][y];
            cellules[x][y] = new LifeCell();
            cout << "Cellule Vivante placée à (" << x << ", " << y << ")" << endl;
        }
    }
}

void Grid::placePattern(int x, int y, const vector<vector<int>>& pattern) {
    for (int i = 0; i < pattern.size(); ++i) {
        for (int j = 0; j < pattern[i].size(); ++j) {
            if (x + i >= 0 && x + i < gridWidth && y + j >= 0 && y + j < gridHeight) {
                if (pattern[i][j] == 1) {
                    if (dynamic_cast<ObstacleCell*>(cellules[x + i][y + j]) == nullptr) {
                        cellules[x + i][y + j] = new LifeCell();
                    }
                } else {
                    if (dynamic_cast<ObstacleCell*>(cellules[x + i][y + j]) == nullptr) {
                        cellules[x + i][y + j] = new DeathCell();
                    }
                }
            }
        }
    }
}

int Grid::compterVoisinsVivants(int i, int j) {
    int nombre_voisin = 0;
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
            if (dx == 0 && dy == 0) continue;

            int nx = (i + dx + gridWidth) % gridWidth;
            int ny = (j + dy + gridHeight) % gridHeight;

            if (cellules[nx][ny] && cellules[nx][ny]->estVivante() == 1) {
                nombre_voisin++;
            }
        }
    }
    return nombre_voisin;
}

void Grid::update() {
    vector<vector<Cell*>> cellules_maj(gridWidth, vector<Cell*>(gridHeight, nullptr));
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            if (cellules[i][j]->estVivante() == 2) {
                cellules_maj[i][j] = new ObstacleCell();
            }
            if (cellules[i][j]->estVivante() == 1) {
                if (compterVoisinsVivants(i, j) == 2 || compterVoisinsVivants(i, j) == 3) {
                    cellules_maj[i][j] = new LifeCell();
                } else {
                    cellules_maj[i][j] = new DeathCell();
                }
            } else if (cellules[i][j]->estVivante() == 0) {
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

void Grid::renderGrid(sf::RenderWindow& window) {
    window.clear();
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f));

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (cellules[x][y] && cellules[x][y]->estVivante() == 1) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color::White);
                window.draw(cell);
            } else if (cellules[x][y] && cellules[x][y]->estVivante() == 2) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color::Red);
                window.draw(cell);
            }
        }
    }
    window.display();
}

void Grid::test_unitaire(){
    char caractere;
    cout << "Démarage test unitaire"<<endl;
    ifstream fichier("Grille_vide.txt");
    fichier.get(caractere);
    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (fichier.get(caractere)) {
                if (caractere == '0') {
                    cellules[x][y] = new DeathCell();
                } else if (caractere == '1') {
                    cellules[x][y] = new LifeCell();
                } else if (caractere == '2') {
                    cellules[x][y] = new ObstacleCell();
                } else {
                    cellules[x][y] = new DeathCell();
                }
            }
        }
    }
    fichier.close();   
}

void Grid::resutlat_test_unitaire(){
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            cout<<cellules[i][j]->estVivante();
     }
     cout<<"f"<<endl;
     }       
}