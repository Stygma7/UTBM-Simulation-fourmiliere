#include "Fourmi.h"

bool Fourmi::isAlive() {
    if (vie > 0)
        return true;
    else
        return false;
}

// void Fourmi::updateVie(){
//     if (vie <= 0) {
//         //delete object
//     } else {
//         vie -= perteVie;
//     }
//     if (vie <= seuilRavitaillement) {
//         //conso Nourriture
//         eat();
//     }
// }

// void Fourmi::eat() {
//     if (colonie->getFood() >= consoNourriture) {
//         colonie->substractFood(consoNourriture);
//         giveLife();
//     }
// }

// void Fourmi::giveLife() {
//     vie = MAX_VIE;
// }