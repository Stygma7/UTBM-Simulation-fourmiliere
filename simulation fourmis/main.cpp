#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include "Environnement.h"

using namespace std;

void gotoxy(int x, int y) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}

int main()
{
	int ligne = 0, colonne = 0, nbObstacles = -1, nbNourr = -1;
	char choix = false;
	cout << "Utiliser les valeurs par defaut (100 colonnes, 50 lignes, 1000 obstacles et 500 nourritures) ? O/N : ";
	cin >> choix;
	if (toupper(choix) == 'N'){
		while(ligne <= 0) {
			cout << "Entrer le nombre de lignes : ";
			cin >> ligne; 
		}
		
		while(colonne <= 0) {
			cout <<"Entrer le nombre de colonnes : ";
			cin >> colonne;
		}

		while((nbObstacles < 0) || (nbObstacles > (ligne*colonne))) {
			cout <<"Entrer le nombre d'obstacles : ";
			cin >> nbObstacles;
		}

		while((nbNourr < 0) || (nbNourr > (ligne*colonne - nbObstacles))) {
			cout <<"Entrer le nombre de sources de nourriture : ";
			cin >> nbNourr;
		}
	} else {
		// ligne = 50;
		// colonne = 100;
		// nbObstacles = 1000;
		// nbNourr = 500;
		ligne = 50;
		colonne = 100;
		nbObstacles = 100;
		nbNourr = 800;
	}
	
	system("cls");
	cout << "Carte des fourmis : \n";
	Environnement e(colonne, ligne, nbObstacles, nbNourr);

	for(int i=0; i<5000;i++){
		e.update();
		Sleep(200);

		if ((i % 10) == 0 && (i != 0)) {
			// e.addObstacles(20);
			// e.addNourriture(100);
		}
	}

	gotoxy(1,54);	

	return 0;
}