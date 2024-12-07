/*                  
██╗░░░░░ ██╗ ██████╗░ ███████╗   ██████╗░ ███████╗ ░█████╗░ ██████╗░ ███╗░░░███╗ ███████╗   
██║░░░░░ ██║ ██╔══██╗ ██╔════╝   ██╔══██╗ ██╔════╝ ██╔══██╗ ██╔══██╗ ████╗░████║ ██╔════╝   
██║░░░░░ ██║ ██████╔╝ █████╗░░   ██████╔╝ █████╗░░ ███████║ ██║░░██║ ██╔████╔██║ █████╗░░   
██║░░░░░ ██║ ██╔══██╗ ██╔══╝░░   ██╔══██╗ ██╔══╝░░ ██╔══██║ ██║░░██║ ██║╚██╔╝██║ ██╔══╝░░   
███████╗ ██║ ██║░░██║ ███████╗   ██║░░██║ ███████╗ ██║░░██║ ██████╔╝ ██║░╚═╝░██║ ███████╗   
╚══════╝ ╚═╝ ╚═╝░░╚═╝ ╚══════╝   ╚═╝░░╚═╝ ╚══════╝ ╚═╝░░╚═╝ ╚═════╝░ ╚═╝░░░░░╚═╝ ╚══════╝
*/

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
    //  motifs prédéfinis du jeu de la vie.
    vector<vector<int>> loaf = {
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {0, 1, 0, 1},
    {0, 1, 0, 0}
    };
    vector<vector<int>> glider = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1}
    };
    vector<vector<int>> toad = {
        {0, 1, 1, 0},
        {1, 1, 1, 0},
        {0, 0, 0, 0}
    };

    vector<vector<int>> beacon = {
        {1, 1, 0, 0},
        {1, 1, 0, 0},
        {0, 0, 1, 1},
        {0, 0, 1, 1}
    };
    char mode_console;
    int maxiteration;
    int iteration = 0;
    float modification = 100;
    int test_nombre_voisin;
    int etat_precedent;
    cout<<"Mode |C|onsole ou |G|raphique ?";
    cin>>mode_console;
    cout<<"Entrez le nombre d'iteration"<<endl;
    cin>> maxiteration;
    bool isPaused = false; 
    Grid grid;
    sf::RenderWindow window(sf::VideoMode(grid.get_gridWidth() * grid.get_cellSize(), grid.get_gridHeight() * grid.get_cellSize()), "Game of Life");
    grid.initializeGrid(mode_console);
    
     // Gestion des fichiers de sortie
    string outputFolder = "output";
    if (!filesystem::exists(outputFolder)) {
        filesystem::create_directory(outputFolder);
    }

    while (window.isOpen()) {
        sf::Event event; 
        while (window.pollEvent(event)) {  //permet de récupérer les événements générés par l'utilisateur ou le système
                     sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                     int X = mousePos.x / grid.get_cellSize();
                     int Y = mousePos.y / grid.get_cellSize();
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
                    grid.placeObstacle(X, Y); 
                }
                if  (event.key.code == sf::Keyboard::V){ 
                    grid.placeLifeCell(X, Y); 
                }
                if (event.key.code == sf::Keyboard::I){
                    cout << "Modification des paramètres" << endl; 
                    cin>> modification;
                }
                if (event.key.code == sf::Keyboard::Numpad1){
                    grid.placePattern(X,Y,loaf);
                }
                if (event.key.code == sf::Keyboard::Numpad2){
                    grid.placePattern(X,Y,toad);
                }
                if (event.key.code == sf::Keyboard::Numpad3){
                    grid.placePattern(X,Y,beacon);
                }
            
         }
            
            if (event.type == sf::Event::MouseButtonPressed) {
                    cout << "Glidder implémenté " << endl;
                    grid.placePattern(X, Y, glider);
            }

        } // mis a jour de la grille 
        if (!isPaused && iteration < maxiteration) {
            etat_precedent = grid.get_status_cell(0,0);  // donne l'état de la cellulue mort ou vivante
            test_nombre_voisin = grid.compterVoisinsVivants(0,0);  // pour le test unitaire sur une cellule précise.
            grid.update();
              
            if (mode_console=='C'){
                cout<<grid.test(0,0,test_nombre_voisin,etat_precedent)<<endl;
                FileManagement::writeToFile(outputFolder + "/iteration_" + to_string(iteration) + ".txt", grid);}  // ecrit dans des nouveaux fichier l'état de la grille
            iteration++;
        }

 
        grid.renderGrid(window);

        sf::sleep(sf::milliseconds(modification)); //temporisation en miliseconde de la grille.
        
        }
        
        if (iteration >= maxiteration) {
             cout << "Simulation terminée après " << maxiteration << " itérations." << endl;
        }
}