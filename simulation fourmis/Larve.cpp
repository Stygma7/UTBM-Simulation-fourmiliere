#include "Larve.h"
#include "Fourmi.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
Larve::Larve(Fourmiliere* col) {
    colonie = col;
    tourAvantEvol =  rand() %10 +25;
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
// met à jour la larve pour un tour
void Larve::update(){
    if (vie >= 0) {
        vie -= perteVie;

        if (vie <= seuilRavitaillement) {
            //conso Nourriture
            eat();
        }

        if (tourAvantEvol <= 0) {
            colonie->evolToOuvriere(this);
        } else {
            tourAvantEvol--;
        }
    }
}

// la larve se nourrit
void Larve::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}