#pragma once
// #ifndef FOURMIG_H
// #define FOURMIG_H
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
    std::vector<Position> cheminToHome;
    // position de la fourmi
    Position pos;
    // derniere position de la fourmi
    Position lastPos;
    // mode de déplacement de la fourmi (vers maison ou vers nourriture)
    Mode mode = Mode::toFood;
    // liste des cases se trouvant autour de la fourmi
    std::vector<Case*> vecCase;
    // pointeur sur l'environnement de la fourmi
    Environnement* env;
    // pointeur sur la colonie de la fourmi
    Fourmilliere* colonie;
    // direction de déplacement de la fourmi
    Direction direction;

    // transport de nourriture vers la fourmilliere
    void moveToHome();
    // recherche de nourriture 
    void moveToFood();
    // change le mode de deplacement
    void setMode(Mode mode) { this->mode = mode;}

public:
    // Constructeur
    FourmiGuerriere(Fourmilliere*);

    Position getPos() { return pos; }
    Position getLastPos() { return lastPos; }

    // deplacement de la fourmi
    void update();
    
    // --------- GESTION NOURRITURE -------------------------------------------------------------
    // Prend de la nourriture sur la case
    void grabNourriture(Case*);
    // Dépose de la nourriture à la fourmilliere
    void dropNourriture();

    // --------- AFFICHAGE ----------------------------------------------------------------------
    // affiche la fourmi (à déplacer dans environnement ???)
    void display();
    // efface graphiquement la derniere position de la fourmi (à déplacer dans environnement ???)
    void eraseLastPos();
};

// #endif