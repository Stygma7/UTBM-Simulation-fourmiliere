#include "FourmiGuerriere.h"
#include <iostream>

using namespace std;

FourmiGuerriere::FourmiGuerriere(Environnement& env) {
    posx = env.getLigne() / 2;
    posy = env.getColonne() / 2;
    cout << posx;
}

// void FourmiGuerriere::move() {
//     posx += 1;
//     posy += 1;
// }

