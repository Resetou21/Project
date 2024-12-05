#include "FileManagement.h"
#include <fstream>

void FileManagement::writeToFile(const std::string &filename, const Grid &grid) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl;
        exit(1);
    }

    int gridWidth = grid.get_gridWidth();
    int gridHeight = grid.get_gridHeight();
    const auto &cellules = grid.getCells();

    // Écriture dans le fichier
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            if (cellules[i][j] && cellules[i][j]->estVivante() == 1) {
                file << "1 ";
            } else if (cellules[i][j] && cellules[i][j]->estVivante() == 0) {
                file << "0 ";
            } else if (cellules[i][j] && cellules[i][j]->estVivante() == 2) {
                file << "2 ";
            }
        }
        file << std::endl;
    }
}

void FileManagement::deleteTxtFilesInDirectory(const std::string &directory) {
    try {
        for (const auto &entry : fs::directory_iterator(directory)) {
            if (entry.path().extension() == ".txt") {
                fs::remove(entry.path());
            }
        }
        std::cout << "Tous les fichiers .txt ont été supprimés du dossier : " << directory << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la suppression des fichiers : " << e.what() << std::endl;
    }
}
