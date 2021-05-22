#include <stdlib.h>
#include <time.h>
#include "Direction.h"

Direction::Direction() {
    angle = rand() % 360;
    updateCaseDir();
}

void Direction::update() {
    // random entre 20 et 50
    int rnd = (rand() % 31) +20;

    if ((rand() %2) == 1)
        angle += rnd;
    else 
        angle = (angle - rnd) +360;
    
    angle %= 360;

    updateCaseDir();
}

// // Direction a +90
// CaseDirection Direction::getCaseDir90() {
//     return (CaseDirection) ( ((int)caseDir+1) % 4 );
// }

// // Direction a -90
// CaseDirection Direction::getCaseDirm90() {
//     return (CaseDirection) ( ((int)caseDir+3) % 4 );
// }

// Direction a +90
CaseDirection Direction::getCaseDir180() {
    return (CaseDirection) ( ((int)caseDir+2) % 4 );
}

void Direction::updateCaseDir() {
    if (angle < 90)
        caseDir = CaseDirection::Haut;
    else if (angle < 180)
        caseDir = CaseDirection::Droite;
    else if (angle < 270)
        caseDir = CaseDirection::Bas;
    else
        caseDir = CaseDirection::Gauche;
}

void Direction::add180() {
    angle += 180;
    updateCaseDir();
}