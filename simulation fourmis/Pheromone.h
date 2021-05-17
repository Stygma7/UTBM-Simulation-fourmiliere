#pragma once

#include "Position.h"

class Pheromone
{
private:
    // quantite de pheromone actuelle
    int amount;
    // quantite max de pheromone
    const int amountMax = 12;
    // position des pheromones
    Position pos;

public:
    Pheromone(Position p) : amount(12), pos(p) {}
    
    int getAmount() {return amount;}
    Position getPos() {return pos;}

    void addAmount(int);
    void addAmount();
    void update();
};
