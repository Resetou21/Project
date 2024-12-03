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
   static void writeToFile(const std::string &filename, const Grid &grid) {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
            exit(1);
        }

        int gridWidth = grid.get_gridWidth();
        int gridHeight = grid.get_gridHeight();
        const auto &cellules = grid.getCells(); 

        for (int i = 0; i < gridWidth; ++i) {
            for (int j = 0; j < gridHeight; ++j) {
                if (cellules[i][j] && cellules[i][j]->estVivante()) {
                    file << "1 ";
                } else {
                    file << "0 ";
                }
            }
            file << std::endl;
        }
    }



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
