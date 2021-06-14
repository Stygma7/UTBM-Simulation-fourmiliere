#ifndef __CASEINFOAFF_H__
#define __CASEINFOAFF_H__

// Renseigne sur les éléments présents sur une case pour mieux gérer l'affichage
enum class CaseInfoAff : int
{
	Rien = 0,

	PheroHome = 1,
	PheroFood = 2,

	Fourmi = 3, 

	SrcNourr = 4,
	Obstacle = 5, 
	Fourmiliere = 6,
};

#endif