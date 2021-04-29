#pragma once

class Case {

//Attributs
private:
	//Position de la case (à voir si on garde)
	//int posX;
	//int posY;
	//Permet de savoir si le déplacement est possible ou non sur la case (oui par défaut)
	bool deplacement;
	bool nourriture;

public:
//Constructeurs
	Case();
	Case(bool);

//Méthodes
	bool getDeplacement() { return this->deplacement; }
	bool getNourriture() { return this->nourriture; }

	void setDeplacement(bool deplacement) {	this->deplacement = deplacement; }
	void setNourriture(bool nourriture) { this->nourriture = nourriture; }
};

