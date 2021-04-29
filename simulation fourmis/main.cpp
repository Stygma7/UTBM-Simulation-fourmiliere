#include <iostream>
#include <vector>
#include "Environnement.h"
#include "Case.h"

using namespace std;

int main()
{
	//Environnement e;
	//e.afficherCarte();

	// vector<int> vecteur;
	// vecteur.push_back(10);
	// vecteur.push_back(20);
	// cout << vecteur[0] << "\n";
	// cout << vecteur[1] << "\n";

	vector<vector<Case>> carte;
	vector<Case> ligne;

	srand(time(NULL));
	int rnd;
	for (int y = 0; y < 50; y++)
	{
		for (int x = 0; x < 100; x++)
		{
			rnd = rand();
			// cout << (rnd % 5) << " ";

			if ((rnd % 15) == 0) {
				ligne.push_back(Case(false));
				ligne[x].setDeplacement(false);
			} else {
				ligne.push_back(Case());
				ligne[x].setDeplacement(true);
			}
			// std::cout << "\nligne " << x << " : " << ligne[x].getDeplacement();
		}
		carte.push_back(ligne);
	}

	// Affichage
	cout << "\nCarte des fourmis : \n";
	for (int y = 0; y < 102; y++) {
		cout << "_";
	}
	cout << "\n";

	for (int y = 0; y < 50; y++) {
		cout << "|";
		for (int x = 0; x < 100; x++) {
			if (carte[y][x].getDeplacement() == false) {
				std::cout << "X";
			} else {
				std::cout << " ";
			}
		}
		cout << "|\n";
	}
	
	cout << "|";
	for (int y = 0; y < 100; y++) {
		cout << "_";
	}
	cout << "|";
}