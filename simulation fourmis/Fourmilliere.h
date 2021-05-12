#pragma once
// #ifndef FOURMILLIERE_H
// #define FOURMILLIERE_H
#include <vector>
#include "FourmiGuerriere.h"
class FourmiGuerriere;
#include "Position.h"
#include "Environnement.h"
class Environnement;

class Fourmilliere
{
private:
    Position pos;
    int populationMax = 100;
    int foodMax = 200;
    int food = 0;
    std::vector<FourmiGuerriere> listFourmisGuerrieres;
    Environnement* env;

    void addAnts();

public:
    Fourmilliere(Environnement*, Position);
    Fourmilliere(Environnement* env);

    Position getPos() {return pos;}
    Environnement* getEnv() {return env;}
    void update();
    void addFood(int);
    int getFood() {return food;}
    int getNbrAnts() {return listFourmisGuerrieres.size();}
    bool isFoodStockFull();
};

// #endif