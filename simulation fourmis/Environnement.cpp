#include <iostream>
#include "Environnement.h"

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
			if (carte[y][x].getDeplacement() == false) {
				cout << "X";
			} else if (carte[y][x].getNourriture() == true) {
				cout << "o";
			} else {
				cout << " ";
			}
		}
		cout << "|\n";
	}
	
	// cout << "|";
	for (int y = 0; y < colonne+2; y++) {
		cout << "-";
	}
	// cout << "|";
}

//Génération
// void Environnement::genererCarte() {
// 	vector<Case> vLigne;
// 	srand(time(NULL));
// 	for (int y = 0; y < ligne; y++) {
// 		for (int x = 0; x < colonne; x++) {
// 			if ((rand() % 15) == 0) {
// 				vLigne.push_back(Case(false));
// 				vLigne[x].setDeplacement(false);
// 			} else {
// 				vLigne.push_back(Case());
// 				vLigne[x].setDeplacement(true);
// 			}
// 		}
// 		carte.push_back(vLigne);
// 	}
// }


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

		if ((carte[yRnd][xRnd].getDeplacement() == true) && carte[yRnd][xRnd].getNourriture() == false) {
			carte[yRnd][xRnd].setDeplacement(false);
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

		if ((carte[yRnd][xRnd].getDeplacement() == true) && carte[yRnd][xRnd].getNourriture() == false) {
			carte[yRnd][xRnd].setNourriture(true);
			cptNou ++;
		}
	}
}
