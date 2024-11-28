
class Cell {
public:
    virtual bool estVivante() const = 0;
    virtual void setEtat(bool etat) = 0;
    virtual ~Cell() {}
};

class LifeCell : Cell {
    
}

class DeathCell : Cell {
    
}