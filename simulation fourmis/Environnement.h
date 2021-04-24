#pragma once

class Environnement {
private:
	int longueur = 100;
	int largeur = 50;
	int nbrObstacles = 1000;
	int nbrSrcNourriture = 500;
	float tauxEvapPheromone = 0.95;
	Objet env[100][50] = null
		new obstacle(x, y)
		env[x][y] = obs

	case tableau[100][50];
	tableau[2][5] = obstacle


public:
	int getLongueur();
	void setLongueur(int longueur);

	int getlargeur();
	void setlargeur(int larg);

	int getnbrObstacles();
	void setnbrObstacles(int nbObst);

	int getnbrSrcNourriture();
	void setnbrSrcNourriture(int nbSrcNour);

	float gettauxEvapPheromone();
	void settauxEvapPheromone(float evap);

	void afficherInfos();
};

