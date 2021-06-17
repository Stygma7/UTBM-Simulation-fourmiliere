#ifndef __CASE_H__
#define __CASE_H__

#include "caseType.h"
#include "Position.h"
#include "SourceNourr.h"
#include "Pheromone.h"
#include "CaseInfoAff.h"
#include <unordered_set>

class Environnement;

class Case {

private:
	// pointeur de l'environnement
	Environnement* env;
	// boolean deplacement sur la case possible ou pas
	bool deplacement;
	// position de la case
	Position pos;
	// type de case
	Type type;
	// pointeur sur source de nourriture
	SourceNourr* srcNour = nullptr;
	// pointeur sur pheromone toFood
	Pheromone* pheroToFood = nullptr;
	// pointeur sur pheromone toHome
	Pheromone* pheroToHome = nullptr;
	// Liste des éléments présents sur la case pour mieux gérer l'affichage
	std::unordered_set <CaseInfoAff> listAffichage;

public:
	// Constructeur
	
	Case(Environnement*);
	~Case();

	// Getters

	bool getDeplacement() { return this->deplacement; }
	Position getPos() { return pos; }
	Type getType() { return type; }
	Pheromone* getPheroToFood() { return pheroToFood; }
	Pheromone* getPheroToHome() { return pheroToHome; }

	// Setters

	void setPos(Position);
	void setPos(int, int);
	void setType(Type);
	void setPheroToFood(Pheromone*);
	void setPheroToHome(Pheromone*);

	int pickNourr(int);
	void addReducPheroToFood(int);
	void addReducPheroToHome(int);
	
	bool isTherePheroToFood();
	bool isTherePheroToHome();

	void addAffichage(CaseInfoAff);
	void deleteAffichage(CaseInfoAff);
	CaseInfoAff getInfoAff();
};

#endif