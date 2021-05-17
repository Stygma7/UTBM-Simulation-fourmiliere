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
	int tailleMax = pow(taille/2,2);
	double chanceApparition = pow((x - taille/2),2);
	double facteur = 0.9 / tailleMax;
	int rand100 = rand()%100 +1;
	int chance = chanceApparition * facteur * 100;

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
Environnement::Environnement() {
	genererCarte();
}
Environnement::Environnement(int x, int y, int nbObstacles, int nbNourriture) {
	setColonne(x);
	setLigne(y);	
	setnbrObstacles(nbObstacles);
	setnbrSrcNourriture(nbNourriture);
	genererCarte();
	fourmilliere = new Fourmilliere(this, Position(getColonne()/2, getLigne()/2));
}


// ----------------- UPDATE ------------------------------------------------------------------------------------------------------------------------------
void Environnement::update() {
	// update fourmilliere + fourmis
	fourmilliere->update();

	// update pheromone
	for(int i=0; i<listPhero.size();  i++) {
		listPhero[i]->update();
		if (listPhero[i]->getAmount() < 0) {
			carte[listPhero[i]->getPos().getY()][listPhero[i]->getPos().getX()].setPhero(nullptr);
			delete listPhero[i];
			listPhero.erase(listPhero.begin() +i);
		}
	}

	nbrTour++;

	updateDisp();
}

void Environnement::addPhero(Position pos) {
	if (carte[pos.getY()][pos.getX()].getPheromone() == nullptr) {
		Pheromone* ph = new Pheromone(pos);
		listPhero.push_back(ph);
		carte[pos.getY()][pos.getX()].setPhero(ph);
	} else {
		carte[pos.getY()][pos.getX()].addPhero();
	}

}


// ----------------- DISPLAY ------------------------------------------------------------------------------------------------------------------------------
void Environnement::updateDisp() {
	fourmilliere->EraseAnts();
	dispPhero();
	fourmilliere->DispAnts();
	// dispFourmilliere();
	
	showInfos();
}

void Environnement::dispPhero() {
	for(int i=0; i<listPhero.size();  i++) {
		if ( listPhero.at(i)->getAmount() >0 )
			affichageTxtColor(listPhero.at(i)->getPos(), ".", 14);
		else
			affichageTxtColor(listPhero.at(i)->getPos(), " ", 14);
	}
}

void Environnement::dispFourmilliere() {
    affichageTxtColor(fourmilliere->getPos(), "O", 6);
}

//Affichage
void Environnement::showInfosInit() {
    affichageTxtColor(Position(getColonne() + affOffset , 2), "Colonnes  : " + to_string(getColonne()), 15);
    affichageTxtColor(Position(getColonne() + affOffset , 3), "Lignes    : " + to_string(getLigne()), 15);
    affichageTxtColor(Position(getColonne() + affOffset , 4), "Obstacles : " + to_string(getNbrObstacles()), 15);
    affichageTxtColor(Position(getColonne() + affOffset , 5), "Src nourr : " + to_string(getNbrSrcNourriture()), 10);
	
}

void Environnement::showInfos() {
    affichageTxtColor(Position(getColonne() + affOffset , 0), "Tour : " + to_string(nbrTour), 11);
    affichageTxtColor(Position(getColonne() + affOffset , 7), "Qte nourr   : " + to_string(fourmilliere->getFood()), 10);
    affichageTxtColor(Position(getColonne() + affOffset , 8), "Nbr fourmis : " + to_string(fourmilliere->getNbrAnts()), 12);
}

void Environnement::afficherCarteInit() {

	for (int y = 0; y < ligne+2; y++) {
		// cout << "|";
		for (int x = 0; x < colonne+2; x++) {
			switch (carte[y][x].getType())
			{
			case Type::SrcNourr:
				// cout << "o";
				affichageTxtColor(carte[y][x].getPos(), "o", 2);
				break;
			case Type::Obstacle:
				// cout << "X";
				affichageTxtColor(carte[y][x].getPos(), "X", 15);
				break;
			default:
				cout << " ";
				break;
			}
		}
		cout << "\n";
	}
	
	dispFourmilliere();
	showInfosInit();
}

// ----------------- GENERATION ------------------------------------------------------------------------------------------------------------------------------
void Environnement::genererCarte() {
	vector<Case> vLigne;
	for (int y = 0; y < ligne+2; y++) {
		for (int x = 0; x < colonne+2; x++) {
			vLigne.push_back(Case());
			vLigne[x].setPos(x, y);
		}
		carte.push_back(vLigne);
	}

	srand(time(NULL));
	ajoutObstacles();
	ajoutNourriture();
}

void Environnement::ajoutObstacles() {
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

void Environnement::ajoutNourriture() {
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
