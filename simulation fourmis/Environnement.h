#ifndef __ENVIRONNEMENT_H__
#define __ENVIRONNEMENT_H__

#include <vector>
#include "Case.h"
#include "Fourmilliere.h"
class Fourmilliere;
#include "Pheromone.h"

class Environnement {
public:
	// Constructeurs
	// Environnement();
	Environnement(int, int, int, int);

	~Environnement();

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
	void afficherCarteInit();

	// MaJ du monde
	void update();
	void addPheroToFood(Position, int);
	void addPheroToHome(Position, int);
	void addObstacles(int);

private:
	// Attributs
	int colonne = 100;
	int ligne = 50;
	int nbrObstacles = 10;
	int nbrSrcNourriture = 500;
	int nbrTour = 0;
	const int affOffset = 4;
	// double tauxEvapPheromone = 0.95;
	std::vector<std::vector<Case>> carte;
	// Liste des pheromones déposée lors de trajet à la nourriture
	std::vector<Pheromone*> listPheroToFood;
	// Liste des pheromones déposée lors de trajet à la maison
	std::vector<Pheromone*> listPheroToHome;
	// Liste de Position de Pheromone à désafficher
	std::vector<Position> listPosToErase;
	// Pointeur sur fourmilliere (à transformer en liste plus tard lorsqu'il y en aura plusieurs)
	Fourmilliere* fourmilliere;

	//Génération
	void genererCarte();
	void addObstaclesInit();
	void addNourritureInit();
	
	void showInfos();
	void showInfosInit();
	void updateInfos();
	void dispPhero();
	void dispFourmilliere();
	void updateAffichage();
};

#endif