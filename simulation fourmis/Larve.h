#pragma once
// #ifndef FOURMIG_H
// #define FOURMIG_H

#include "Fourmi.h"
#include "Fourmilliere.h"
class Fourmilliere;
// #include "Environnement.h"
// class Environnement;

class Larve : public Fourmi
{
private:
    // pointeur sur l'environnement de la fourmi
    // Environnement* env;
    // pointeur sur la colonie de la fourmi
    Fourmilliere* colonie;

    // nombre de points de vie perdue par une fourmi par tour
    // int perteVie = 1;
    // quantité de nourriture consommée lors du ravitaillement
    // int consoNourriture = 1;
    int tourAvantEvol = 30;

public:
    // Constructeur
    Larve(Fourmilliere*);

    // deplacement de la fourmi
    void update();


    // Consommer de nourriture
    void eat();

    // Complète la vie de la fourmi
    // void giveLife();
};

// #endif