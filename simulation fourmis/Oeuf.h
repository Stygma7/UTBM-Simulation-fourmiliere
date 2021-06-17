#pragma once
#ifndef OEUF_H
#define OEUF_H

#include "Fourmiliere.h"

class Fourmiliere;

class Oeuf
{
private:
    // pointeur sur la colonie de la fourmi
    Fourmiliere* colonie;

    int tourAvantEvol = 30;

public:
    // Constructeur
    Oeuf(Fourmiliere*);

    // deplacement de la fourmi
    void update();

    // Complète la vie de la fourmi
    // void giveLife();
};

#endif