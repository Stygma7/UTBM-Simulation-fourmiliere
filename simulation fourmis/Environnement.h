#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H

#include <vector>
#include <conio.h>
#include <windows.h>
#include "Case.h"
// #include "Fourmilliere.h"

using namespace std;

class Environnement {
public:
	// Constructeurs
	Environnement();
	Environnement(int, int, int, int);

	// Getters
	int getColonne() { return this->colonne; }
	int getLigne() { return this->ligne; }
	int getnbrObstacles() { return this->nbrObstacles; }
	int getnbrSrcNourriture() { return this->nbrSrcNourriture; }
	// double gettauxEvapPheromone() { return this->tauxEvapPheromone; }
	Case getCase(int x, int y) { return carte[y][x];}

	// Setters
	void setColonne(int colonne) { this->colonne = colonne; }
	void setLigne(int ligne) { this->ligne = ligne; }
	void setnbrObstacles(int nbObst) { this->nbrObstacles = nbObst; }
	void setnbrSrcNourriture(int nbSrcNour) { this->nbrSrcNourriture = nbSrcNour; }
	// void settauxEvapPheromone(double evap) { this->tauxEvapPheromone = evap; }

	// Affichage
	void afficherInfos();
	void afficherCarte();

	// MaJ du monde
	void update();

private:
	// Attributs
	int colonne = 100;
	int ligne = 50;
	int nbrObstacles = 10;
	int nbrSrcNourriture = 500;
	// double tauxEvapPheromone = 0.95;
	vector<vector<Case>> carte;
	// Fourmilliere fourmilliere;
	// Fourmilliere* fourmilliere = nullptr;

	//Génération
	void genererCarte();
	void ajoutObstacles();
	void ajoutNourriture();
};

#endif