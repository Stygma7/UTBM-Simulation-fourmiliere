#include "FourmiGuerriere.h"
#include <iostream>
#include "caseType.h"

using namespace std;

FourmiGuerriere::FourmiGuerriere(Environnement& env) {
    pos.setX(env.getColonne() / 2);
    pos.setY(env.getLigne() / 2);
    // cout << "\nfourmis posx :" << pos.getX();
    // cout << "\nfourmis posy :" << pos.getY();
}

void dispFourmi(Position p, char c) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = p.getX();
	dwPos.Y = p.getY() +1; // +1 à cause de la premiere ligne de texte
	SetConsoleCursorPosition(hcon, dwPos);
    SetConsoleTextAttribute(hcon, 12);
    cout << c;
    SetConsoleTextAttribute(hcon, 15);
}

void eraseLastPos(Position p) {
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = p.getX();
	dwPos.Y = p.getY() +1;
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
        dispFourmi(pos, '8');
        eraseLastPos(lastPos);
    }
}

void FourmiGuerriere::move(Environnement& env){
    lastPos = pos;

    if (mode == Mode::toHome) {
        moveToHome(env);
    } else {
        moveToFood(env);
    }

    display();
}


void FourmiGuerriere::moveToHome(Environnement& env) {
    if (!cheminToHome.empty()) {
        pos = cheminToHome.back();
        cheminToHome.erase(cheminToHome.end()-1);
    } else {
        dropNourriture();
    }
}

void FourmiGuerriere::moveToFood(Environnement& env) {

    // Récupération des cases voisines
    vector<Case> vecCase;
    vecCase.push_back(env.getCase(pos.getX(), pos.getY() + 1));
    vecCase.push_back(env.getCase(pos.getX() + 1, pos.getY()));
    vecCase.push_back(env.getCase(pos.getX(), pos.getY() - 1));
    vecCase.push_back(env.getCase(pos.getX() - 1, pos.getY()));

    // Stocke la position avant déplacement
    cheminToHome.push_back(pos);

    bool nourrTrouve = false;
    bool bloque = false;
    Case* caseNour = nullptr;

    for(Case & c : vecCase ) {
        if (c.getType() == Type::SrcNourr){
            nourrTrouve = true;
            caseNour = &c;
            break;
        }
    }
    
    if (nourrTrouve) {
        grabNourriture(caseNour->getSrcNour());
    } else {
        while((vecCase.size()) > 0 || bloque) {
            int rndDir = rand() % vecCase.size();
            if (vecCase[rndDir].getDeplacement() && (!isDejaPasseDessus(cheminToHome, vecCase[rndDir].getPos()))) {
                pos.setPos(vecCase[rndDir].getPos());
                break;
            } 
            // if(!vecCase[rndDir].getDeplacement())
            //     cout << "Obstacle";
            // if((isDejaPasseDessus(chemin, vecCase[rndDir].getPos())))
            //     cout << "isDejaPasseDessus";
            
            vecCase.erase(vecCase.begin()+rndDir);
        }
    }
}

void FourmiGuerriere::grabNourriture(SourceNourr src) {
    src.pickNourr();
    setMode(Mode::toHome);
}

void FourmiGuerriere::dropNourriture() {
    setMode(Mode::toFood);
}