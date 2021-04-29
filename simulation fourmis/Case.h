#pragma once

class Case {

//Attributs
private:
	//Position de la case (� voir si on garde)
	//int posX;
	//int posY;
	//Permet de savoir si le d�placement est possible ou non sur la case (oui par d�faut)
	bool deplacement;
	int test;

public:
//Constructeurs
	Case();
	Case(bool);

//M�thodes
	bool getDeplacement() {
		return this->deplacement;
	}

	void setDeplacement(bool deplacement) {
		this->deplacement = deplacement;
	}
	

};

