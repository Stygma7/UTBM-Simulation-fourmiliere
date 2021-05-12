#include "Fourmilliere.h"

using namespace std;

Fourmilliere::Fourmilliere() {

}

Fourmilliere::Fourmilliere(Environnement& env, Position position) {
    pos = position;
    for (int i = 0; i < 10; i++)
    {
        listFourmisGuerrieres.push_back(FourmiGuerriere(env));
    }
}

void Fourmilliere::update(Environnement& env) {
    for(FourmiGuerriere & fourmiG : listFourmisGuerrieres ) {
        fourmiG.update(env);
    }
}
