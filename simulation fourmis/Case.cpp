#include <iostream>
#include <conio.h>
#include <windows.h>
#include "Environnement.h"
#include "Case.h"

void affichageTxt(Position p) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = p.getX();
	dwPos.Y = p.getY() +1; // +1 à cause de la premiere ligne de texte
	SetConsoleCursorPosition(hcon, dwPos);
    std::cout << ' ';
    SetConsoleTextAttribute(hcon, 15);
}

// Constructeur
// Case::Case() {
//     setType(Type::Normal);
// }

Case::Case(Environnement* e) {
    env = e;
    setType(Type::Normal);
}


void Case::setPos(Position pos) {
    this->pos = pos;
}

void Case::setPos(int x, int y) {
    pos.setX(x);
    pos.setY(y);
}

// réduit la quantité de nourriture sur la source associée
int Case::pickNourr(int nourr) {
    int tmp = srcNour->pickNourr(nourr);
    if (srcNour->getquantite() <= 0) {
        delete srcNour;
        srcNour = nullptr;
        setType(Type::Normal);
        
        affichageTxt(pos);
    }
    return tmp;
}

// change le type de la case
void Case::setType(Type type) {
    switch (type)
    {
    case Type::Obstacle:
        deplacement = false;
        break;
    case Type::SrcNourr:
        deplacement = false;
        if (srcNour == nullptr)
            srcNour = new SourceNourr();
        break;

    default:
        this->type = Type::Normal;
        deplacement = true;
        break;
    }

    this->type = type;
}

bool Case::isTherePheroToFood() {
    if (pheroToFood == nullptr)
        return false;

    if (pheroToFood->getAmount() > 0)
        return true;
    else
        return false;
}

bool Case::isTherePheroToHome() {
    // return isTherePhero(pheroToHome);
    if (pheroToHome == nullptr)
        return false;

    if (pheroToHome->getAmount() > 0)
        return true;
    else
        return false;
}

void Case::setPheroToFood(Pheromone* ph) {
    pheroToFood = ph;
}

void Case::setPheroToHome(Pheromone* ph) {
    pheroToHome = ph;
}

// ajoute de la phero seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Case::addReducPheroToFood(int reduc) {
    pheroToFood->addReducAmount(reduc);
}

// ajoute de la phero seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Case::addReducPheroToHome(int reduc) {
    pheroToHome->addReducAmount(reduc);
}
