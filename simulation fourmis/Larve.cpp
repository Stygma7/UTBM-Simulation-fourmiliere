#include "Larve.h"
#include "Fourmi.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
Larve::Larve(Fourmilliere* col) {
    colonie = col;
    env = colonie->getEnv();
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
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

void Larve::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}

// void FourmiOuvriere::giveLife() {
//     vie = MAX_VIE;
// }