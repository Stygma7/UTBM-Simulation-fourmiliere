#pragma once

class Case
{
//Constructeurs
public:
	Case();
	Case(bool deplacement);

//Attributs
private:
	//Position de la case (� voir si on garde)
	//int posX;
	//int posY;
	//Permet de savoir si le d�placement est possible ou non sur la case (oui par d�faut)
	bool deplacement;
	
//M�thodes
public:
	//int getPosX();
	//int getPosY();
	bool getDeplacement();

	//void setPosX(int posX);
	//void setPosY(int posY);
	void setDeplacement(bool deplacement);
	

};

