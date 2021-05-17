#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "caseType.h"
#include "FourmiGuerriere.h"

using namespace std;

// --------------- FONCTIONS ----------------------------------------------------------------------------------------
bool isDejaPasseDessus(vector<Position> vPos, Position pos) {
    if (find(vPos.begin(), vPos.end(), pos) != vPos.end())
        return true;
    else
        return false;
}

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
FourmiGuerriere::FourmiGuerriere(Fourmilliere* col) {
    colonie = col;
    env = colonie->getEnv();
    pos.setX(env->getColonne() / 2);
    pos.setY(env->getLigne() / 2);
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
void FourmiGuerriere::update(){
    lastPos = pos;

    if (mode == Mode::toHome) {
        moveToHome();
    } else {
        moveToFood();
    }
}

// --------------- DEPLACEMENT --------------------------------------------------------------------------------------
void FourmiGuerriere::moveToHome() {
    if (pos.isNextTo(colonie->getPos())) {
        env->addPhero(pos);
        pos = colonie->getPos();
        cheminToHome.clear();
    } else if (cheminToHome.empty()) {
        dropNourriture();
    } else {
        env->addPhero(pos);
        pos = cheminToHome.back();
        cheminToHome.erase(cheminToHome.end()-1);
    }
}

void FourmiGuerriere::moveToFood() {

    // Récupération des cases voisines
    vecCase.clear();
    vecCase.push_back(env->getPtrCase(pos.getX(), pos.getY() + 1));
    vecCase.push_back(env->getPtrCase(pos.getX() + 1, pos.getY()));
    vecCase.push_back(env->getPtrCase(pos.getX(), pos.getY() - 1));
    vecCase.push_back(env->getPtrCase(pos.getX() - 1, pos.getY()));

    // Stocke la position avant déplacement
    cheminToHome.push_back(pos);

    Case* casePhero = nullptr;
    Case* caseNour = nullptr;
    
    // On vérifie si il y a de la nourriture ou de la phéromone à proximité
    for(Case* & c : vecCase ) {
        if (c->isTherePhero()) {
            // if (casePhero == nullptr)
            //     casePhero = c;
            // else if (c->getPheromone()->getAmount() < casePhero->getPheromone()->getAmount())
                casePhero = c;
        }
        if (c->getType() == Type::SrcNourr) {
            caseNour = c;
        }
    }

    // S'il y a de la nourriture, on en prend
    if (caseNour != nullptr)
        grabNourriture(caseNour);

    // Sinon on suit la pheromone
    else if (casePhero != nullptr) {
        pos.setPos(casePhero->getPos());

    // Sinon on continue de chercher aléatoirement
    } else {
        while(!vecCase.empty()) {
            int rndDir = rand() % vecCase.size();
            // if (vecCase[rndDir]->getDeplacement() && (!isDejaPasseDessus(cheminToHome, vecCase[rndDir]->getPos()))) {
            if ( vecCase[rndDir]->getDeplacement() ) {
                pos.setPos(vecCase[rndDir]->getPos());
                break;
            } 
            
            vecCase.erase(vecCase.begin()+rndDir);
        }

        // ---POUR TEST--- se déplace uniquement à gauche (écrase obstacles)
        // pos.setPos(getPos().getX()-1,getPos().getY());
    }
}

// --------------- GESTION NOURRITURE -------------------------------------------------------------------------------
void FourmiGuerriere::grabNourriture(Case* caseNour) {
    caseNour->pickNourr();
    setMode(Mode::toHome);
}

void FourmiGuerriere::dropNourriture() {
    if (!colonie->isFoodStockFull()) {
        colonie->addFood(1);
        setMode(Mode::toFood);
    }
}

// --------------- AFFICHAGE ----------------------------------------------------------------------------------------
void FourmiGuerriere::display() {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = pos.getX();
	dwPos.Y = pos.getY() +1; // +1 à cause de la premiere ligne de texte
	SetConsoleCursorPosition(hcon, dwPos);
    SetConsoleTextAttribute(hcon, 12);
    cout << '8';
    SetConsoleTextAttribute(hcon, 15);
}

void FourmiGuerriere::eraseLastPos() {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = lastPos.getX();
	dwPos.Y = lastPos.getY() +1;
	SetConsoleCursorPosition(hcon, dwPos);
    SetConsoleTextAttribute(hcon, 15);
    cout << " ";
}