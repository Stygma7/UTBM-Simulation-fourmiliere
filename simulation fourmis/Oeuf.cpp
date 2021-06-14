#include "Oeuf.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
Oeuf::Oeuf(Fourmiliere* col) {
    colonie = col;
    tourAvantEvol =  rand() %10 +25;
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
// met à jour l'oeuf pour un tour
void Oeuf::update(){

    if (tourAvantEvol <= 0) {
        colonie->evolToLarve(this);
    } else {
        tourAvantEvol--;
    }
}