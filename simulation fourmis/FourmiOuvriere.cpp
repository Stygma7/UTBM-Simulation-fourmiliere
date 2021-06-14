#include "FourmiOuvriere.h"
#include "Fourmi.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
FourmiOuvriere::FourmiOuvriere(Fourmiliere* col) {
    colonie = col;
    consoNourriture = 2;
    tourAvantEvol = rand() % 20 + 40;
}

FourmiOuvriere::FourmiOuvriere(Fourmiliere* col, int vie_) {
    colonie = col;
    consoNourriture = 2;
    tourAvantEvol = rand() % 20 + 40;
    vie = vie_;
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
// met à jour la fourmi pour un tour
void FourmiOuvriere::update(){
    if (vie >= 0) {
        vie -= perteVie;

        if (vie <= seuilRavitaillement) {
            //conso Nourriture
            eat();
        }

        if (tourAvantEvol <= 0) {
            colonie->evolToGuerriere(this);
        } else {
            tourAvantEvol--;
        }
    }
}

// la fourmi se nourrit
void FourmiOuvriere::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}