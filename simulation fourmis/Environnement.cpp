#include <iostream>
#include "Environnement.h"
#include "caseType.h"

using namespace std;

// Cosntructeurs
Environnement::Environnement() {
	genererCarte();
}
Environnement::Environnement(int x, int y, int nbObstacles, int nbNourriture) {
	setColonne(x);
	setLigne(y);
	setnbrObstacles(nbObstacles);
	setnbrSrcNourriture(nbNourriture);
	genererCarte();
}

//Affichage
void Environnement::afficherInfos() {
	cout << "Colonnes : " << this->getColonne() << "\n";
	cout << "Lignes : " << this->getLigne() << "\n";
	cout << "Nombre d'obstacles : " << this->getnbrObstacles() << "\n";
	cout << "Nombre de source de nourriture : " << this->getnbrSrcNourriture() << "\n";
	cout << "Taux d'evaporation des Pheromones : " << this->gettauxEvapPheromone() << "\n";
}

void Environnement::afficherCarte() {
	cout << "\nCarte des fourmis : \n";
	for (int y = 0; y < colonne+2; y++) {
		cout << "-";
	}
	cout << "\n";

	for (int y = 0; y < ligne; y++) {
		cout << "|";
		for (int x = 0; x < colonne; x++) {
			switch (carte[y][x].getType())
			{
			case Type::SrcNourr:
				cout << "o";
				break;
			case Type::Obstacle:
				cout << "X";
				break;
			default:
				cout << " ";
				break;
			}
		}
		cout << "|\n";
	}
	
	for (int y = 0; y < colonne+2; y++) {
		cout << "-";
	}
}


void Environnement::genererCarte() {
	vector<Case> vLigne;
	for (int y = 0; y < ligne; y++) {
		for (int x = 0; x < colonne; x++) {
			vLigne.push_back(Case());
		}
		carte.push_back(vLigne);
	}

	ajoutObstacles();
	ajoutNourriture();
}

void Environnement::ajoutObstacles() {
	int xRnd;
	int yRnd;
	srand(time(NULL));
	int cptObs = 0;
	while (cptObs < nbrObstacles) {
		xRnd = rand() % colonne;
		yRnd = rand() % ligne;

		if (carte[yRnd][xRnd].getType() == Type::Normal) {
			carte[yRnd][xRnd].setObstacle();
			cptObs ++;
		}
	}
}

void Environnement::ajoutNourriture() {
	int xRnd;
	int yRnd;
	srand(time(NULL));
	int cptNou = 0;
	while (cptNou < nbrSrcNourriture) {
		xRnd = rand() % colonne;
		yRnd = rand() % ligne;

		if (carte[yRnd][xRnd].getType() == Type::Normal) {
			carte[yRnd][xRnd].setSrcNourr();
			cptNou ++;
		}
	}
}
