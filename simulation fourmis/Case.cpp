#include "Case.h"

//Consrtucteurs
Case::Case() {
    // par défaut, case sans obstacle/nourriture
    deplacement = true;
    qteNourriture = 0;
    updateType();
}

// Case::Case(bool dep) {
//     this->deplacement = dep;
//     nourriture = false;
//     qteNourriture = 0;
// }

Type Case::getType() {
    return type;
}

void Case::updateType() {
    if (deplacement)
        type = Type::Normal;
    else if (qteNourriture > 0)
        type = Type::SrcNourr;
    else 
        type = Type::Obstacle;
}

void Case::setSrcNourr() {
    qteNourriture = 20;
    setObstacle();
}

void Case::setObstacle() { 
    deplacement = false;
    updateType(); 
}

void Case::setQteNourriture(int qteNourriture) { 
    this->qteNourriture = qteNourriture; 
}
