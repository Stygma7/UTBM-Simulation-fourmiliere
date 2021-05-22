#include "Pheromone.h"

void Pheromone::addAmount(int a) {
    if (amount + a >= AMOUNT_MAX) 
        amount = AMOUNT_MAX;
    else
        amount += a;
}

// ajoute de la phero seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Pheromone::addReducAmount(int redu) {
    if (amount < AMOUNT_MAX - redu) 
        amount = AMOUNT_MAX - redu;
}

void Pheromone::addAmount() {
    amount = AMOUNT_MAX;
}

void Pheromone::update() {
    if (amount >= 0)
        amount--; 
    // else
    //     delete this;    
}