#include "Case.h"

Case::Case() {
    // par défaut, case sans obstacle/nourriture
    deplacement = true;
    updateType();
}

// Case::~Case() {
//     delete(srcNour);
// }


void Case::updateType() {
    if (deplacement)
        type = Type::Normal;
    else if (srcNour != nullptr)
        type = Type::SrcNourr;
    else 
        type = Type::Obstacle;
}

void Case::setSrcNourr() {
    if (srcNour == nullptr);
        this->srcNour = new SourceNourr();
    deplacement = false;
    updateType(); 
}

void Case::setObstacle() { 
    deplacement = false;
    updateType(); 
}

void Case::setPos(Position pos) {
    this->pos = pos;
}

void Case::setPos(int x, int y) {
    pos.setX(x);
    pos.setY(y);
}
