// #pragma once
#ifndef REINE_H
#define REINE_H

#include "Fourmi.h"
class Fourmi;
#include "Fourmilliere.h"
class Fourmilliere;
#include "Environnement.h"
class Environnement;

class Reine : public Fourmi
{
private:

    // int MAX_VIE = 80;
    // pointeur sur l'environnement de la fourmi
    Environnement* env;
    // pointeur sur la colonie de la fourmi
    Fourmilliere* colonie;

    int tempsCreation = 5;
    int cptCreation = 0;

    // nombre de points de vie perdue par une fourmi par tour
    // int perteVie = 1;

    // quantité de nourriture consommée lors du ravitaillement
    // int consoNourriture = 1;

public:
    // Constructeur
    // Reine();
    Reine(Fourmilliere*);

    // ~Reine();

    // deplacement de la fourmi
    void update();


    // Consommer de nourriture
    void eat();

    // ponds un oeuf
    void Pondre();
};

#endif