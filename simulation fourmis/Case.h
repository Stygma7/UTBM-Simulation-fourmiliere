#pragma once
#include "caseType.h"

class Case {

//Attributs
private:
	//Position de la case (à voir si on garde)
	//int posX;
	//int posY;
	//Permet de savoir si le déplacement est possible ou non sur la case (oui par défaut)
	bool deplacement;
	// bool nourriture;
	int qteNourriture;
	Type type;

public:
//Constructeurs
	Case();
	// Case(bool);

//Méthodes
	bool getDeplacement() { return this->deplacement; }
	// bool getNourriture() { return this->nourriture; }
	bool getQteNourriture() { return this->qteNourriture; }
	Type getType();
	void updateType();

	// void setDeplacement(bool deplacement) {	this->deplacement = deplacement; }
	void setObstacle();
	// void setNourriture(bool nourriture) { this->nourriture = nourriture; }
	void setQteNourriture(int qteNourriture);
	void setSrcNourr();
};

