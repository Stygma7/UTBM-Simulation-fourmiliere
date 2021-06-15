#pragma once
#ifndef FOURMIO_H
#define FOURMIO_H

#include "Fourmi.h"
#include "Fourmiliere.h"
class Fourmiliere;

class FourmiOuvriere : public Fourmi
{
private:

    int tourAvantEvol;

public:
    // Constructeur
    FourmiOuvriere(Fourmiliere*);
    FourmiOuvriere(Fourmiliere*, int);

    // deplacement de la fourmi
    void update();
};

#endif