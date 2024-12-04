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
    Grid grille_test;
    grille_test.test_unitaire();
    grille_test.update();
    grille_test.resutlat_test_unitaire();

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

    int maxiteration;
    int iteration = 0;
    float ecart = 100;
    cout<<"Entrez le nombre d'iteration"<<endl;
    cin>> maxiteration;
    bool isPaused = false; 
    Grid grid;
    
    sf::RenderWindow window(sf::VideoMode(grid.get_gridWidth() * grid.get_cellSize(), grid.get_gridHeight() * grid.get_cellSize()), "Game of Life");
    grid.initializeGrid();

    string outputFolder = "output";
    if (!filesystem::exists(outputFolder)) {
        filesystem::create_directory(outputFolder);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
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
                    cin>> ecart;
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

        }
        if (!isPaused && iteration < maxiteration) {
            grid.update();  
            FileManagement::writeToFile(outputFolder + "/iteration_" + to_string(iteration) + ".txt", grid);
            iteration++;
        }

 
        grid.renderGrid(window);

        sf::sleep(sf::milliseconds(ecart));
        
        }
        
        if (iteration >= maxiteration) {
             cout << "Simulation terminée après " << maxiteration << " itérations." << endl;
        }
    return 0;
}