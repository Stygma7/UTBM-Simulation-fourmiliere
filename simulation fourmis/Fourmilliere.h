#ifndef FOURMILLIERE_H
#define FOURMILLIERE_H

#include "Position.h"
//#include "Reine.h"
#include "FourmiGuerriere.h"
#include "Environnement.h"
#include <vector>

using namespace std;

class Fourmilliere
{
private:
    Position pos;
    int populationMax = 100;
    int qteNourrMax = 200;
    //Reine reine;
    vector<FourmiGuerriere> listFourmisGuerrieres;

public:
    Fourmilliere();
    Fourmilliere(Environnement&, Position);

    Position getPos() {return pos;}
    void update(Environnement&);
};

#endif