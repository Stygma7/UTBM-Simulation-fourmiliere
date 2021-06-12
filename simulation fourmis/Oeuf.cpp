#include "Oeuf.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
Oeuf::Oeuf(Fourmilliere* col) {
    colonie = col;
    // env = colonie->getEnv();
    tourAvantEvol =  rand() %10 +25;
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
void Oeuf::update(){

    if (tourAvantEvol <= 0) {
        colonie->evolToLarve(this);
    } else {
        tourAvantEvol--;
    }
}