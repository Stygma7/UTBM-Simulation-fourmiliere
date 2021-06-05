
#ifndef FOURMILLIERE_H
#define FOURMILLIERE_H
#include <vector>
#include "Oeuf.h"
class Oeuf;
#include "Larve.h"
class Larve;
#include "FourmiGuerriere.h"
class FourmiGuerriere;
#include "FourmiOuvriere.h"
class FourmiOuvriere;
#include "Reine.h"
class Reine;
#include "Position.h"
#include "Environnement.h"
class Environnement;

class Fourmilliere
{
private:
    // position de la fourmilliere
    Position pos;
    // nombre de fourmi max 
    int populationMax = 100;
    // nombre de nourriture max 
    int foodMax = 20000;
    // nourriture actuellement disponible
    int food = 0;
    // Reine de la fourmillière
    Reine* reine;
    // liste des oeufs de la fourmilliere
    std::vector<Oeuf*> listOeufs;
    // liste des larves de la fourmilliere
    std::vector<Larve*> listLarves;
    // liste des fourmis guerrieres de la fourmilliere
    std::vector<FourmiGuerriere*> listFourmisGuerrieres;
    // liste des fourmis ouvrières de la fourmilliere
    std::vector<FourmiOuvriere*> listFourmisOuvrieres;
    // pointeur sur l'environnement de la fourmilliere
    Environnement* env;

    // ajoute les fourmis de base
    void addReine();
    void addAntsDefault();
    void addFourmisGuerrieres(int);
    void addFourmisOuvrieres(int);
    
public:
    // Constructeurs
    Fourmilliere(Environnement*, Position);
    ~Fourmilliere();
    // Fourmilliere(Environnement* env);

    Position getPos() {return pos;}
    Environnement* getEnv() {return env;}
    int getFood() {return food;}
    int getFoodMax() {return foodMax;}
    int getNbrOeufs() {return listOeufs.size();}
    int getNbrLarves() {return listLarves.size();}
    int getNbrFourmiGuerrieres() {return listFourmisGuerrieres.size();}
    int getNbrFourmiOuvrieres() {return listFourmisOuvrieres.size();}

    // met à jour toutes les fourmis de la fourmilliere
    void update();

    // affiche les fourmis
    void DispAnts();
    // efface les fourmis
    void EraseAnts();

    // ajoute de la nourriture dans la fourmilliere
    void addFood(int);
    void addFood(int*);
    // retirer de la nourriture dans la fourmilliere
    void substractFood(int);
    // teste si les stock de nourriture sont plein
    bool isFoodStockFull();
    // teste si les stock de nourriture sont vide
    bool isFoodStockEmpty();

    void addOeuf();

    void evolToLarve(Oeuf*);
    void evolToOuvriere(Larve*);
    void evolToGuerriere(FourmiOuvriere*);
};

#endif