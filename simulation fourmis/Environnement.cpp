#include <iostream>
#include "Environnement.h"

using namespace std;

int Environnement::getLongueur() { 
	return this->longueur; 
}

void Environnement::setLongueur(int longueur) { 
	this->longueur = longueur; 
}

int Environnement::getlargeur() { 
	return this->largeur; 
}

void Environnement::setlargeur(int larg) { 
	this->largeur = larg; 
}

int Environnement::getnbrObstacles() { 
	return this->nbrObstacles; 
}

void Environnement::setnbrObstacles(int nbObst) { 
	this->nbrObstacles = nbObst; 
}

int Environnement::getnbrSrcNourriture() { 
	return this->nbrSrcNourriture; 
}

void Environnement::setnbrSrcNourriture(int nbSrcNour) { 
	this->nbrSrcNourriture = nbSrcNour; 
}

float Environnement::gettauxEvapPheromone() { 
	return this->tauxEvapPheromone; 
}

void Environnement::settauxEvapPheromone(float evap) {
	this->tauxEvapPheromone = evap; 
}

void Environnement::afficherInfos(){
	std::cout << "Longueur : " << this->getLongueur() << "\n";
	std::cout << "Largeur : " << this->getlargeur() << "\n";
	std::cout << "Nombre d'obstacles : " << this->getnbrObstacles() << "\n";
	std::cout << "Nombre de source de nourriture : " << this->getnbrSrcNourriture() << "\n";
	std::cout << "Taux d'evaporation des Pheromones : " << this->gettauxEvapPheromone() << "\n";
	
}
