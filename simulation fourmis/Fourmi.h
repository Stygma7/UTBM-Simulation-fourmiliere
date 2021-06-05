#ifndef __FOURMI_H__
#define __FOURMI_H__

// #include "Environnement.h"
// class Environnement;
// #include "Fourmilliere.h"
// class Fourmilliere;

class Fourmi
{
protected:
    int MAX_VIE = 50;
    int vie = MAX_VIE;
    int seuilRavitaillement = 20;

    // pointeur sur l'environnement de la fourmi
    // Environnement* env;
    // pointeur sur la colonie de la fourmi
    // Fourmilliere* colonie;

    //nombre de points de vie perdue par une fourmi par tour
    int perteVie = 1;

    //quantité de nourriture consommée lors du ravitaillement
    int consoNourriture = 1;

public: 
    // void Fourmi::eat();
    // virtual void update();
    int getVie() {return vie;}
    // void updateVie();
    // void eat();
    void giveLife();
    bool isAlive();
};

#endif