#include "SourceNourr.h"
#include <cstdlib>

SourceNourr::SourceNourr() {
    // entre 5 et 25
    qteNourr = rand() % 21 +5;
    // qteNourr = 2;
}

int SourceNourr::pickNourr(int nourr) {
    if (qteNourr > nourr) {
        qteNourr -= nourr;
        return nourr;
    } else {
        int tmp = qteNourr;
        qteNourr = 0;
        return tmp;
    }
}