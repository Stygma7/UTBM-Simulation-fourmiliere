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

// --------------- FONCTIONS ----------------------------------------------------------------------------------------
// bool isDejaPasseDessus(vector<Position> vPos, Position pos) {
//     if (find(vPos.begin(), vPos.end(), pos) != vPos.end())
//         return true;
//     else
//         return false;
// }

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
FourmiGuerriere::FourmiGuerriere(Fourmilliere* col) {
    MAX_VIE = 100;
    vie = MAX_VIE;
    seuilRavitaillement = 40;
    colonie = col;
    env = colonie->getEnv();
    pos = col->getPos();
    lastPos = pos;
    consoNourriture = 3;
}

FourmiGuerriere::FourmiGuerriere(Fourmilliere* col, int vie_) {
    MAX_VIE = 100;
    vie = vie_;
    seuilRavitaillement = 40;
    colonie = col;
    env = colonie->getEnv();
    pos = col->getPos();
    lastPos = pos;
    consoNourriture = 3;
}


// --------------- UPDATE -------------------------------------------------------------------------------------------
// void FourmiGuerriere::update(){
void FourmiGuerriere::update() {
    // Récupération des cases voisines
    aroundCase.clear();
    aroundCase.push_back(env->getPtrCase(pos.getX(), pos.getY() + 1)); // Haut
    aroundCase.push_back(env->getPtrCase(pos.getX() + 1, pos.getY())); // Droite
    aroundCase.push_back(env->getPtrCase(pos.getX(), pos.getY() - 1)); // Bas
    aroundCase.push_back(env->getPtrCase(pos.getX() - 1, pos.getY())); // Gauche

    // lastPos = tempPos;
    // tempPos=pos;
    // lastPos = pos;

    direction.update();
    if (vie < seuilRavitaillement || mode == Mode::toHome) {
        moveToHome();
    } else {
        moveToFood();
    }

    vie -= perteVie;
    // if (vie <= 0)
    //     erasePos();

    if (pos != colonie->getPos()) 
        cptTour++;
        
    // affichageTxtColor2(Position(104,14), "vie : " + to_string(vie) + " " , 15);
    // if (mode == Mode::toHome)
    //     affichageTxtColor2(Position(104,14), "toHome " + to_string(Pheromone::AMOUNT_MAX - 2*cptTour) + " ", 15);
    // else
    //     affichageTxtColor2(Position(104,14), "toFood " + to_string(Pheromone::AMOUNT_MAX - 2*cptTour) + " ", 15);
    // affichageTxtColor2(Position(104,15), "pos X : " + to_string(pos.getX()) + " Y : " + to_string(pos.getY()) + " ", 15);
    // affichageTxtColor2(Position(104,16), "las X : " + to_string(lastPos.getX()) + " Y : " + to_string(lastPos.getY()) + " ", 15);


    // Case* ptrCase;

    // ptrCase = env->getPtrCase(pos.getX(), pos.getY());
    // affichageTxtColor2(Position(104,17), "case fourmi ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,17), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,17), "          " , 15);

    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,17), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,17), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX(), pos.getY()-1);
    // affichageTxtColor2(Position(104,18), "case haut ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,18), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,18), "          " , 15);

    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,18), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,18), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX()+1, pos.getY());
    // affichageTxtColor2(Position(104,19), "case droite ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,19), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,19), "          " , 15);

    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,19), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,19), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX(), pos.getY()+1);
    // affichageTxtColor2(Position(104,20), "case bas ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,20), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,20), "          " , 15);
    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,20), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,20), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX()-1, pos.getY());
    // affichageTxtColor2(Position(104,21), "case gauche ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,21), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,21), "          " , 15);
    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,21), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,21), "          " , 15);

}


// --------------- DEPLACEMENT --------------------------------------------------------------------------------------
void FourmiGuerriere::moveToHome() {
    if (pos == colonie->getPos()) {
        if (nourr > 0) {
            dropNourriture();
        }
        
        if (vie < seuilRavitaillement) {
            eat();
        }
        cptTour = 0;

    } else {
        env->addPheroToFood(pos, 2*cptTour);

        if (pos.isNextTo(colonie->getPos())) {
            pos = colonie->getPos();
        } else {

            Case* casePhero = nullptr;
            Case* caseNour = nullptr;
            
            // On vérifie s'il y a de la phéromone à proximité
            for(Case* & c : aroundCase ) {
                // on vérifie s'il y a de la pheromone et si la case ne correspond pas à la derniere position
                // if ( c->isTherePheroToHome() && (!(c->getPos() == lastPos)) ) {
                if ( c->isTherePheroToHome() ) {
                    if (casePhero == nullptr)
                        casePhero = c;
                    else if (c->getPheroToHome()->getAmount() > casePhero->getPheroToHome()->getAmount())
                        casePhero = c;
                }
            }

            if (casePhero != nullptr) {
                setPos(casePhero->getPos());

            // Sinon on continue de chercher aléatoirement
            } else {
                while (!aroundCase[(int)direction.getCaseDir()]->getDeplacement()) {
                    direction.update();
                }
                setPos(aroundCase[(int)direction.getCaseDir()]->getPos());

                // ---------- POUR TEST ----------------------------------
                // se déplace dans une direction uniquement (écrase obstacles)
                // pos.setPos(getPos().getX()-1,getPos().getY());

                // se déplace dans une direction variable (écrase obstacles)
                // pos.setPos(aroundCase[(int)direction.getCaseDir()]->getPos());
            }
        }
    }
}

void FourmiGuerriere::moveToFood() {

    if (!(pos == colonie->getPos())) {
        env->addPheroToHome(pos, 2*cptTour);
    }

    Case* caseNour = nullptr;
    Case* casePhero = nullptr;
    Case* casePos = env->getPtrCase(pos.getX(), pos.getY());
    int amountPos;

    if (casePos->isTherePheroToFood()) 
        amountPos = casePos->getPheroToFood()->getAmount();
    else
        amountPos = 0;

    
    // On vérifie si il y a de la nourriture ou de la phéromone à proximité
    for(Case* & c : aroundCase ) {
        // on vérifie s'il y a de la pheromone et si la case ne correspond pas à la derniere position
        // if ( c->isTherePheroToFood() && (!(c->getPos() == lastPos)) ) {
        if ( c->isTherePheroToFood() && (!(c->getPos() == lastPos)) && (c->getPheroToFood()->getAmount() > amountPos) ) {
            if (casePhero == nullptr)
                casePhero = c;
            else if (c->getPheroToFood()->getAmount() > casePhero->getPheroToFood()->getAmount())
                casePhero = c;
        }
        if (c->getType() == Type::SrcNourr) {
            caseNour = c;
        }
    }

    // S'il y a de la nourriture, on en prend
    if (caseNour != nullptr) {
        grabNourriture(caseNour);
        cptTour = 0;
    }

    // Sinon on suit la pheromone
    else if (casePhero != nullptr) {
        // pos.setPos(casePhero->getPos());
        setPos(casePhero->getPos());

    // Sinon on continue de chercher aléatoirement
    } else {
        while (!aroundCase[(int)direction.getCaseDir()]->getDeplacement()) {
            direction.update();
        }
        // pos.setPos(aroundCase[(int)direction.getCaseDir()]->getPos());
        setPos(aroundCase[(int)direction.getCaseDir()]->getPos());

        // ---------- POUR TEST ----------------------------------
        // se déplace dans une direction uniquement (écrase obstacles)
        // pos.setPos(getPos().getX()-1,getPos().getY());

        // se déplace dans une direction variable (écrase obstacles)
        // pos.setPos(aroundCase[(int)direction.getCaseDir()]->getPos());
    }
}

void FourmiGuerriere::moveToDirection() {
    while (!aroundCase[(int)direction.getCaseDir()]->getDeplacement()) {
        direction.update();
    }
    // pos.setPos(aroundCase[(int)direction.getCaseDir()]->getPos());
    setPos(aroundCase[(int)direction.getCaseDir()]->getPos());
}

void FourmiGuerriere::setMode(Mode mode) { 
    this->mode = mode; 
}

void FourmiGuerriere::setPos(Position p) {
    lastPos = pos;
    pos = p;
}

// --------------- GESTION NOURRITURE -------------------------------------------------------------------------------
void FourmiGuerriere::grabNourriture(Case* caseNour) {
    nourr = caseNour->pickNourr(maxNourr);
    setMode(Mode::toHome);
}

void FourmiGuerriere::dropNourriture() {
    // if (colonie->getFood() + nourr <= colonie->getFoodMax()) {
        colonie->addFood(nourr);
        nourr = 0;
        setMode(Mode::toFood);
    // }
}

void FourmiGuerriere::eat() {
    cptTour = 0;
    if (colonie->getFood() >= consoNourriture) {
        colonie->substractFood(consoNourriture);
        giveLife();
    }
}

// --------------- AFFICHAGE ----------------------------------------------------------------------------------------
void FourmiGuerriere::display() {
	// HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD dwPos;
	// dwPos.X = pos.getX();
	// dwPos.Y = pos.getY() +1; // +1 à cause de la premiere ligne de texte
	// SetConsoleCursorPosition(hcon, dwPos);
    // SetConsoleTextAttribute(hcon, 12);
    // cout << '8';
    // SetConsoleTextAttribute(hcon, 15);
    affichageTxtColor2(pos, "8", 12);
}

void FourmiGuerriere::eraseLastPos() {
	// HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	// COORD dwPos;
	// dwPos.X = lastPos.getX();
	// dwPos.Y = lastPos.getY() +1;
	// SetConsoleCursorPosition(hcon, dwPos);
    // SetConsoleTextAttribute(hcon, 15);
    // cout << " ";
    affichageTxtColor2(lastPos, " ", 15);
}

void FourmiGuerriere::erasePos() {
    if (pos != colonie->getPos())
        affichageTxtColor2(pos, " ", 15);
}