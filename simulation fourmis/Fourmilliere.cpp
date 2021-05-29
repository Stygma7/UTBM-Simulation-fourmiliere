#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "Fourmilliere.h"

using namespace std;

Fourmilliere::Fourmilliere(Environnement* env, Position position) {
    this->env = env;
    pos = position;
    addAntsDefault();
}

// Fourmilliere::Fourmilliere(Environnement* env) {
//     this->env = env;
//     pos = Position(env->getColonne()/2, env->getLigne()/2);
//     addAnts();
// }

void Fourmilliere::update() {
    // int cpt = 0;
    for(FourmiGuerriere* & fourmiG : listFourmisGuerrieres ) {
        fourmiG->update();
    }

    for(int i=0; i<listFourmisOuvrieres.size(); i++) {
        if (listFourmisOuvrieres[i]->isAlive()) {
            listFourmisOuvrieres[i]->update();
        } else {
            delete listFourmisOuvrieres[i];
            listFourmisOuvrieres.erase(listFourmisOuvrieres.begin() +i);
        }

    }
}

void Fourmilliere::EraseAnts() {
    for(FourmiGuerriere* & fourmiG : listFourmisGuerrieres ) {
        if (!(fourmiG->getLastPos() == pos))
            fourmiG->eraseLastPos();
    }
}

void Fourmilliere::DispAnts() {
    for (FourmiGuerriere* & fourmiG : listFourmisGuerrieres) {
        if (!(fourmiG->getPos() == pos))
            fourmiG->display();
    }
}

void Fourmilliere::addAntsDefault() {
    addFourmisGuerrieres(1);
    addFourmisOuvrieres(5);
}

void Fourmilliere::addFourmisGuerrieres(int nb) {
    for (int i = 0; i < nb; i++) {
        listFourmisGuerrieres.push_back(new FourmiGuerriere(this));
    }
}

void Fourmilliere::addFourmisOuvrieres(int nb) {
    for (int i = 0; i < nb; i++) {
        listFourmisOuvrieres.push_back(new FourmiOuvriere(this));
    }
}

void Fourmilliere::addFood(int nb) {
    if (food + nb <= foodMax) {
        food += nb;
    }
}

void Fourmilliere::substractFood(int nb) {
    if (food >= 0) {
        food -= nb;
    }
}

bool Fourmilliere::isFoodStockFull() {
    if (food >= foodMax)
        return true;
    else
        return false;
}

bool Fourmilliere::isFoodStockEmpty() {
    if (food <= 0)
        return true;
    else
        return false;
}