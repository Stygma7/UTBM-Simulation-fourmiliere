#include "FourmiOuvriere.h"
#include "Fourmi.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
FourmiOuvriere::FourmiOuvriere(Fourmiliere* col) :
    Fourmi(col, 50, 1, 2, 20)
{
    tourAvantEvol = rand() % 20 + 40;
}

FourmiOuvriere::FourmiOuvriere(Fourmiliere* col, int vie) :
    Fourmi(col, 50, 1, 2, 20)
{
    tourAvantEvol = rand() % 20 + 40;
    setVie(vie);
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
// met à jour la fourmi pour un tour
void FourmiOuvriere::update(){
    if (getVie() >= 0) {
        setVie(getVie() - getPerteVie());

        if (getVie() <= getSeuilRavitaillement()) {
            //conso Nourriture
            eat();
        }

        if (tourAvantEvol <= 0) {
            getColonie()->evolToGuerriere(this);
        }
        else {
            tourAvantEvol--;
        }
    }
}