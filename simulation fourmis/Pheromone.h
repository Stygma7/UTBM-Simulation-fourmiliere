#pragma once
#include "Position.h"

// quantite max de pheromone
#define AMOUNT_MAX 50

class Pheromone
{
private:
    // quantite de pheromone actuelle
    int amount;
    // position des pheromones
    Position pos;

public:
    Pheromone(Position p) : amount(AMOUNT_MAX), pos(p) {}
    Pheromone(Position p, int reduc) : amount(AMOUNT_MAX-reduc), pos(p) {}

    int getAmount() {return amount;}
    int getAmountMax() { return AMOUNT_MAX; }
    Position getPos() {return pos;}

    void addAmount();
    void addAmount(int);
    void addReducAmount(int);
    void update();
};
