#include "Case.h"

//Consrtucteurs
Case::Case() {
    deplacement = true;
    nourriture = false;
}

Case::Case(bool dep) {
    deplacement = dep;
    nourriture = false;
}
;