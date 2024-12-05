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
    LifeCell();

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
