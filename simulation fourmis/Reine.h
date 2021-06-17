#ifndef REINE_H
#define REINE_H

#include "Fourmi.h"
#include "Fourmiliere.h"

class Fourmi;
class Fourmiliere;

class Reine : public Fourmi
{
private:

    int tempsCreation = 5;
    int cptCreation = 0;

public:
    // Constructeur
    Reine(Fourmiliere*);

    // deplacement de la fourmi
    void update();
    // ponds un oeuf
    void Pondre();
};

#endif