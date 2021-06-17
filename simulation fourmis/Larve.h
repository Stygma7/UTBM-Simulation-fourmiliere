#pragma once
#ifndef LARVE_H
#define LARVE_H

#include "Fourmi.h"
#include "Fourmiliere.h"

class Fourmiliere;

class Larve : public Fourmi
{
private:

    int tourAvantEvol;

public:
    // Constructeur
    Larve(Fourmiliere*);

    void update();
};

#endif