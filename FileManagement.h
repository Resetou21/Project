#pragma once

#include <string>
#include <iostream>
#include <filesystem>
#include "Grid.h"

namespace fs = std::filesystem;

class FileManagement {
public:
    // Méthode pour écrire les fichiers correspondant à chaque itération
    static void writeToFile(const std::string &filename, const Grid &grid);

    // Méthode pour supprimer tous les fichiers .txt d'un répertoire
    static void deleteTxtFilesInDirectory(const std::string &directory);
};
