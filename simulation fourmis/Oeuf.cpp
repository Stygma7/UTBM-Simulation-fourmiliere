#include "Oeuf.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
Oeuf::Oeuf(Fourmilliere* col) {
    colonie = col;
    env = colonie->getEnv();
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
void Oeuf::update(){

    if (tourAvantEvol <= 0) {
        colonie->evolToLarve(this);
    } else {
        tourAvantEvol--;
    }
}