#include <vector>
#include "Case.h"

class Environnement {
public:
	// Constructeurs
	Environnement();

	// Getters
	int getLongueur();
	int getlargeur();
	int getnbrObstacles();
	int getnbrSrcNourriture();
	double gettauxEvapPheromone();

	// Setters
	void setLongueur(int longueur);
	void setlargeur(int larg);
	void setnbrObstacles(int nbObst);
	void setnbrSrcNourriture(int nbSrcNour);
	void settauxEvapPheromone(double evap);

	//Affichage
	void afficherInfos();
	void afficherCarte();

private:
	// Attributs
	int longueur = 100;
	int largeur = 50;
	int nbrObstacles = 1000;
	int nbrSrcNourriture = 500;
	double tauxEvapPheromone = 0.95;
	vector<vector<Case>> carte;

	//Génération
	void genererCarte();
};

