#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <stack>
#include "Grid.h"
namespace fs = std::filesystem;
using namespace std;
class FileManagement {
public:
    // méthode pour écrire les fichiers corespondant a chaque ittération
   static void writeToFile(const std::string &filename, const Grid &grid) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
            exit(1);
        }

        int gridWidth = grid.get_gridWidth();
        int gridHeight = grid.get_gridHeight();
        const auto &cellules = grid.getCells(); 
        //ecriture dans le fichier
        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                if (cellules[i][j] && cellules[i][j]->estVivante()==1) {
                    file << "1 ";
                } 
                else if(cellules[i][j] && cellules[i][j]->estVivante()==0){
                    file << "0 ";
                }
                else if(cellules[i][j] && cellules[i][j]->estVivante()==2){
                    file << "2 ";
                }
            }
            file << std::endl;
        }
    }
    //méthode pour supprimer tous les fichier ittération sauf le dernier quand on ferme la fenêtre SFML
    static void deleteTxtFilesInDirectory(const string &directory) {
        try {
            for (const auto &entry : fs::directory_iterator(directory)) {
                if (entry.path().extension() == ".txt") {
                    fs::remove(entry.path());
                }
            }
            cout << "Tous les fichiers .txt ont été supprimés du dossier : " << directory << endl;
        } catch (const exception &e) {
            cerr << "Erreur lors de la suppression des fichiers : " << e.what() << endl;
        }
    }
};
