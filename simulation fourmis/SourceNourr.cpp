#include "SourceNourr.h"
#include <cstdlib>

// aléatoire entre 5 et 25
SourceNourr::SourceNourr() {
    qteNourr = rand() % 21 +5;
}

// déduit la quantité de nourriture passée en paramètre, et renvoit la quantité qui a été ramassée
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