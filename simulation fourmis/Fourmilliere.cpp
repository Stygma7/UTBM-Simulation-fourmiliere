#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "Fourmilliere.h"

using namespace std;

void affichageTxtColor3(Position p, string str, int color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = p.getX();
	dwPos.Y = p.getY() +1; // +1 à cause de la premiere ligne de texte
	SetConsoleCursorPosition(hcon, dwPos);
    SetConsoleTextAttribute(hcon, color);
    cout << str;
    SetConsoleTextAttribute(hcon, 15);
}

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
    for(FourmiGuerriere & fourmiG : listFourmisGuerrieres ) {
        fourmiG.update();
    }
    for(FourmiOuvriere & fourmiO : listFourmisOuvrieres ) {
        fourmiO.update();
        // affichageTxtColor3(Position(104,16 + cpt), "vie " + to_string(cpt) + " : " + to_string(fourmiO.getVie()) + " ", 15);
        // cpt++;
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

void Fourmilliere::addAntsDefault() {
    for (int i = 0; i < 30; i++)
    {
        listFourmisGuerrieres.push_back(FourmiGuerriere(this));
    }
    for (int i = 0; i < 5; i++)
    {
        listFourmisOuvrieres.push_back(FourmiOuvriere(this));
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