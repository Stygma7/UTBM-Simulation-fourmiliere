#include "Reine.h"

Reine::Reine(Fourmiliere* col) :
    Fourmi(col, 80, 1, 5, 20)
{
}

// met à jour la reine pour un tour
void Reine::update(){
    if (getVie() >= 0) {
        setVie(getVie() - getPerteVie());

        if (getVie() <= getSeuilRavitaillement()) {
            //conso Nourriture
            eat();
        }
        // la reine arrête de pondre si la colonie est au max de population
        if ((cptCreation >= tempsCreation) && (getColonie()->getPop() < getColonie()->getPopMax()) ){
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
    getColonie()->addOeuf();
}