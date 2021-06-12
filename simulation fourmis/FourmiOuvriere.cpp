#include "FourmiOuvriere.h"
#include "Fourmi.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
FourmiOuvriere::FourmiOuvriere(Fourmilliere* col) {
    colonie = col;
    env = colonie->getEnv();
    consoNourriture = 2;
    tourAvantEvol = rand() % 20 + 40;
}

FourmiOuvriere::FourmiOuvriere(Fourmilliere* col, int vie_) {
    colonie = col;
    env = colonie->getEnv();
    consoNourriture = 2;
    tourAvantEvol = rand() % 20 + 40;
    vie = vie_;
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
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

void FourmiOuvriere::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}

// void FourmiOuvriere::giveLife() {
//     vie = MAX_VIE;
// }