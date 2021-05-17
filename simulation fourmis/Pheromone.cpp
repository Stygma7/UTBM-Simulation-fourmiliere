#include "Pheromone.h"

void Pheromone::addAmount(int a) {
    if (amount + a >= amountMax) 
        amount = amountMax;
    else
        amount += a;
}

void Pheromone::addAmount() {
    amount = amountMax;
}

void Pheromone::update() {
    if (amount >= 0)
        amount--; 
    // else
    //     delete this;    
}