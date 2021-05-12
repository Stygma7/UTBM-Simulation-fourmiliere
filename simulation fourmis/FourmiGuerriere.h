#ifndef FOURMIG_H
#define FOURMIG_H

#pragma once
#include <vector>
#include <conio.h>
#include <windows.h>
#include "Fourmi.h"
#include "Environnement.h"
#include "ModeFourmi.h"
// #include "Fourmilliere.h"

using namespace std;

class FourmiGuerriere : public Fourmi
{
private:
    vector<Position> cheminToHome;
    Position pos;
    Position lastPos;
    Mode mode = Mode::toFood;
    void moveToHome(Environnement&);
    void moveToFood(Environnement&);
    void setMode(Mode mode) { this->mode = mode;}

public:
    FourmiGuerriere(Environnement&);
    //FourmiGuerriere(Fourmilliere&);

    void display();
    void update(Environnement&);
    Position getPos() { return pos; }
    void grabNourriture(SourceNourr);
    void dropNourriture();
};

#endif