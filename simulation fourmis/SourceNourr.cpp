#include "SourceNourr.h"
#include <cstdlib>

SourceNourr::SourceNourr() {
    // entre 5 et 25
    // qteNourr = rand() % 21 +5;
    qteNourr = 2;
}

void SourceNourr::pickNourr() {
    if (qteNourr > 0) {
        qteNourr--;
    }
}