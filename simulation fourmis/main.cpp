#include <iostream>
#include <vector>
#include "Environnement.h"
#include "Case.h"

using namespace std;

int main()
{
	int ligne = 0, colonne = 0, nbObstacles = -1, nbNourr = -1;
	char choix = false;
	cout << "Utiliser les valeurs par defaut (100 colonnes, 50 lignes, 1000 obstacles et 500 nourritures) ? O/N ";
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
	
	Environnement e(colonne, ligne, nbObstacles, nbNourr);
	e.afficherCarte();
}