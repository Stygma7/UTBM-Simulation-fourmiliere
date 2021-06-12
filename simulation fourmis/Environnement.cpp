#include <iostream>
#include <math.h>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Environnement.h"
#include "caseType.h"

using namespace std;

// ----------------- FONCTIONS -----------------------------------------------------------------------------------------------------------------------
bool isCentre(int x, int y, int colonne, int ligne) {
// bool isCentre(int x, int taille) {
	int offset = 5;
	if ( (x >= (colonne/2 -offset)) && (x <= (colonne/2 +offset)) && (y >= (ligne/2 -offset)) && (y <= (ligne/2 +offset)) )
		return true;
	else
		return false;
}

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
	genererCarte();
	fourmilliere = new Fourmilliere(this, Position(colonne/2, ligne/2));
	getPtrCase(colonne/2, ligne/2)->addAffichage(CaseInfoAff::Fourmilliere);
	showInfosInit();
}


Environnement::~Environnement() {
	for (Pheromone* & ph : listPheroToFood) {
		delete(ph);
	}
	for (Pheromone* & ph : listPheroToHome) {
		delete(ph);
	}
	
	delete(fourmilliere);
}


// ----------------- UPDATE ------------------------------------------------------------------------------------------------------------------------------
void Environnement::update() {
	// listPosToErase.clear();
	// update pheromoneToFood
	for(int i=0; i<listPheroToFood.size();  i++) {
		listPheroToFood[i]->update();
		if (listPheroToFood[i]->getAmount() <= 0) {
			// listPosToErase.push_back(listPheroToFood[i]->getPos());
			carte[listPheroToFood[i]->getPos().getY()][listPheroToFood[i]->getPos().getX()].deleteAffichage(CaseInfoAff::PheroFood);
			carte[listPheroToFood[i]->getPos().getY()][listPheroToFood[i]->getPos().getX()].setPheroToFood(nullptr);
			delete listPheroToFood[i];
			listPheroToFood.erase(listPheroToFood.begin() +i);
			i--;
		}
	}

	// update pheromoneToHome
	for(int i=0; i<listPheroToHome.size();  i++) {
		listPheroToHome[i]->update();
		if (listPheroToHome[i]->getAmount() <= 0) {
			// listPosToErase.push_back(listPheroToHome[i]->getPos());
			carte[listPheroToHome[i]->getPos().getY()][listPheroToHome[i]->getPos().getX()].deleteAffichage(CaseInfoAff::PheroHome);
			carte[listPheroToHome[i]->getPos().getY()][listPheroToHome[i]->getPos().getX()].setPheroToHome(nullptr);
			delete listPheroToHome[i];
			listPheroToHome.erase(listPheroToHome.begin() +i);
			i--;
		} 
	}
	// update fourmilliere + fourmis
	fourmilliere->update();


	// for (vector<Pheromone*>::iterator it = listPheroToFood.begin() ; it != listPheroToFood.end(); it++) {
	// 	(*it)->update();
	// 	if ((*it)->getAmount() < 0) {
	// 		carte[(*it)->getPos().getY()][(*it)->getPos().getX()].setPheroToFood(nullptr);
	// 		delete (*it);
	// 		listPheroToFood.erase(it);
	// 	}
	// }

	// for (vector<Pheromone*>::iterator it = listPheroToHome.begin() ; it != listPheroToHome.end(); it++) {
	// 	(*it)->update();
	// 	if ((*it)->getAmount() < 0) {
	// 		carte[(*it)->getPos().getY()][(*it)->getPos().getX()].setPheroToFood(nullptr);
	// 		delete (*it);
	// 		listPheroToHome.erase(it);
	// 	}
	// }

	nbrTour++;

	updateAffichage();
}


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
void Environnement::updateAffichage() {
	// fourmilliere->EraseAnts();
	// dispPhero();
	// fourmilliere->DispAnts();
	// // dispFourmilliere();
	
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

		case CaseInfoAff::Fourmilliere:
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

// void Environnement::dispPhero() {
// 	for(Position & pos : listPosToErase) {
// 		affichageTxtColor(pos, " ", 9);
// 	}

// 	for(Pheromone* & ph : listPheroToFood) {
// 		affichageTxtColor(ph->getPos(), ".", 14);
// 	}

// 	for(Pheromone* & ph : listPheroToHome) {
// 		affichageTxtColor(ph->getPos(), ".", 9);
// 	}
// }

// void Environnement::dispFourmilliere() {
//     affichageTxtColor(fourmilliere->getPos(), "O", 6);
// }

//Affichage
void Environnement::showInfosInit() {
    affichageTxtColor(Position(colonne + affOffset , 2), "Parametres initiaux :", 15);
    affichageTxtColor(Position(colonne + affOffset , 3), "Colonnes  : " + to_string(getColonne()), 15);
    affichageTxtColor(Position(colonne + affOffset , 4), "Lignes    : " + to_string(getLigne()), 15);
    affichageTxtColor(Position(colonne + affOffset , 5), "Obstacles : " + to_string(getNbrObstacles()), 15);
    affichageTxtColor(Position(colonne + affOffset , 6), "Src nourr : " + to_string(getNbrSrcNourriture()), 10);
}

void Environnement::showInfos() {
	int cptLigne = 0;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Tour : " + to_string(nbrTour), 11);

	cptLigne = 8;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Colonie 1 :", 15);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Population : " + to_string(fourmilliere->getPop()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Qte nourr : " + to_string(fourmilliere->getFood()) + "  ", 10);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nbr reine : " + to_string(fourmilliere->getNbrReine()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nbr oeufs : " + to_string(fourmilliere->getNbrOeufs()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nbr larves : " + to_string(fourmilliere->getNbrLarves()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nbr fourmis ouv : " + to_string(fourmilliere->getNbrFourmiOuvrieres()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nbr fourmis gue : " + to_string(fourmilliere->getNbrFourmiGuerrieres()) + "  ", 12);
	cptLigne++;
    affichageTxtColor(Position(colonne + affOffset , cptLigne), "Nbr phero tot : " + to_string(listPheroToHome.size() + listPheroToFood.size()) + "  ", 9);
	// cptLigne++;
    // affichageTxtColor(Position(colonne + affOffset , cptLigne), "liste aff : " + to_string(listAffichage.size()) + "   ", 15);


    // affichageTxtColor(Position(104,22), "toHome", 15);
	// int cpt = 0;
	// for (Pheromone* & ph : listPheroToHome) {
    // 	affichageTxtColor(Position(104,23+cpt), "ph " + to_string(cpt) + " : " + to_string(ph->getAmount()) + " ", 15);
	// 	cpt++;
	// }

    // affichageTxtColor(Position(116,22), "toFood", 15);
	// cpt = 0;
	// for (Pheromone* & ph : listPheroToFood) {
    // 	affichageTxtColor(Position(116,23+cpt), "ph " + to_string(cpt) + " : " + to_string(ph->getAmount()) + " ", 15);
	// 	cpt++;
	// }
}

// void Environnement::afficherCarteInit() {

// 	for (int y = 0; y < ligne+2; y++) {
// 		for (int x = 0; x < colonne+2; x++) {
// 			switch (carte[y][x].getType())
// 			{
// 			case Type::SrcNourr:
// 				affichageTxtColor(carte[y][x].getPos(), "o", 2);
// 				break;
// 			case Type::Obstacle:
// 				affichageTxtColor(carte[y][x].getPos(), "X", 15);
// 				break;
// 			default:
// 				cout << " ";
// 				break;
// 			}
// 		}
// 		cout << "\n";
// 	}
	
// 	// dispFourmilliere();
// 	showInfosInit();
// }

void Environnement::addCaseAffichage(Case* c) {
	listAffichage.insert(c);
}

// ----------------- GENERATION ------------------------------------------------------------------------------------------------------------------------------
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

void Environnement::addObstaclesInit() {
	int xRnd;
	int yRnd;
	int cptObs = 0;

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
	
	while (cptObs < nbrObstacles) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		// if ((carte[yRnd][xRnd].getType() == Type::Normal) && (isCentre(xRnd,yRnd,colonne,ligne) == false)) {
		if ((carte[yRnd][xRnd].getType() == Type::Normal) && (chanceApparition(xRnd,colonne)) && (chanceApparition(yRnd,ligne)) && (!isCentre(xRnd,yRnd,colonne,ligne))) {
			carte[yRnd][xRnd].setType(Type::Obstacle);
			cptObs ++;
		}
	}
}
	
void Environnement::addObstacles(int nbObs) {
	int xRnd;
	int yRnd;
	int cptObs = 0;
	
	while (cptObs < nbObs) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		// if ((carte[yRnd][xRnd].getType() == Type::Normal) && (isCentre(xRnd,yRnd,colonne,ligne) == false)) {
		if ((carte[yRnd][xRnd].getType() == Type::Normal) && (chanceApparition(xRnd,colonne)) && (chanceApparition(yRnd,ligne)) && (!isCentre(xRnd,yRnd,colonne,ligne))) {
			carte[yRnd][xRnd].setType(Type::Obstacle);
			cptObs ++;
		}
	}
}

void Environnement::addNourritureInit() {
	int xRnd;
	int yRnd;
	int cptNou = 0;
	while (cptNou < nbrSrcNourriture) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		if ((carte[yRnd][xRnd].getType() == Type::Normal) && (isCentre(xRnd,yRnd,colonne,ligne) == false)) {
			carte[yRnd][xRnd].setType(Type::SrcNourr);
			cptNou ++;
		}
	}
}
