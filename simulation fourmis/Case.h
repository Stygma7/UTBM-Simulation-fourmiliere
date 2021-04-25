#pragma once

class Case
{
//Constructeurs
public:
	Case();
	Case(bool deplacement);

//Attributs
private:
	//Position de la case (à voir si on garde)
	//int posX;
	//int posY;
	//Permet de savoir si le déplacement est possible ou non sur la case (oui par défaut)
	bool deplacement;
	
//Méthodes
public:
	//int getPosX();
	//int getPosY();
	bool getDeplacement();

	//void setPosX(int posX);
	//void setPosY(int posY);
	void setDeplacement(bool deplacement);
	

};

