#pragma once

#include "Position.h"

class Pheromone
{
private:
    // quantite de pheromone actuelle
    int amount;
    // quantite max de pheromone
    const int amountMax = 30;
    // position des pheromones
    Position pos;

public:
    Pheromone(Position p) : amount(30), pos(p) {}
    
    int getAmount() {return amount;}
    Position getPos() {return pos;}

    void addAmount(int);
    void addAmount();
    void update();
};
