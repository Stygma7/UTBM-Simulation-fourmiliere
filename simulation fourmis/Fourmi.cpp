#include "Fourmi.h"

// la fourmi est elle vivante ? (vie > 0)
bool Fourmi::isAlive() {
    if (vie > 0)
        return true;
    else
        return false;
}

// redonne le max de vie à la fourmi
void Fourmi::giveLife() {
    vie = MAX_VIE;
}