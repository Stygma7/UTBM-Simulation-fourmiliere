#include "Position.h"

bool Position::operator==(Position pos) {
    if ((x == pos.getX()) && (y == pos.getY()))
        return true;
    else
        return false; 
}