#pragma once

class Cell {
public:
    virtual int estVivante() const = 0;  // Renvoie l'état de la cellule (vivante ou morte)
    virtual void setEtat(bool etat) = 0;  // Fonction pour changer l'état de la cellule (vivante ou morte)
    virtual ~Cell() {} // destructeur 
};
 // heritage de cellule vivante. Cellule vivante est un "enfant" de Cellule.
class LifeCell : public Cell {
private:
    bool vivante; // vivant ou mort 
public:
    int estVivante() const override;
    void setEtat(bool etat) override;
};

class DeathCell : public Cell {
public:
    int estVivante() const override;
    void setEtat(bool etat) override;
};

class ObstacleCell : public Cell {
public:
    int estVivante() const override;
    void setEtat(bool etat) override;
};
