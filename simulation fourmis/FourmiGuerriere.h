#pragma once
// #ifndef FOURMIG_H
// #define FOURMIG_H
#include <vector>
#include "Fourmilliere.h"
class Fourmilliere;
#include "Environnement.h"
class Environnement;
#include "Position.h"
#include "ModeFourmi.h"
#include "Fourmi.h"

class FourmiGuerriere : public Fourmi
{
private:
    std::vector<Position> cheminToHome;
    Position pos;
    Position lastPos;
    Mode mode = Mode::toFood;
    Environnement* env;
    Fourmilliere* colonie;
    void moveToHome();
    void moveToFood();
    void setMode(Mode mode) { this->mode = mode;}

public:
    // FourmiGuerriere(Environnement*);
    FourmiGuerriere(Fourmilliere*);

    void display();
    void update();
    Position getPos() { return pos; }
    void grabNourriture(Case*);
    void dropNourriture();
    void eraseLastPos();
    void dispFourmi();
};

// #endif