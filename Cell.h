#pragma once

class Cell {
public:
    virtual int estVivante() const = 0;
    virtual void setEtat(bool etat) = 0;
    virtual ~Cell() {}
};
class LifeCell : public Cell {
private:
    bool vivante;
public:
    LifeCell() : vivante(true) {}

    int estVivante() const  {
        return 1;
    }
    void setEtat(bool etat) override {
        vivante = etat;
    }

};

class DeathCell : public Cell {
public:
    int estVivante() const  {
        return 0;
    }

    void setEtat(bool etat) override {
        
    }
};

class ObstacleCell : public Cell {
public:
    int estVivante() const {
        return 2;
    }

    void setEtat(bool etat) override {
       
    }
};
