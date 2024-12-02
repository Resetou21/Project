#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;
class FileManagement {
public:
    // Fonction pour écrire dans un fichier
    static void writeToFile(const string &filename, const string &content) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Impossible d'ouvrir le fichier pour écrire : " << filename << std::endl;
            exit(1);
        }
        file << content;
        file.close();
    }

    // Fonction pour supprimer tous les fichiers .txt dans un dossier donné
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
