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

	void updateType();

public:
	Case();
	// ~Case();

	bool getDeplacement() { return this->deplacement; }
	Position getPos() { return pos; }
	Type getType() { return type; }
	SourceNourr getSrcNour() { return *srcNour; }

	void setObstacle();
	void setSrcNourr();
	void setPos(Position);
	void setPos(int, int);
};

