#include "Position.h"
#include <math.h>

bool Position::operator==(Position pos) {
    if ((x == pos.getX()) && (y == pos.getY()))
        return true;
    else
        return false; 
}

bool Position::operator!=(Position pos) {
    if ((x != pos.getX()) || (y != pos.getY()))
        return true;
    else
        return false; 
}

bool Position::isNextTo(Position pos) {
    if ( (abs(pos.getX() -x) ==1) && ((pos.getY() -y) ==0) || (abs(pos.getY() -y) ==1) && ((pos.getX() -x) ==0))
        return true;
    else 
        return false;
}