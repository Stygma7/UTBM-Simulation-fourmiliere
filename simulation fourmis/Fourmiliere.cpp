#include "Fourmiliere.h"
#include "FourmiOuvriere.h"

using namespace std;

Fourmiliere::Fourmiliere(Environnement* env, Position position) {
    this->env = env;
    pos = position;
    addAntsDefault();
}

Fourmiliere::~Fourmiliere() {
    delete reine;
	for (FourmiGuerriere* & fourmi : listFourmisGuerrieres) {
		delete(fourmi);
	}
	for (FourmiOuvriere* & fourmi : listFourmisOuvrieres) {
		delete(fourmi);
	}
	for (Larve* & larve : listLarves) {
		delete(larve);
	}
	for (Oeuf* & oeuf : listOeufs) {
		delete(oeuf);
	}
}

// met à jour toute la fourmiliere pour un tour
void Fourmiliere::update() {
    // MaJ reine
    if (reine != nullptr) {
        if (reine->isAlive()) {
            reine->update();
        } else {
            delete reine;
            reine = nullptr;
        }
    }
    
    // MaJ oeufs
    for(int i=0; i<listOeufs.size(); i++) {
        listOeufs[i]->update();
    }

    // MaJ larves
    for(int i=0; i<listLarves.size(); i++) {

        if (listLarves[i]->isAlive()) {
            listLarves[i]->update();
        } else {
            delete listLarves[i];
            listLarves.erase(listLarves.begin() +i);
            i--;
        }
    }

    // MaJ fourmis ouvrières
    for(int i=0; i<listFourmisOuvrieres.size(); i++) {
        if (listFourmisOuvrieres[i]->isAlive()) {
            listFourmisOuvrieres[i]->update();
        } else {
            delete listFourmisOuvrieres[i];
            listFourmisOuvrieres.erase(listFourmisOuvrieres.begin() +i);
            i--;
        }
    }

    // MaJ fourmis guerrières
    for(int i=0; i<listFourmisGuerrieres.size(); i++) {
        if (listFourmisGuerrieres[i]->isAlive()) {
            listFourmisGuerrieres[i]->update();
        } else {
            env->getPtrCase(listFourmisGuerrieres[i]->getPos().getX(), listFourmisGuerrieres[i]->getPos().getY())->deleteAffichage(CaseInfoAff::Fourmi);
            delete listFourmisGuerrieres[i];
            listFourmisGuerrieres.erase(listFourmisGuerrieres.begin() +i);
            i--;
        }
    }
}

// ajoute les fourmis de bases à la création de la fourmilière
void Fourmiliere::addAntsDefault() {
    addReine();
    addFourmisOuvrieres(5);
    addFourmisGuerrieres(10);
}

// ajoute un oeuf
void Fourmiliere::addOeuf() {
    listOeufs.push_back(new Oeuf(this));
}

// ajoute la reine
void Fourmiliere::addReine() {
    reine = new Reine(this);
}

// ajoute des fourmis guerrières
void Fourmiliere::addFourmisGuerrieres(int nb) {
    for (int i = 0; i < nb; i++) {
        listFourmisGuerrieres.push_back(new FourmiGuerriere(this));
    }
}

// ajoute des fourmis ouvrières
void Fourmiliere::addFourmisOuvrieres(int nb) {
    for (int i = 0; i < nb; i++) {
        listFourmisOuvrieres.push_back(new FourmiOuvriere(this));
    }
}

// ajoute de la nourriture dans la fourmilière
void Fourmiliere::addFood(int nb) {
    if (food + nb <= foodMax) {
        food += nb;
    }
}

// enleve de la nourriture de la fourmilière
void Fourmiliere::substractFood(int nb) {
    if (food >= 0) {
        food -= nb;
    }
}

// true: le stock de nourriture max est atteint
bool Fourmiliere::isFoodStockFull() {
    if (food >= foodMax)
        return true;
    else
        return false;
}

// true: le stock de nourriture est vide
bool Fourmiliere::isFoodStockEmpty() {
    if (food <= 0)
        return true;
    else
        return false;
}

// fait évoluer un oeuf à l'état de larve
void Fourmiliere::evolToLarve(Oeuf* o) {
    for(int i=0; i<listOeufs.size(); i++) {
        if (listOeufs[i] == o) {
            listLarves.push_back(new Larve(this));
            delete(o);
            listOeufs.erase(listOeufs.begin() + i);
        }
    }
}

// fait évoluer une larve à l'état de fourmi ouvrière
void Fourmiliere::evolToOuvriere(Larve* f) {
    for(int i=0; i<listLarves.size(); i++) {
        if (listLarves[i] == f) {
            listFourmisOuvrieres.push_back(new FourmiOuvriere(this, f->getVie()));
            delete(f);
            listLarves.erase(listLarves.begin() + i);
        }
    }
}

// fait évoluer une fourmi ouvrière à l'état de fourmi guerrière
void Fourmiliere::evolToGuerriere(FourmiOuvriere* f) {
    for(int i=0; i<listFourmisOuvrieres.size(); i++) {
        if (listFourmisOuvrieres[i] == f) {
            listFourmisGuerrieres.push_back(new FourmiGuerriere(this, f->getVie()));
            delete(f);
            listFourmisOuvrieres.erase(listFourmisOuvrieres.begin() + i);
        }
    }
}

// renvoit la population présente dans la fourmilière
int Fourmiliere::getPop() {
    return getNbrReine() + listOeufs.size() + listLarves.size() + listFourmisOuvrieres.size() + listFourmisGuerrieres.size();
}

// renvoit le nombre de reine présente dans la fourmilière, logiquement uniquement 1 ou 0
int Fourmiliere::getNbrReine() {
    if (reine != nullptr)
        return 1;
    else
        return 0;
}