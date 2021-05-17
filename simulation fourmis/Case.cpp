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

Case::Case() {
    // par défaut, case sans obstacle/nourriture
    setType(Type::Normal);
}

// Case::~Case() {
//     delete(srcNour);
// }


// void Case::updateType() {
//     if (deplacement)
//         type = Type::Normal;
//     else if (srcNour != nullptr)
//         type = Type::SrcNourr;
//     else 
//         type = Type::Obstacle;
// }

// void Case::setSrcNourr() {
//     if (srcNour == nullptr);
//         srcNour = new SourceNourr();
//     deplacement = false;
//     updateType(); 
// }

// void Case::ajoutPheromone(Pheromone* phero) {
//     pheromone = phero;
// }

// void Case::setObstacle() { 
//     deplacement = false;
//     updateType(); 
// }

void Case::setPos(Position pos) {
    this->pos = pos;
}

void Case::setPos(int x, int y) {
    pos.setX(x);
    pos.setY(y);
}

void Case::pickNourr() {
    srcNour->pickNourr();
    if (srcNour->getquantite() <= 0) {
        delete srcNour;
        srcNour = nullptr;
        setType(Type::Normal);
        
        affichageTxt(pos);
    }
}

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

bool Case::isTherePhero() {
    if (phero == nullptr) {
        return false;  
    } else {
        if (phero->getAmount() > 0) 
            return true;
        else
            return false;  
    }  
}

void Case::setPhero(Pheromone* ph) {
    phero = ph;
}

void Case::addPhero() {
    phero->addAmount();
}