#include "FileManagement.h"
#include <fstream>

void FileManagement::writeToFile(const std::string &filename, const Grid &grid) {
    std::ofstream file(filename); // Création ou ouverture d'un fichier en mode écriture
    if (!file.is_open()) {
        std::cerr << "Impossible d'ouvrir le fichier : " << filename << std::endl; // pour les erreurs.
        exit(1);  // Sortie du programme en cas d'erreur
    }

    int gridWidth = grid.get_gridWidth();
    int gridHeight = grid.get_gridHeight();
    const auto &cellules = grid.getCells(); // Référence aux cellules de la grille

    // Écriture dans le fichier
    for (int i = 0; i < gridWidth; ++i) {
        for (int j = 0; j < gridHeight; ++j) {
            if (cellules[i][j] && cellules[i][j]->estVivante() == 1) {
                file << "1 "; // celulle vivante 
            } else if (cellules[i][j] && cellules[i][j]->estVivante() == 0) {
                file << "0 "; // morte
            } else if (cellules[i][j] && cellules[i][j]->estVivante() == 2) {
                file << "2 "; // obstacle
            }
        }
        file << std::endl; // passage a la ligne suivante.
    }
}

void FileManagement::deleteTxtFilesInDirectory(const std::string &directory) {
    try {
        for (const auto &entry : fs::directory_iterator(directory)) {
            if (entry.path().extension() == ".txt") { // Vérifie si le fichier a l'extension .txt
                fs::remove(entry.path()); // on le supprime.
            }
        }
        std::cout << "Tous les fichiers .txt ont été supprimés du dossier : " << directory << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Erreur lors de la suppression des fichiers : " << e.what() << std::endl; // message d'erreur explicant l'erreur grace a methode what().
    }
}
