#include "Larve.h"
#include "Fourmi.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
Larve::Larve(Fourmiliere* col) : 
    Fourmi(col, 50, 1, 1, 20) 
{
    tourAvantEvol =  rand() %10 +25;
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
// met à jour la larve pour un tour
void Larve::update(){
    if (getVie() >= 0) {
        setVie(getVie() - getPerteVie());

        if (getVie() <= getSeuilRavitaillement()) {
            //conso Nourriture
            eat();
        }

        if (tourAvantEvol <= 0) {
            getColonie()->evolToOuvriere(this);
        } else {
            tourAvantEvol--;
        }
    }
}