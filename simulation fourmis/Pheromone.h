#pragma once

#include "Position.h"

class Pheromone
{
private:
    int amount;
    const int amountMax = 30;
    Position pos;

public:
    Pheromone(Position p) : amount(30), pos(p) {}
    int getAmount() {return amount;}
    Position getPos() {return pos;}

    void addAmount(int);
    void addAmount();
    void update();
};
