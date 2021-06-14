#ifndef REINE_H
#define REINE_H

#include "Fourmi.h"
class Fourmi;
#include "Fourmiliere.h"
class Fourmiliere;

class Reine : public Fourmi
{
private:
    // pointeur sur la colonie de la fourmi
    Fourmiliere* colonie;

    int tempsCreation = 5;
    int cptCreation = 0;

public:
    // Constructeur
    Reine(Fourmiliere*);

    // deplacement de la fourmi
    void update();
    // Consommer de nourriture
    void eat();
    // ponds un oeuf
    void Pondre();
};

#endif