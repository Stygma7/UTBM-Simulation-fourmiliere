#include "Reine.h"
#include <iostream>

Reine::Reine(Fourmilliere* col) {
    MAX_VIE = 80;
    vie = MAX_VIE;
    colonie = col;
    env = colonie->getEnv();
    consoNourriture = 5;
}

void Reine::update(){
    if (vie >= 0) {
        vie -= perteVie;

        if (vie <= seuilRavitaillement) {
            //conso Nourriture
            eat();
        }
        if ((cptCreation >= tempsCreation) && (colonie->getPop() < colonie->getPopMax()) ){
            Pondre();
            cptCreation = 0;
            tempsCreation = rand() %2 + 4;
        } else {
            cptCreation ++;
        }
    }
}

void Reine::Pondre() {
    colonie->addOeuf();
}

void Reine::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}