#include <iostream>
#include <conio.h>
#include <windows.h>
#include "caseType.h"
#include "FourmiGuerriere.h"

using namespace std;

// FourmiGuerriere::FourmiGuerriere(Environnement* env) {
FourmiGuerriere::FourmiGuerriere(Fourmilliere* col) {
    colonie = col;
    env = colonie->getEnv();
    pos.setX(env->getColonne() / 2);
    pos.setY(env->getLigne() / 2);
    // cout << "\nfourmis posx :" << pos.getX();
    // cout << "\nfourmis posy :" << pos.getY();
}
// FourmiGuerriere::FourmiGuerriere(Fourmilliere& f) {
//     pos.setPos(f.getPos());*
// }

void FourmiGuerriere::dispFourmi() {
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

bool isDejaPasseDessus(vector<Position> vPos, Position pos) {
    if (find(vPos.begin(), vPos.end(), pos) != vPos.end())
        return true;
    else
        return false;
}

void FourmiGuerriere::display(){
    if (!(pos == lastPos)) {
        dispFourmi();
        eraseLastPos();
    }
}

void FourmiGuerriere::update(){
    lastPos = pos;

    if (mode == Mode::toHome) {
        moveToHome();
    } else {
        moveToFood();
    }

    // display();
}


void FourmiGuerriere::moveToHome() {
    if (!cheminToHome.empty()) {
        
        pos = cheminToHome.back();
        cheminToHome.erase(cheminToHome.end()-1);
    } else {
        //  if colonie autour
                dropNourriture();
    }
}

void FourmiGuerriere::moveToFood() {

    // Récupération des cases voisines
    vector<Case*> vecCase;
    // vecCase.push_back(env->getCase(pos.getX(), pos.getY() + 1));
    // vecCase.push_back(env->getCase(pos.getX() + 1, pos.getY()));
    // vecCase.push_back(env->getCase(pos.getX(), pos.getY() - 1));
    // vecCase.push_back(env->getCase(pos.getX() - 1, pos.getY()));
    vecCase.push_back(env->getPtrCase(pos.getX(), pos.getY() + 1));
    vecCase.push_back(env->getPtrCase(pos.getX() + 1, pos.getY()));
    vecCase.push_back(env->getPtrCase(pos.getX(), pos.getY() - 1));
    vecCase.push_back(env->getPtrCase(pos.getX() - 1, pos.getY()));

    // Stocke la position avant déplacement
    cheminToHome.push_back(pos);

    bool nourrTrouve = false;
    bool bloque = false;
    Case* caseNour = nullptr;
    // if (caseNour == nullptr)
    //     cout << "null";

    for(Case* & c : vecCase ) {
        if (c->getType() == Type::SrcNourr){
            nourrTrouve = true;
            caseNour = c;
            break;
        }
    }
    
    if (nourrTrouve) {
        grabNourriture(caseNour);
    } else {
        while(!vecCase.empty() || bloque) {
            int rndDir = rand() % vecCase.size();
            // if (vecCase[rndDir]->getDeplacement() && (!isDejaPasseDessus(cheminToHome, vecCase[rndDir]->getPos()))) {
            if ( vecCase[rndDir]->getDeplacement() ) {
                pos.setPos(vecCase[rndDir]->getPos());
                break;
            } 
            
            vecCase.erase(vecCase.begin()+rndDir);
        }

        // se dépalce uniquement à gauche
        // pos.setPos(getPos().getX()-1,getPos().getY());
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