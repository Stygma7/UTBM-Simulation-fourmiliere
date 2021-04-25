#include "Case.h"

//Consrtucteurs
Case::Case() : deplacement(true) {}
Case::Case(bool deplacement) : deplacement(deplacement) {}

//Getters
//int Case::getPosX() { return this->posX; }
//int Case::getPosY() { return this->posY; }
bool Case::getDeplacement() { return this->deplacement; }

//Setters
//void Case::setPosX(int posX) { this->posX = posX; }
//void Case::setPosY(int posY) { this->posY = posY; }
void Case::setDeplacement(bool deplacement) { this->deplacement = deplacement; }
;