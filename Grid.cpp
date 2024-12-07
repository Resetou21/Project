#include "Grid.h"
#include "Cell.h"

// Constructeur de Grid
Grid::Grid() : cellules(gridWidth, vector<Cell*>(gridHeight, nullptr)) {}

// destructeur
Grid::~Grid() {
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            delete cellules[i][j];
        }
    }
}
// recupere la largeur de la grille
int Grid::get_gridWidth() const {
    return gridWidth;
}
// recupere l'états de la cellule.
int Grid::get_status_cell(int x,int y){
    return cellules[x][y]->estVivante();
}

int Grid::get_cellSize() const {
    return cellSize;
}

int Grid::get_gridHeight() const {
    return gridHeight;
}
// Retourne la grille de cellules (type Cell*)
const std::vector<std::vector<Cell*>>& Grid::getCells() const {
    return cellules;
}
// Fonction pour initialiser la grille de manière aléatoire ou à partir d'un fichier
void Grid::initializeGrid() {
    srand(time(0)); // Initialise le générateur de nombres aléatoires avec l'heure actuelle
    char type;
    cout << "|R|andom ou |G|rille" << endl;
    cin >> type;
    if (type == 'R') {   // Si l'utilisateur choisit 'R', la grille est remplie aléatoirement
        for (int x = 0; x < gridWidth; ++x) {
            for (int y = 0; y < gridHeight; ++y) {
                int random = rand();
                if (random % 101 == 0) {
                    cellules[x][y] = new ObstacleCell(); //  // Place un obstacle avec une faible probabilité 
                } else if (random % 5 == 0) {
                    cellules[x][y] = new LifeCell();
                } else {
                    cellules[x][y] = new DeathCell();
                }
            }
        }
    } else if (type == 'G') { // Si l'utilisateur choisit 'G', on charge la grille à partir d'un fichier que l'utilisateur fournit.
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
                        cellules[x][y] = new DeathCell(); // si le caractere est inconnu par exemple '3' qui n'existe pas.
                    }
                }
            }
        }
        fichier.close(); // ferme le fichier
    }
}


// Place un obstacle à la position (x, y) si ce n'est pas déjà un obstacle
    void Grid::placeObstacle(int x, int y) {
        if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
            if (!dynamic_cast<ObstacleCell*>(cellules[x][y])) { //  Si la cellule n'est pas un obstacle elle en devient un.
                cellules[x][y] = new ObstacleCell();
                cout << "Cellule obstacle placée à (" << x << ", " << y << ")" << endl;
            }
        }
    }
// place des cellules vivante sur la grille.
void Grid::placeLifeCell(int x, int y) {
    if (x >= 0 && x < gridWidth && y >= 0 && y < gridHeight) {
        if (!dynamic_cast<LifeCell*>(cellules[x][y])) {
            delete cellules[x][y];
            cellules[x][y] = new LifeCell();
            cout << "Cellule Vivante placée à (" << x << ", " << y << ")" << endl;
        }
    }
}
// permet d'implementer differents partern du jeu de la vie qu'on puisse les utiliser comme un glider qu'on va definir.
void Grid::placePattern(int x, int y, const vector<vector<int>>& pattern) {
    for (int i = 0; i < pattern.size(); ++i) { 
        for (int j = 0; j < pattern[i].size(); ++j) { //colonne
            if (x + i >= 0 && x + i < gridWidth && y + j >= 0 && y + j < gridHeight) { // pour ne pas sortir de la grille
                if (pattern[i][j] == 1) {
                    if (dynamic_cast<ObstacleCell*>(cellules[x + i][y + j]) == nullptr) { // si ce n'est pas un obstacle
                        cellules[x + i][y + j] = new LifeCell(); // la cellule devient vivante
                    }
                } else { // si la cellule doit devenir morte
                    if (dynamic_cast<ObstacleCell*>(cellules[x + i][y + j]) == nullptr) { // est que ce n'est pas un obstacle
                        cellules[x + i][y + j] = new DeathCell(); // la cellule devient morte
                    }
                }
            }
        }
    }
}

int Grid::compterVoisinsVivants(int i, int j) {
    int nombre_voisin = 0;
      // dx et dy vont de -1 à +1 pour inclure tous les voisins (diagonales comprises)
    for (int dx = -1; dx <= 1; ++dx) {
        for (int dy = -1; dy <= 1; ++dy) {
             // On ignore la cellule elle-même, donc on saute le cas où dx = 0 et dy = 0
            if (dx == 0 && dy == 0) continue;

           // La grille torrique fait en sorte que les bords se "rejoignent" (ex : le bord droit rejoint le bord gauche)
            int nx = (i + dx + gridWidth) % gridWidth; 
            int ny = (j + dy + gridHeight) % gridHeight;
            // si la cellule voisine existe et est vivante 
            if (cellules[nx][ny] && cellules[nx][ny]->estVivante() == 1) {
                nombre_voisin++;
            }
        }
    }
    return nombre_voisin;
}

void Grid::update() {
    //Nouvelle grille temporaire pour stocker les états mis à jour des cellules et éviter les conflits.
    vector<vector<Cell*>> cellules_maj(gridWidth, vector<Cell*>(gridHeight, nullptr));
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            if (cellules[i][j]->estVivante() == 2) { // si la cellule est un obstacle 
                cellules_maj[i][j] = new ObstacleCell();
            }
            if (cellules[i][j]->estVivante() == 1) { // si la cellule est vivante 
                if (compterVoisinsVivants(i, j) == 2 || compterVoisinsVivants(i, j) == 3) { // et qu'elle a 2 ou 3 voisins
                    cellules_maj[i][j] = new LifeCell(); //reste vivante
                } else {
                    cellules_maj[i][j] = new DeathCell(); //meurs
                }
            } else if (cellules[i][j]->estVivante() == 0) {
                if (compterVoisinsVivants(i, j) == 3) { // si la cellule à 3 voisins vivant 
                    cellules_maj[i][j] = new LifeCell();  //elle devient vivante (regle du brouillage)
                } else {
                    cellules_maj[i][j] = new DeathCell(); // Reste morte
                }
            }
        }
    }
    // Cela supprime les anciennes cellules et remplace chaque cellule avec son nouvel état
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            delete cellules[i][j];
            cellules[i][j] = cellules_maj[i][j];
        }
    }
}

void Grid::renderGrid(sf::RenderWindow& window) {
    window.clear(); //Efface tout le contenu précédent de la fenêtre.
    sf::RectangleShape cell(sf::Vector2f(cellSize - 1.0f, cellSize - 1.0f)); // Crée une forme de cellule de taille ajustée

    for (int x = 0; x < gridWidth; ++x) {
        for (int y = 0; y < gridHeight; ++y) {
            if (cellules[x][y] && cellules[x][y]->estVivante() == 1) {
                cell.setPosition(x * cellSize, y * cellSize); // definit la position de la cellule
                cell.setFillColor(sf::Color::White); // la met blanche si elle est vivante
                window.draw(cell); // dessine la cellule dans la fenetre
            } else if (cellules[x][y] && cellules[x][y]->estVivante() == 2) {
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color::Red);
                window.draw(cell);
            }
        }
    }
    window.display(); // Affiche le contenu de la fenêtre mise à jour
}
string Grid::test(int x, int y,int nombre_voisin,int etat_precedent){    // test unitaire
    if (cellules[x][y]->estVivante()==2){ 
        return "C'est un obstacle o";
    }
    else{
        if (etat_precedent = 0){
            if (cellules[x][y]->estVivante()==1){
                if (nombre_voisin == 3){
                    return "Test validé v";
                }
                else{
                    return "Test non validé v";
                }
            }
            else if (cellules[x][y]->estVivante()==0){            
                if (nombre_voisin != 3){
                    return "Test validé m";
                }
                else{
                    return "Test non validé m";
                }
            
            }
        }
        else if (etat_precedent = 1){
            if (cellules[x][y]->estVivante()==1){
                if (nombre_voisin == 3 ||nombre_voisin == 2){
                    return "Test validé v";
                }
                else{
                    return "Test non validé v";
                }
            }
            else if (cellules[x][y]->estVivante()==0){            
                if (nombre_voisin != 3 || nombre_voisin != 2){
                    return "Test validé m";
                }
                else{
                    return "Test non validé m";
                }
            
            }
        
        }
    }
    return "Erreur inconnue"; // Par défaut pour éviter un chemin non couvert
}
