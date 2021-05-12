#pragma once
#include "caseType.h"
#include "Position.h"
#include "SourceNourr.h"

class Case {

private:
	//Permet de savoir si le déplacement est possible ou non sur la case (oui par défaut)
	bool deplacement;
	Position pos;
	Type type;
	SourceNourr* srcNour = nullptr;
	// Pheromone* pheromone = nullptr;

	void updateType();

public:
	Case();
	// ~Case();

	bool getDeplacement() { return this->deplacement; }
	Position getPos() { return pos; }
	Type getType() { return type; }
	SourceNourr getSrcNour() { return *srcNour; }
	// Pheromone getPheromone() { return *pheromone; }

	void setObstacle();
	void setSrcNourr();
	// void ajoutPheromone(Pheromone*);
	void setPos(Position);
	void setPos(int, int);
};

