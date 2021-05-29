#pragma once
// #include "Environnement.h"
// class Environnement;
// #include "Fourmilliere.h"
// class Fourmilliere;

class Fourmi
{
protected:
    const int MAX_VIE = 100;
    int vie = MAX_VIE;
    int seuilRavitaillement = 20;

    // pointeur sur l'environnement de la fourmi
    // Environnement* env;
    // pointeur sur la colonie de la fourmi
    // Fourmilliere* colonie;

    //nombre de points de vie perdue par une fourmi par tour
    // int perteVie = 1;

    //quantité de nourriture consommée lors du ravitaillement
    // int consoNourriture = 3;

public: 
    // void Fourmi::eat();
    // virtual void update();
    int getVie() {return vie;}
    // void updateVie();
    // void eat() ;
    // void giveLife();
    bool isAlive();
};