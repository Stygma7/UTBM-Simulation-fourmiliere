#pragma once

#include "caseType.h"
#include "Position.h"
#include "SourceNourr.h"
#include "Pheromone.h"

class Case {

private:
	// deplacement sur la case
	bool deplacement;
	// position de la case
	Position pos;
	// type de case
	Type type;
	// pointeur sur source de nourriture
	SourceNourr* srcNour = nullptr;
	// pointeur sur pheromone
	Pheromone* phero = nullptr;

public:
	// Constructeurs
	Case();

	// Getters
	bool getDeplacement() { return this->deplacement; }
	Position getPos() { return pos; }
	Type getType() { return type; }
	Pheromone* getPheromone() { return phero; }

	// Setters
	void setPos(Position);
	void setPos(int, int);
	void setType(Type);
	void setPhero(Pheromone*);

	// 
	void pickNourr();
	void addPhero();
	bool isTherePhero();
};
