#include <iostream>
#include <math.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "Environnement.h"
#include "caseType.h"

using namespace std;

// ----------------- FONCTIONS -----------------------------------------------------------------------------------------------------------------------
// vérifie si les coordonnées x et y se trouvent au centre + offset des colonnes et lignes indiquées
bool isCentre(int x, int y, int colonne, int ligne) {
// bool isCentre(int x, int taille) {
	int offset = 5;
	if ( (x >= (colonne/2 -offset)) && (x <= (colonne/2 +offset)) && (y >= (ligne/2 -offset)) && (y <= (ligne/2 +offset)) )
		return true;
	else
		return false;
}

// permet d'augmenter la chance d'apparition plus on est loin du centre
bool chanceApparition(int x, int taille) {
	int tailleMax = (int)pow(taille/2,2);
	double chanceApparition = pow((x - taille/2),2);
	double facteur = 0.9 / tailleMax;
	int rand100 = rand()%100 +1;
	int chance = (int)(chanceApparition * facteur * 100);

	if (rand100 <= (chance+35)) {
		return true;
	}
	else {
		return false;
	}
}

// 0: noir
// 1: bleu foncé
// 2: vert
// 3: bleu-gris
// 4: marron
// 5: pourpre
// 6: kaki
// 7: gris clair
// 8: gris
// 9: bleu
// 10: vert fluo
// 11: turquoise
// 12: rouge
// 13: rose fluo
// 14: jaune fluo
// 15: blanc
// affiche le texte sur la console à la position souhaitée et avec la couleur souhaitée
void affichageTxtColor(Position p, string str, int color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = p.getX();
	dwPos.Y = p.getY() +1; // +1 à cause de la premiere ligne de texte
	SetConsoleCursorPosition(hcon, dwPos);
    SetConsoleTextAttribute(hcon, color);
    cout << str;
    SetConsoleTextAttribute(hcon, 15);
}

// ----------------- CONSTRUCTEURS -----------------------------------------------------------------------------------------------------------------------
Environnement::Environnement(int x, int y, int nbObstacles, int nbNourriture) {
	setColonne(x);
	setLigne(y);	
	setnbrObstacles(nbObstacles);
	setnbrSrcNourriture(nbNourriture);
	fourmiliere = new Fourmiliere(this, Position(colonne/2, ligne/2));
	listFourmiliere.push_back(fourmiliere);

	nbrTour = 0;

	genererCarte();

	getPtrCase(colonne/2, ligne/2)->addAffichage(CaseInfoAff::Fourmiliere);
	showInfosInit();

	rndApparition = 50;
}


Environnement::~Environnement() {
	for (Pheromone* & ph : listPheroToFood) {
		delete(ph);
	}
	for (Pheromone* & ph : listPheroToHome) {
		delete(ph);
	}
	for (Fourmiliere* & fourm : listFourmiliere) {
		delete(fourm);
	}
	// delete(Fourmiliere);
}


// ----------------- UPDATE ------------------------------------------------------------------------------------------------------------------------------
// permet d'avancer d'un tour pour tous les éléments présents sur l'environnement
void Environnement::update() {

	// update de toutes les pheromones ToFood
	for(int i=0; i<listPheroToFood.size();  i++) {
		listPheroToFood[i]->update();
		if (listPheroToFood[i]->getAmount() <= 0) {
			carte[listPheroToFood[i]->getPos().getY()][listPheroToFood[i]->getPos().getX()].deleteAffichage(CaseInfoAff::PheroFood);
			carte[listPheroToFood[i]->getPos().getY()][listPheroToFood[i]->getPos().getX()].setPheroToFood(nullptr);
			delete listPheroToFood[i];
			listPheroToFood.erase(listPheroToFood.begin() +i);
			i--;
		}
	}

	// update de toutes les pheromones ToHome
	for(int i=0; i<listPheroToHome.size();  i++) {
		listPheroToHome[i]->update();
		if (listPheroToHome[i]->getAmount() <= 0) {
			carte[listPheroToHome[i]->getPos().getY()][listPheroToHome[i]->getPos().getX()].deleteAffichage(CaseInfoAff::PheroHome);
			carte[listPheroToHome[i]->getPos().getY()][listPheroToHome[i]->getPos().getX()].setPheroToHome(nullptr);
			delete listPheroToHome[i];
			listPheroToHome.erase(listPheroToHome.begin() +i);
			i--;
		} 
	}

	// update de la Fourmiliere + fourmis
	for(int i=0; i<listFourmiliere.size();  i++) {
		listFourmiliere[i]->update();
	}

	// ajout d'obstacles et source de nourriture
	if ((nbrTour % rndApparition) == 0 && (nbrTour != 0)) {
		addNourriture(rand() % 4 + 6);
		addObstacles(rand() % 4 + 2);
		rndApparition = nbrTour + (rand() % 50) + 50;
	}

	nbrTour++;

	updateAffichage();
}

// ajoute de la pheromone toFood à la position souhaitée
void Environnement::addPheroToFood(Position pos, int reduc) {
	if (carte[pos.getY()][pos.getX()].isTherePheroToFood()) {
		carte[pos.getY()][pos.getX()].addReducPheroToFood(reduc);
	} else if (Pheromone::AMOUNT_MAX - reduc > 0) {
		Pheromone* ph = new Pheromone(pos, reduc);
		listPheroToFood.push_back(ph);
		carte[pos.getY()][pos.getX()].setPheroToFood(ph);
		carte[pos.getY()][pos.getX()].addAffichage(CaseInfoAff::PheroFood);
	}

}

// ajoute de la pheromone toHome à la position souhaitée
void Environnement::addPheroToHome(Position pos, int reduc) {
	if (carte[pos.getY()][pos.getX()].isTherePheroToHome()) {
		carte[pos.getY()][pos.getX()].addReducPheroToHome(reduc);
	} else if (Pheromone::AMOUNT_MAX - reduc > 0) {
		Pheromone* ph = new Pheromone(pos, reduc);
		listPheroToHome.push_back(ph);
		carte[pos.getY()][pos.getX()].setPheroToHome(ph);
		carte[pos.getY()][pos.getX()].addAffichage(CaseInfoAff::PheroHome);
	}
}


// ----------------- DISPLAY ------------------------------------------------------------------------------------------------------------------------------
// met à jour l'affichage
void Environnement::updateAffichage() {
	
	for(Case* c : listAffichage) {
		CaseInfoAff infoAff = c->getInfoAff();

		switch (infoAff)
		{
		case CaseInfoAff::Rien:
			affichageTxtColor(c->getPos(), " ", 15);
			break;

		case CaseInfoAff::Fourmi:
			affichageTxtColor(c->getPos(), "8", 12);
			break;

		case CaseInfoAff::Fourmiliere:
			affichageTxtColor(c->getPos(), "O", 6);
			break;

		case CaseInfoAff::Obstacle:
			affichageTxtColor(c->getPos(), "X", 15);
			break;

		case CaseInfoAff::PheroFood:
			affichageTxtColor(c->getPos(), ".", 14);
			break;

		case CaseInfoAff::PheroHome:
			affichageTxtColor(c->getPos(), ".", 9);
			break;

		case CaseInfoAff::SrcNourr:
			affichageTxtColor(c->getPos(), "o", 10);
			break;
		
		default:
			break;
		}
	}

	showInfos();
	listAffichage.clear();
}

// Affichage des infos initiales sur le coté de la carte
void Environnement::showInfosInit() {
    affichageTxtColor(Position(colonne + affOffset , 3), "Parametres initiaux :", 15);
    affichageTxtColor(Position(colonne + affOffset , 4), " - Colonnes  : " + to_string(getColonne()), 15);
    affichageTxtColor(Position(colonne + affOffset , 5), " - Lignes    : " + to_string(getLigne()), 15);
    affichageTxtColor(Position(colonne + affOffset , 6), " - Obstacles : " + to_string(getNbrObstacles()), 15);
    affichageTxtColor(Position(colonne + affOffset , 7), " - Src nourr : " + to_string(getNbrSrcNourriture()), 10);
}

// Affichage des infos diverses sur le coté de la carte
void Environnement::showInfos() {
	int cptLigne = 0;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Tour : " + to_string(nbrTour), 11);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Evol du terrain : " + to_string(rndApparition), 11);

	cptLigne = 9;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Colonie 1 :", 15);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), " - Qte nourr : " + to_string(fourmiliere->getFood()) + "  ", 10);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), " - Population : " + to_string(fourmiliere->getPop()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), " - Nb reine : " + to_string(fourmiliere->getNbrReine()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), " - Nb oeufs : " + to_string(fourmiliere->getNbrOeufs()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), " - Nb larves : " + to_string(fourmiliere->getNbrLarves()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), " - Nb fourmis ouv : " + to_string(fourmiliere->getNbrFourmiOuvrieres()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), " - Nb fourmis gue : " + to_string(fourmiliere->getNbrFourmiGuerrieres()) + "  ", 12);
	cptLigne++;
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nb phero toHome : " + to_string(listPheroToHome.size()) + "  ", 9);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nb phero toFood : " + to_string(listPheroToFood.size()) + "  ", 14);
}

// Ajoute une case à la liste d'affichage pour laquelle l'affichage est à mettre à jour
void Environnement::addCaseAffichage(Case* c) {
	listAffichage.insert(c);
}

// ----------------- GENERATION ------------------------------------------------------------------------------------------------------------------------------
// génère la carte (cases) avec les obstacles et sources de nourritures initiales
void Environnement::genererCarte() {
	vector<Case> vLigne;
	for (int y = 0; y < ligne+2; y++) {
		for (int x = 0; x < colonne+2; x++) {
			vLigne.push_back(Case(this));
			vLigne[x].setPos(x, y);
		}
		carte.push_back(vLigne);
	}

	srand(time(NULL));
	addObstaclesInit();
	addNourritureInit();
}

// ajoute les obstacles initiaux
void Environnement::addObstaclesInit() {
	int xRnd;
	int yRnd;
	int cptObs = 0;
	int cptWhile = 0;

	// Ajout obstacles pour la bordure de la carte
	for (int i = 0; i < colonne+2; i++)
	{
		carte[0][i].setType(Type::Obstacle);
		carte[ligne+1][i].setType(Type::Obstacle);
	}
	for (int i = 0; i < ligne+2; i++)
	{
		carte[i][0].setType(Type::Obstacle);
		carte[i][colonne+1].setType(Type::Obstacle);
	}
	
	while ((cptObs < nbrObstacles) && (cptWhile < nbrObstacles*10) ) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		if ((carte[yRnd][xRnd].getType() == Type::Normal) && (chanceApparition(xRnd,colonne)) && (chanceApparition(yRnd,ligne)) && (!isCentre(xRnd,yRnd,colonne,ligne))) {
			carte[yRnd][xRnd].setType(Type::Obstacle);
			cptObs ++;
		}
	}
}
	
// ajoute des obstacles en cours de la simulation
void Environnement::addObstacles(int nbObs) {
	int xRnd;
	int yRnd;
	int cptObs = 0;
	int cptWhile = 0;
	
	while ((cptObs < nbObs) && (cptWhile < nbObs*10) ) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		// if ((carte[yRnd][xRnd].getType() == Type::Normal) && (isCentre(xRnd,yRnd,colonne,ligne) == false)) {
		if ((carte[yRnd][xRnd].getInfoAff() == CaseInfoAff::Rien) && (chanceApparition(xRnd,colonne)) && (chanceApparition(yRnd,ligne)) && (!isCentre(xRnd,yRnd,colonne,ligne))) {
			carte[yRnd][xRnd].setType(Type::Obstacle);
			cptObs ++;
		}
	}
}

// ajoute les sources de nourritures initiales
void Environnement::addNourritureInit() {
	int xRnd;
	int yRnd;
	int cptNou = 0;
	int cptWhile = 0;

	while ((cptNou < nbrSrcNourriture) && (cptWhile < nbrSrcNourriture*10) ) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		if ((carte[yRnd][xRnd].getType() == Type::Normal) && (isCentre(xRnd,yRnd,colonne,ligne) == false)) {
			carte[yRnd][xRnd].setType(Type::SrcNourr);
			cptNou ++;
		}
	}
}

// ajoute des sources de nourritures en cours de la simulation
void Environnement::addNourriture(int nbNourr) {
	int xRnd;
	int yRnd;
	int cptNou = 0;
	int cptWhile = 0;

	while ((cptNou < nbNourr) && (cptWhile < nbNourr*10) ) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		if ((carte[yRnd][xRnd].getInfoAff() == CaseInfoAff::Rien) && (isCentre(xRnd,yRnd,colonne,ligne) == false)) {
			carte[yRnd][xRnd].setType(Type::SrcNourr);
			cptNou ++;
		}
		cptWhile++;
	}
}
