#pragma once

class Cell {
public:
    virtual bool estVivante() const = 0;
    virtual void setEtat(bool etat) = 0;
    virtual ~Cell() {}
};
class LifeCell : public Cell {
private:
    bool vivante;
public:
    LifeCell() : vivante(true) {}

    bool estVivante() const override {
        return vivante;
    }
    void setEtat(bool etat) override {
        vivante = etat;
    }

};

class DeathCell : public Cell {
public:
    bool estVivante() const override {
        return false;
    }

    void setEtat(bool etat) override {
        // Ne rien faire car une cellule morte ne peut pas devenir vivante.
    }
};

class CelluleObstacle : public Cell {
public:
    bool estVivante() const override {
        return true; // L'obstacle reste toujours "vivant" mais ne change jamais.
    }

    void setEtat(bool etat) override {
        // Ne rien faire car une cellule obstacle ne change pas.
    }
};
