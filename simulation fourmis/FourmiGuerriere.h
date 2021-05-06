#pragma once
#include <conio.h>
#include <windows.h>
#include "Fourmi.h"
#include "Environnement.h"
#include "ModeFourmi.h"

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

    void display();
    void move(Environnement&);
    Position getPos() { return pos; }
    void grabNourriture(SourceNourr);
    void dropNourriture();
};