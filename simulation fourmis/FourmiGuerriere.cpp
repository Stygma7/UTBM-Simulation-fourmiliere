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
    pos.setX(env->getColonne() / 2);
    pos.setY(env->getLigne() / 2);
}

// --------------- UPDATE -------------------------------------------------------------------------------------------
void FourmiGuerriere::update(){
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
    
    affichageTxtColor2(Position(104,14), "pos X : " + to_string(pos.getX()) + " Y : " + to_string(pos.getY()) + " ", 15);
    affichageTxtColor2(Position(104,15), "las X : " + to_string(lastPos.getX()) + " Y : " + to_string(lastPos.getY()) + " ", 15);
    
    // sauvegarde derniere position
    lastPos = tempPos;
    tempPos = pos;

    if (!(pos == colonie->getPos())) 
        cptTour++;
}

// --------------- DEPLACEMENT --------------------------------------------------------------------------------------
void FourmiGuerriere::moveToHome() {
    // if (!(pos == colonie->getPos())) {
    //     env->addPhero(pos, 2*cptTour);

    //     if (pos.isNextTo(colonie->getPos())) {
    //         pos = colonie->getPos();
    //         cheminToHome.clear();
    //     } else {
    //         pos = cheminToHome.back();
    //         cheminToHome.erase(cheminToHome.end()-1);
    //     }
    //     cptTour++;
    // } else
    //     dropNourriture();

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
                if ( c->isTherePheroToHome() && (!(c->getPos() == lastPos)) ) {
                    if (casePhero == nullptr)
                        casePhero = c;
                    else if (c->getPheroToHome()->getAmount() > casePhero->getPheroToHome()->getAmount())
                        casePhero = c;
                }
            }


            if (casePhero != nullptr) {
                pos.setPos(casePhero->getPos());

            // Sinon on continue de chercher aléatoirement
            } else {
                while (!aroundCase[(int)direction.getCaseDir()]->getDeplacement()) {
                    direction.update();
                }
                pos.setPos(aroundCase[(int)direction.getCaseDir()]->getPos());

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
    
    // On vérifie si il y a de la nourriture ou de la phéromone à proximité
    for(Case* & c : aroundCase ) {
        // on vérifie s'il y a de la pheromone et si la case ne correspond pas à la derniere position
        if ( c->isTherePheroToFood() && (!(c->getPos() == lastPos)) ) {
            affichageTxtColor2(Position(104,10), "cas X : " + to_string(c->getPos().getX()) + " Y : " + to_string(c->getPos().getY()) + " ", 15);
            affichageTxtColor2(Position(104,11), "pos X : " + to_string(pos.getX()) + " Y : " + to_string(pos.getY()) + " ", 15);
            affichageTxtColor2(Position(104,12), "las X : " + to_string(lastPos.getX()) + " Y : " + to_string(lastPos.getY()) + " ", 15);
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
        pos.setPos(casePhero->getPos());

    // Sinon on continue de chercher aléatoirement
    } else {
        while (!aroundCase[(int)direction.getCaseDir()]->getDeplacement()) {
            direction.update();
        }
        pos.setPos(aroundCase[(int)direction.getCaseDir()]->getPos());

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
    pos.setPos(aroundCase[(int)direction.getCaseDir()]->getPos());
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