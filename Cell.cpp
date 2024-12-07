#include "Cell.h"

int LifeCell::estVivante() const {
    return 1;
}

void LifeCell::setEtat(bool etat) {
    vivante = etat;
}


int DeathCell::estVivante() const {
    return 0;
}

void DeathCell::setEtat(bool etat) {

}


int ObstacleCell::estVivante() const {
    return 2;
}

void ObstacleCell::setEtat(bool etat) {

}
