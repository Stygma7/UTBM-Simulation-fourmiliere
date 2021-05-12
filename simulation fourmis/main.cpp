#include <iostream>
#include <vector>
#include "Environnement.h"
#include "Fourmilliere.h"
// #include "FourmiGuerriere.h"

using namespace std;

void gotoxy(int x, int y) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}


bool isCentre(int x, int taille) {
	int tailleMax = pow(taille/2,2);
	double chanceApparition = pow((x - taille/2),2);
	double facteur = 0.9 / tailleMax;
	int rand100 = rand()%100 +1;
	int chance = chanceApparition * facteur * 100;

	cout << "tailleMax : " << tailleMax << endl;
	cout << "chanceApparition : " << chanceApparition << endl;
	cout << "facteur : " << facteur << endl;
	cout << "chance : " << chance << endl;
	cout << "rand100 : " << rand100 << endl;

	if (rand100 <= chance) {
		cout << "true";
		return true;
	}
	else {
		cout << "false";
		return false;
	}
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
			cout <<"Entrer le nombre de colonne : ";
			cin >> colonne;
		}

		while((nbObstacles < 0) || (nbObstacles > (ligne*colonne))) {
			cout <<"Entrer le nombre d'obstacles : ";
			cin >> nbObstacles;
		}

		while((nbNourr < 0) || (nbNourr > (ligne*colonne - nbObstacles))) {
			cout <<"Entrer le nombre de nourriture : ";
			cin >> nbNourr;
		}
	} else {
		cout << "\nUtilisation des valeurs par defaut";
		ligne = 50;
		colonne = 100;
		nbObstacles = 1000;
		nbNourr = 500;
	}
	system("cls");
	Environnement e(colonne, ligne, nbObstacles, nbNourr);
	e.afficherCarte();
	
	// FourmiGuerriere warrior(e);
	// FourmiGuerriere warrior2(e);
	// FourmiGuerriere warrior3(e);
	// warrior.display();
	// warrior2.display();
	// warrior3.display();

	Fourmilliere colonie(e,  Position(e.getColonne()/2, e.getLigne()/2));

	for(int i=0; i<50;i++){
		// warrior.update(e);
		// warrior2.update(e);
		// warrior3.update(e);
		// e.update();
		colonie.update(e);
		Sleep(200);
	}

	gotoxy(1,54);
	// srand(time(NULL));

	// int rnd = rand()%100 +1;
	// cout << "rnd:" << rnd << endl;
	// cout << isCentre(rnd,100) << endl;
	return 0;
}