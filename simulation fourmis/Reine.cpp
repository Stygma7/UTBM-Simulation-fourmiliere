#include "Reine.h"

Reine::Reine(Fourmiliere* col) {
    MAX_VIE = 80;
    vie = MAX_VIE;
    colonie = col;
    consoNourriture = 5;
}

// met à jour la reine pour un tour
void Reine::update(){
    if (vie >= 0) {
        vie -= perteVie;

        if (vie <= seuilRavitaillement) {
            //conso Nourriture
            eat();
        }
        // la reine arrête de pondre si la colonie est au max de population
        if ((cptCreation >= tempsCreation) && (colonie->getPop() < colonie->getPopMax()) ){
            Pondre();
            cptCreation = 0;
            // pond tous les 4 à 6 tours
            tempsCreation = rand() %2 + 4;
        } else {
            cptCreation ++;
        }
    }
}

// pond un oeuf
void Reine::Pondre() {
    colonie->addOeuf();
}

// la reine se nourrit
void Reine::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}