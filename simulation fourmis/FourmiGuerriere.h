
#ifndef FOURMIG_H
#define FOURMIG_H
#include <vector>
#include "Fourmilliere.h"
class Fourmilliere;
#include "Environnement.h"
class Environnement;
#include "Position.h"
#include "ModeFourmi.h"
#include "Fourmi.h"
#include "Direction.h"

class FourmiGuerriere : public Fourmi
{
private:
    // liste des cases parcourues depuis la fourmilliere
    // std::vector<Position> cheminToHome;
    // position de la fourmi
    Position pos;
    // derniere position de la fourmi
    Position lastPos;
    // Position tempPos;
    // mode de déplacement de la fourmi (vers maison ou vers nourriture)
    Mode mode = Mode::toFood;
    // liste des cases se trouvant autour de la fourmi
    std::vector<Case*> aroundCase;
    // pointeur sur l'environnement de la fourmi
    Environnement* env;
    // pointeur sur la colonie de la fourmi
    Fourmilliere* colonie;
    // direction de déplacement de la fourmi
    Direction direction;
    // quantité de nourriture transportée
    int nourr = 0;
    const int maxNourr = 5;
    // compteur de tour pour pouvoir réduire la quantité de pheromone à déposer
    int cptTour = 0;

    // transport de nourriture vers la fourmilliere
    void moveToHome();
    // recherche de nourriture 
    void moveToFood();
    // suit la direction
    void moveToDirection();
    // change le mode de deplacement
    void setMode(Mode);

public:
    // Constructeur
    FourmiGuerriere(Fourmilliere*);
    FourmiGuerriere(Fourmilliere*, int);

    Position getPos() { return pos; }
    Position getLastPos() { return lastPos; }
    void setPos(Position);

    // deplacement de la fourmi
    void update();
    // void updateVie();
    
    // --------- GESTION NOURRITURE -------------------------------------------------------------
    // Prend de la nourriture sur la case
    void grabNourriture(Case*);
    // Dépose de la nourriture à la fourmilliere
    void dropNourriture();
    void eat();

    // --------- AFFICHAGE ----------------------------------------------------------------------
    // affiche la fourmi (à déplacer dans environnement ???)
    void display();
    // efface graphiquement la derniere position de la fourmi (à déplacer dans environnement ???)
    void eraseLastPos();
};

#endif