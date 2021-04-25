#include <iostream>
#include "Environnement.h"

using namespace std;

// Cosntructeurs
Environnement::Environnement() {
	genererCarte();
}

// Getters
int Environnement::getLongueur() { return this->longueur; }
int Environnement::getlargeur() { return this->largeur; }
int Environnement::getnbrObstacles() { return this->nbrObstacles; }
int Environnement::getnbrSrcNourriture() { return this->nbrSrcNourriture; }
double Environnement::gettauxEvapPheromone() { return this->tauxEvapPheromone; }

// Setters
void Environnement::setLongueur(int longueur) { this->longueur = longueur; }
void Environnement::setlargeur(int larg) { this->largeur = larg; }
void Environnement::setnbrObstacles(int nbObst) { this->nbrObstacles = nbObst; }
void Environnement::setnbrSrcNourriture(int nbSrcNour) { this->nbrSrcNourriture = nbSrcNour; }
void Environnement::settauxEvapPheromone(double evap) { this->tauxEvapPheromone = evap; }

//Affichage
void Environnement::afficherInfos() {
	std::cout << "Longueur : " << this->getLongueur() << "\n";
	std::cout << "Largeur : " << this->getlargeur() << "\n";
	std::cout << "Nombre d'obstacles : " << this->getnbrObstacles() << "\n";
	std::cout << "Nombre de source de nourriture : " << this->getnbrSrcNourriture() << "\n";
	std::cout << "Taux d'evaporation des Pheromones : " << this->gettauxEvapPheromone() << "\n";
}

void Environnement::afficherCarte() {
	std::cout << "Carte des fourmis : \n";
	for (int i = 0; i < 50; i++) {
		std::cout << "\n";
		for (int j = 0; j < 100; j++) {
			if (carte[j][i].getDeplacement() == false)
				std::cout << "X";
			else
				std::cout << " ";
		}
	}
}

//Génération
void Environnement::genererCarte() {
	srand(time(NULL));
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 100; j++) {
			if (rand() % 15 == 0)
				carte[j][i].setDeplacement(false);
		}
	}
}
