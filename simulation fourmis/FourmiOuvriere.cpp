#include "FourmiOuvriere.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
FourmiOuvriere::FourmiOuvriere(Fourmilliere* col) {
    colonie = col;
    env = colonie->getEnv();
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
void FourmiOuvriere::update(){
    if (vie <= 0) {
        //delete object
    } else {
        vie -= perteVie;
    }
    if (vie <= seuilRavitaillement) {
        //conso Nourriture
        eat();
    }
    // updateVie();
}

void FourmiOuvriere::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}

void FourmiOuvriere::giveLife() {
    vie = MAX_VIE;
}