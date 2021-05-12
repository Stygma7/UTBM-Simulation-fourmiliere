#include <iostream>
#include "Environnement.h"
// #include "caseType.h"
#include <math.h>

using namespace std;

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

// Cosntructeurs
Environnement::Environnement() {
	// fourmilliere = new Fourmilliere(*this, Position( getColonne()/2, getLigne()/2 ));
	genererCarte();
}
Environnement::Environnement(int x, int y, int nbObstacles, int nbNourriture) {
	setColonne(x);
	setLigne(y);	
	setnbrObstacles(nbObstacles);
	setnbrSrcNourriture(nbNourriture);
	// fourmilliere = new Fourmilliere(*this, Position( getColonne()/2, getLigne()/2 ));
	genererCarte();
}

void Environnement::update() {
	// fourmilliere->update(*this);
}

//Affichage
void Environnement::afficherInfos() {
	cout << "Colonnes : " << this->getColonne() << "\n";
	cout << "Lignes : " << this->getLigne() << "\n";
	cout << "Nombre d'obstacles : " << this->getnbrObstacles() << "\n";
	cout << "Nombre de source de nourriture : " << this->getnbrSrcNourriture() << "\n";
	// cout << "Taux d'evaporation des Pheromones : " << this->gettauxEvapPheromone() << "\n";
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
void affichageTxtColor(Position p, char c, int color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = p.getX();
	dwPos.Y = p.getY() +1; // +1 à cause de la premiere ligne de texte
	SetConsoleCursorPosition(hcon, dwPos);
    SetConsoleTextAttribute(hcon, color);
    cout << c;
    SetConsoleTextAttribute(hcon, 15);
}

void Environnement::afficherCarte() {
	cout << "Carte des fourmis : \n";
	// for (int y = 0; y < colonne+2; y++) {
	// 	cout << "-";
	// }
	// cout << "\n";

	for (int y = 0; y < ligne+2; y++) {
		// cout << "|";
		for (int x = 0; x < colonne+2; x++) {
			switch (carte[y][x].getType())
			{
			case Type::SrcNourr:
				// cout << "o";
				affichageTxtColor(carte[y][x].getPos(), 'o', 2);
				break;
			case Type::Obstacle:
				// cout << "X";
				affichageTxtColor(carte[y][x].getPos(), 'X', 15);
				break;
			default:
				cout << " ";
				break;
			}
		}
		cout << "\n";
	}
	
	// for (int y = 0; y < colonne+2; y++) {
	// 	cout << "-";
	// }
}


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
		carte[0][i].setObstacle();
		carte[ligne+1][i].setObstacle();
	}
	for (int i = 0; i < ligne+2; i++)
	{
		carte[i][0].setObstacle();
		carte[i][colonne+1].setObstacle();
	}
	
	while (cptObs < nbrObstacles) {
		xRnd = rand() % colonne +1;
		yRnd = rand() % ligne +1;

		// if ((carte[yRnd][xRnd].getType() == Type::Normal) && (isCentre(xRnd,yRnd,colonne,ligne) == false)) {
		if ((carte[yRnd][xRnd].getType() == Type::Normal) && (chanceApparition(xRnd,colonne)) && (chanceApparition(yRnd,ligne)) && (!isCentre(xRnd,yRnd,colonne,ligne))) {
			carte[yRnd][xRnd].setObstacle();
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
			carte[yRnd][xRnd].setSrcNourr();
			cptNou ++;
		}
	}
}
