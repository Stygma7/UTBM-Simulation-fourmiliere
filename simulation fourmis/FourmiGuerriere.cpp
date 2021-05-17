#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include "caseType.h"
#include "FourmiGuerriere.h"

using namespace std;

void affichageTxtColor2(Position p, string str, int color) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = p.getX();
	dwPos.Y = p.getY() +1; // +1 à cause de la premiere ligne de texte
	SetConsoleCursorPosition(hcon, dwPos);
    SetConsoleTextAttribute(hcon, color);
    cout << str;
    SetConsoleTextAttribute(hcon, 15);
}

bool isDejaPasseDessus(vector<Position> vPos, Position pos) {
    if (find(vPos.begin(), vPos.end(), pos) != vPos.end())
        return true;
    else
        return false;
}

FourmiGuerriere::FourmiGuerriere(Fourmilliere* col) {
    colonie = col;
    env = colonie->getEnv();
    pos.setX(env->getColonne() / 2);
    pos.setY(env->getLigne() / 2);
}

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

void FourmiGuerriere::update(){
    lastPos = pos;

    if (mode == Mode::toHome) {
        moveToHome();
    } else {
        moveToFood();
    }
}


void FourmiGuerriere::moveToHome() {
    env->addPhero(pos);
    
    if (pos.isNextTo(colonie->getPos())) {
        pos = colonie->getPos();
        cheminToHome.clear();
    } else if (cheminToHome.empty()) {
        dropNourriture();
    } else {
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

    bool nourrTrouve = false;
    Case* caseNour = nullptr;
    
    // On cherche une source de nourriture
    for(Case* & c : vecCase ) {
        if (c->getType() == Type::SrcNourr) {
            nourrTrouve = true;
            caseNour = c;
            break;
        }
    }

    if (nourrTrouve) {
        grabNourriture(caseNour);
    } else {
        // On vérifie si on trouve de la pheromone
        // for(Case* & c : vecCase ) {
        // if (c->getType() == Type::SrcNourr) {
        //     nourrTrouve = true;
        //     caseNour = c;
        //     break;
        //     }
        // }

        while(!vecCase.empty()) {
            
            int rndDir = rand() % vecCase.size();
            // if (vecCase[rndDir]->getDeplacement() && (!isDejaPasseDessus(cheminToHome, vecCase[rndDir]->getPos()))) {
            if ( vecCase[rndDir]->getDeplacement() ) {
                pos.setPos(vecCase[rndDir]->getPos());
                break;
            } 
            
            vecCase.erase(vecCase.begin()+rndDir);
        }

        // ---POUR TEST--- se déplace uniquement à gauche
        // pos.setPos(getPos().getX()+1,getPos().getY());
    }
}

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