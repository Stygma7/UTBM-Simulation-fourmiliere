#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "Fourmilliere.h"

using namespace std;

Fourmilliere::Fourmilliere(Environnement* env, Position position) {
    this->env = env;
    pos = position;
    addAnts();
}

// Fourmilliere::Fourmilliere(Environnement* env) {
//     this->env = env;
//     pos = Position(env->getColonne()/2, env->getLigne()/2);
//     addAnts();
// }

void Fourmilliere::update() {
    for(FourmiGuerriere & fourmiG : listFourmisGuerrieres ) {
        fourmiG.update();
    }
}

void Fourmilliere::EraseAnts() {
    for(FourmiGuerriere & fourmiG : listFourmisGuerrieres ) {
        if (!(fourmiG.getLastPos() == pos))
            fourmiG.eraseLastPos();
    }
}

void Fourmilliere::DispAnts() {
    for (FourmiGuerriere& fourmiG : listFourmisGuerrieres) {
        if (!(fourmiG.getPos() == pos))
            fourmiG.display();
    }
}

void Fourmilliere::addAnts() {
    for (int i = 0; i < 10; i++)
    {
        listFourmisGuerrieres.push_back(FourmiGuerriere(this));
    }
}

void Fourmilliere::addFood(int nb) {
    if (food + nb <= foodMax) {
        food += nb;
    }
}

bool Fourmilliere::isFoodStockFull() {
    if (food >= foodMax)
        return true;
    else
        return false;
}