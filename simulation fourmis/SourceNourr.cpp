#include "SourceNourr.h"
#include <cstdlib>

SourceNourr::SourceNourr() {
    // qteNourr = rand() % 21 +5;
    qteNourr = 3;
}

void SourceNourr::pickNourr() {
    if (qteNourr > 0) {
        qteNourr--;
    }
}