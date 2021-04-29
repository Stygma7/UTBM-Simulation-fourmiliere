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
	cout << "\nCarte des fourmis : \n";
	for (int y = 0; y < 102; y++) {
		cout << "_";
	}
	cout << "\n";

	for (int y = 0; y < 50; y++) {
		cout << "|";
		for (int x = 0; x < 100; x++) {
			if (carte[y][x].getDeplacement() == false) {
				std::cout << "X";
			} else {
				std::cout << " ";
			}
		}
		cout << "|\n";
	}
	
	cout << "|";
	for (int y = 0; y < 100; y++) {
		cout << "_";
	}
	cout << "|";
}

//Génération
void Environnement::genererCarte() {
	vector<Case> ligne;
	srand(time(NULL));
	for (int y = 0; y < largeur; y++) {
		for (int x = 0; x < longueur; x++) {
			if ((rand() % 15) == 0) {
				ligne.push_back(Case(false));
				ligne[x].setDeplacement(false);
			} else {
				ligne.push_back(Case());
				ligne[x].setDeplacement(true);
			}
		}
		carte.push_back(ligne);
	}
}
