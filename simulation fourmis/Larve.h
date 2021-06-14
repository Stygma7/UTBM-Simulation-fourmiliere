#pragma once
#ifndef LARVE_H
#define LARVE_H

#include "Fourmi.h"
#include "Fourmiliere.h"
class Fourmiliere;

class Larve : public Fourmi
{
private:
    // pointeur sur la colonie de la fourmi
    Fourmiliere* colonie;

    int tourAvantEvol = 30;

public:
    // Constructeur
    Larve(Fourmiliere*);

    void update();
    void eat();
};

#endif