#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "Fourmilliere.h"
#include "FourmiOuvriere.h"

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

Fourmilliere::~Fourmilliere() {
    delete reine;
	for (FourmiGuerriere* & fourmi : listFourmisGuerrieres) {
		delete(fourmi);
	}
	for (FourmiOuvriere* & fourmi : listFourmisOuvrieres) {
		delete(fourmi);
	}
}

// Fourmilliere::Fourmilliere(Environnement* env) {
//     this->env = env;
//     pos = Position(env->getColonne()/2, env->getLigne()/2);
//     addAnts();
// }

void Fourmilliere::update() {
    // for(FourmiGuerriere* & fourmiG : listFourmisGuerrieres ) {
    //     fourmiG->update();
    // }

    if (reine != nullptr) {
        if (reine->isAlive()) {
            reine->update();
        } else {
            delete reine;
            reine = nullptr;
        }
    }
    
    for(int i=0; i<listOeufs.size(); i++) {
        listOeufs[i]->update();
    }

    for(int i=0; i<listLarves.size(); i++) {

        if (listLarves[i]->isAlive()) {
            listLarves[i]->update();
        } else {
            delete listLarves[i];
            listLarves.erase(listLarves.begin() +i);
            i--;
        }
    }

    for(int i=0; i<listFourmisOuvrieres.size(); i++) {
        // affichageTxtColor3(Position(104,19+i), to_string(i) + " " + to_string(listFourmisOuvrieres[i]->getVie()) + " ", 15);

        if (listFourmisOuvrieres[i]->isAlive()) {
            listFourmisOuvrieres[i]->update();
        } else {
            delete listFourmisOuvrieres[i];
            listFourmisOuvrieres.erase(listFourmisOuvrieres.begin() +i);
            i--;
        }
    }

    for(int i=0; i<listFourmisGuerrieres.size(); i++) {
        // affichageTxtColor3(Position(104,19+i), to_string(i) + " " + to_string(listFourmisOuvrieres[i]->getVie()) + " ", 15);

        if (listFourmisGuerrieres[i]->isAlive()) {
            listFourmisGuerrieres[i]->update();
        } else {
            delete listFourmisGuerrieres[i];
            listFourmisGuerrieres.erase(listFourmisGuerrieres.begin() +i);
            i--;
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
    addReine();
    // addOeuf();
    addFourmisOuvrieres(5);
    addFourmisGuerrieres(5);
}

void Fourmilliere::addOeuf() {
    listOeufs.push_back(new Oeuf(this));
}

void Fourmilliere::addReine() {
    reine = new Reine(this);
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

void Fourmilliere::addFood(int* nb) {
    if (food + *nb <= foodMax) {
        food += *nb;
        *nb = 0;
    } 
    // else {

    // }
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

void Fourmilliere::evolToLarve(Oeuf* o) {
    for(int i=0; i<listOeufs.size(); i++) {
        if (listOeufs[i] == o) {
            listLarves.push_back(new Larve(this));
            delete(o);
            listOeufs.erase(listOeufs.begin() + i);
        }
    }
}

void Fourmilliere::evolToOuvriere(Larve* f) {
    for(int i=0; i<listLarves.size(); i++) {
        if (listLarves[i] == f) {
            listFourmisOuvrieres.push_back(new FourmiOuvriere(this, f->getVie()));
            delete(f);
            listLarves.erase(listLarves.begin() + i);
        }
    }
}

void Fourmilliere::evolToGuerriere(FourmiOuvriere* f) {
    for(int i=0; i<listFourmisOuvrieres.size(); i++) {
        if (listFourmisOuvrieres[i] == f) {
            listFourmisGuerrieres.push_back(new FourmiGuerriere(this, f->getVie()));
            delete(f);
            listFourmisOuvrieres.erase(listFourmisOuvrieres.begin() + i);
        }
    }
}