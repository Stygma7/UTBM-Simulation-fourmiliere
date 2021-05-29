#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "caseType.h"
#include "FourmiGuerriere.h"
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
        //ajout vie
    }
}

void FourmiOuvriere::eat() {
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}

void FourmiOuvriere::giveLife() {
    vie = maxVie;
}