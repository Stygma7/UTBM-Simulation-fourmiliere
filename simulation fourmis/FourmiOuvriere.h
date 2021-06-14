#pragma once
#ifndef FOURMIO_H
#define FOURMIO_H

#include "Fourmi.h"
#include "Fourmiliere.h"
class Fourmiliere;

class FourmiOuvriere : public Fourmi
{
private:
    // pointeur sur la colonie de la fourmi
    Fourmiliere* colonie;

    int tourAvantEvol;

public:
    // Constructeur
    FourmiOuvriere(Fourmiliere*);
    FourmiOuvriere(Fourmiliere*, int);

    // deplacement de la fourmi
    void update();

    // Consommer de nourriture
    void eat();
};

#endif