
#ifndef FOURMIG_H
#define FOURMIG_H
#include <vector>
#include "Fourmiliere.h"
class Fourmiliere;
#include "Environnement.h"
class Environnement;
#include "Position.h"
#include "ModeFourmi.h"
#include "Fourmi.h"
#include "Direction.h"

class FourmiGuerriere : public Fourmi
{
private:
    // position de la fourmi
    Position pos;
    // derniere position de la fourmi
    Position lastPos;
    // mode de déplacement de la fourmi (vers maison ou vers nourriture)
    Mode mode = Mode::toFood;
    // liste des cases se trouvant autour de la fourmi
    std::vector<Case*> aroundCase;
    // pointeur sur l'environnement de la fourmi
    Environnement* env;
    // pointeur sur la colonie de la fourmi
    Fourmiliere* colonie;
    // direction de déplacement de la fourmi
    Direction direction;
    // quantité de nourriture transportée
    int nourr = 0;
    // quantité max de nourriture pouvant être transportée
    const int maxNourr = 5;
    // compteur de tour pour pouvoir réduire la quantité de pheromone à déposer à chaque tour
    int cptTour = 0;

    // retour vers la Fourmiliere, avec nourriture ou non
    void moveToHome();
    // recherche de nourriture 
    void moveToFood();
    // se déplace vers la direction
    void moveToDirection();
    // change le mode de deplacement
    void setMode(Mode);

public:
    // Constructeur
    FourmiGuerriere(Fourmiliere*);
    FourmiGuerriere(Fourmiliere*, int);

    Position getPos() { return pos; }
    Position getLastPos() { return lastPos; }
    void setPos(Position);

    // deplacement de la fourmi
    void update();
    
    // --------- GESTION NOURRITURE -------------------------------------------------------------
    // Prend de la nourriture sur la case
    void grabNourriture(Case*);
    // Dépose de la nourriture à la Fourmiliere
    void dropNourriture();
    void eat();
};

#endif