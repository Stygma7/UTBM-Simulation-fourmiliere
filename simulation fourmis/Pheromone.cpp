#include "Pheromone.h"

// ajoute de la phero seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Pheromone::addReducAmount(int redu) {
    if (amount < AMOUNT_MAX - redu) 
        amount = AMOUNT_MAX - redu;
}

// met à jour la pheromone pour un tour
void Pheromone::update() {
    if (amount >= 0)
        amount--; 
}