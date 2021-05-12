#pragma once

#include <vector>
#include "Case.h"
#include "Fourmilliere.h"
class Fourmilliere;

class Environnement {
public:
	// Constructeurs
	Environnement();
	Environnement(int, int, int, int);

	// Getters
	int getColonne() { return this->colonne; }
	int getLigne() { return this->ligne; }
	int getNbrObstacles() { return this->nbrObstacles; }
	int getNbrSrcNourriture() { return this->nbrSrcNourriture; }
	// double gettauxEvapPheromone() { return this->tauxEvapPheromone; }
	Case getCase(int x, int y) { return carte[y][x];}
	Case* getPtrCase(int x, int y) { return &carte[y][x];}

	// Setters
	void setColonne(int colonne) { this->colonne = colonne; }
	void setLigne(int ligne) { this->ligne = ligne; }
	void setnbrObstacles(int nbObst) { this->nbrObstacles = nbObst; }
	void setnbrSrcNourriture(int nbSrcNour) { this->nbrSrcNourriture = nbSrcNour; }
	// void settauxEvapPheromone(double evap) { this->tauxEvapPheromone = evap; }

	// Affichage
	void showInfos();
	void showInfosInit();
	void updateInfos();
	void afficherCarte();

	// MaJ du monde
	void update();

private:
	// Attributs
	int colonne = 100;
	int ligne = 50;
	int nbrObstacles = 10;
	int nbrSrcNourriture = 500;
	const int affOffset = 4;
	// double tauxEvapPheromone = 0.95;
	std::vector<std::vector<Case>> carte;
	Fourmilliere* fourmilliere;

	//Génération
	void genererCarte();
	void ajoutObstacles();
	void ajoutNourriture();
};
