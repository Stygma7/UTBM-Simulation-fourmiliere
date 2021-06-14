#ifndef FOURMILIERE_H
#define FOURMILIERE_H
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

class Fourmiliere
{
private:
    // position de la Fourmiliere
    Position pos;
    // nombre de fourmi max 
    int populationMax = 80;
    // nombre de nourriture max 
    int foodMax = 100;
    // nourriture actuellement disponible
    int food = 0;
    // Reine de la fourmillière
    Reine* reine;
    // liste des oeufs de la Fourmiliere
    std::vector<Oeuf*> listOeufs;
    // liste des larves de la Fourmiliere
    std::vector<Larve*> listLarves;
    // liste des fourmis guerrieres de la Fourmiliere
    std::vector<FourmiGuerriere*> listFourmisGuerrieres;
    // liste des fourmis ouvrières de la Fourmiliere
    std::vector<FourmiOuvriere*> listFourmisOuvrieres;
    // pointeur sur l'environnement de la Fourmiliere
    Environnement* env;

    // ajoute les fourmis de base
    void addReine();
    void addAntsDefault();
    void addFourmisGuerrieres(int);
    void addFourmisOuvrieres(int);
    
public:
    // Constructeurs
    Fourmiliere(Environnement*, Position);
    ~Fourmiliere();
    // Fourmiliere(Environnement* env);

    Position getPos() {return pos;}
    Environnement* getEnv() {return env;}
    int getFood() {return food;}
    int getFoodMax() {return foodMax;}
    int getNbrOeufs() {return listOeufs.size();}
    int getNbrLarves() {return listLarves.size();}
    int getNbrFourmiGuerrieres() {return listFourmisGuerrieres.size();}
    int getNbrFourmiOuvrieres() {return listFourmisOuvrieres.size();}
    int getPop();
    int getPopMax() {return populationMax;}
    int getNbrReine();
    // met à jour toutes les fourmis de la Fourmiliere
    void update();

    // ajoute de la nourriture dans la Fourmiliere
    void addFood(int);
    // retirer de la nourriture dans la Fourmiliere
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