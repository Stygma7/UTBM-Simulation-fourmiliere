#pragma once
// #ifndef FOURMILLIERE_H
// #define FOURMILLIERE_H
#include <vector>
#include "FourmiGuerriere.h"
class FourmiGuerriere;
#include "FourmiOuvriere.h"
class FourmiOuvriere;
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
    int foodMax = 2000;
    // nourriture actuellement disponible
    int food = 0;
    // liste des fourmis guerrieres de la fourmilliere
    std::vector<FourmiGuerriere*> listFourmisGuerrieres;
    // liste des fourmis ouvrières de la fourmilliere
    std::vector<FourmiOuvriere*> listFourmisOuvrieres;
    // pointeur sur l'environnement de la fourmilliere
    Environnement* env;

    // ajoute les fourmis de base
    void addAntsDefault();
    void addFourmisGuerrieres(int);
    void addFourmisOuvrieres(int);
    
public:
    // Constructeurs
    Fourmilliere(Environnement*, Position);
    // Fourmilliere(Environnement* env);

    Position getPos() {return pos;}
    Environnement* getEnv() {return env;}
    int getFood() {return food;}
    int getNbrAntsG() {return listFourmisGuerrieres.size();}
    int getNbrAntsO() {return listFourmisOuvrieres.size();}

    // met à jour toutes les fourmis de la fourmilliere
    void update();

    // affiche les fourmis
    void DispAnts();
    // efface les fourmis
    void EraseAnts();

    // ajoute de la nourriture dans la fourmilliere
    void addFood(int);
    // retirer de la nourriture dans la fourmilliere
    void substractFood(int);
    // teste si les stock de nourriture sont plein
    bool isFoodStockFull();
    // teste si les stock de nourriture sont vide
    bool isFoodStockEmpty();
};

// #endif