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
    // pos.setX(env->getColonne() / 2);
    // pos.setY(env->getLigne() / 2);
    pos = col->getPos();
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

    direction.update();
    if (mode == Mode::toHome) {
        moveToHome();
    } else {
        moveToFood();
    }
    
    // affichageTxtColor2(Position(104,11), "pos X : " + to_string(pos.getX()) + " Y : " + to_string(pos.getY()) + " ", 15);
    // affichageTxtColor2(Position(104,12), "las X : " + to_string(lastPos.getX()) + " Y : " + to_string(lastPos.getY()) + " ", 15);
    // if (mode == Mode::toHome)
    //     affichageTxtColor2(Position(104,13), "toHome " + to_string(Pheromone::AMOUNT_MAX - 2*cptTour) + " ", 15);
    // else
    //     affichageTxtColor2(Position(104,13), "toFood " + to_string(Pheromone::AMOUNT_MAX - 2*cptTour) + " ", 15);


    // Case* ptrCase;

    // ptrCase = env->getPtrCase(pos.getX(), pos.getY());
    // affichageTxtColor2(Position(104,16), "case fourmi ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,16), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,16), "          " , 15);

    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,16), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,16), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX(), pos.getY()-1);
    // affichageTxtColor2(Position(104,17), "case haut ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,17), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,17), "          " , 15);

    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,17), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,17), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX()+1, pos.getY());
    // affichageTxtColor2(Position(104,18), "case droite ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,18), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,18), "          " , 15);

    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,18), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,18), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX(), pos.getY()+1);
    // affichageTxtColor2(Position(104,19), "case bas ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,19), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,19), "          " , 15);
    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,19), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,19), "          " , 15);

    // ptrCase = env->getPtrCase(pos.getX()-1, pos.getY());
    // affichageTxtColor2(Position(104,20), "case gauche ", 15);
    // if (ptrCase->isTherePheroToFood()) 
    //     affichageTxtColor2(Position(116,20), "food : " + to_string(ptrCase->getPheroToFood()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(116,20), "          " , 15);
    // if (ptrCase->isTherePheroToHome()) 
    //     affichageTxtColor2(Position(126,20), " home : " + to_string(ptrCase->getPheroToHome()->getAmount()) + " ", 15);
    // else
    //     affichageTxtColor2(Position(126,20), "          " , 15);



    if (!(pos == colonie->getPos())) 
        cptTour++;
}

// --------------- DEPLACEMENT --------------------------------------------------------------------------------------
void FourmiGuerriere::moveToHome() {
    if (pos == colonie->getPos()) {
        dropNourriture();

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

    // Stocke la position avant déplacement
    // cheminToHome.push_back(pos);

    Case* caseNour = nullptr;
    Case* casePhero = nullptr;
    casePhero = nullptr;

    Case* casePos = env->getPtrCase(pos.getX(), pos.getY());
    int amountPos;

    if (casePos->isTherePheroToFood()) 
        amountPos = casePos->getPheroToFood()->getAmount();
    else
        amountPos = 0;

    
    // On vérifie si il y a de la nourriture ou de la phéromone à proximité
    for(Case* & c : aroundCase ) {
        // on vérifie s'il y a de la pheromone et si la case ne correspond pas à la derniere position
        if ( c->isTherePheroToFood() && (!(c->getPos() == lastPos)) ) {
        // if ( c->isTherePheroToFood() && (c->getPheroToFood()->getAmount() > amountPos) ) {
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
    if (caseNour != nullptr)
        grabNourriture(caseNour);

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
    cptTour = 0;
}

void FourmiGuerriere::setPos(Position p) {
    lastPos = pos;
    pos = p;
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