#include <iostream>
#include "Case.h"
#include <conio.h>
#include <windows.h>

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
Case::Case() {
    // par défaut, case normale
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
void Case::pickNourr() {
    srcNour->pickNourr();
    if (srcNour->getquantite() <= 0) {
        delete srcNour;
        srcNour = nullptr;
        setType(Type::Normal);
        
        affichageTxt(pos);
    }
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

// true : pheromone dispo, false : pas de pheromone
// bool Case::isTherePhero(Pheromone* ph) {
//     if (ph == nullptr)
//         return false;

//     if (ph->getAmount() > 0)
//         return true;
//     else
//         return false;
// }

// bool Case::isTherePheroToFood() {
//     return isTherePhero(pheroToFood);
// }
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

// ajoute de la pheromone
// void Case::addPheroToFood(int amount) {
//     pheroToFood->addAmount(amount);
// }

// ajoute de la phero seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Case::addReducPheroToFood(int reduc) {
    pheroToFood->addReducAmount(reduc);
}

void Case::setPheroToHome(Pheromone* ph) {
    pheroToHome = ph;
}

// ajoute de la pheromone
// void Case::addPheroToHome(int amount) {
//     pheroToHome->addAmount(amount);
// }

// ajoute de la phero seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Case::addReducPheroToHome(int reduc) {
    pheroToHome->addReducAmount(reduc);
}