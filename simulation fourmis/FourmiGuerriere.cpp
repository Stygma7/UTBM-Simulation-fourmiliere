#include "caseType.h"
#include "FourmiGuerriere.h"

using namespace std;

// --------------- CONSTRUCTEURS ------------------------------------------------------------------------------------
FourmiGuerriere::FourmiGuerriere(Fourmiliere* col) :
    Fourmi(col, 100, 1, 3, 40)
{
    env = getColonie()->getEnv();
    pos = col->getPos();
    lastPos = pos;
}

FourmiGuerriere::FourmiGuerriere(Fourmiliere* col, int vie) :
    Fourmi(col, 100, 1, 3, 40)
{
    setVie(vie);
    env = getColonie()->getEnv();
    pos = col->getPos();
    lastPos = pos;
}


// --------------- UPDATE -------------------------------------------------------------------------------------------
// met à jour la fourmi pour un tour
void FourmiGuerriere::update() {
    // Récupération des cases voisines
    aroundCase.clear();
    aroundCase.push_back(env->getPtrCase(pos.getX(), pos.getY() + 1)); // Haut
    aroundCase.push_back(env->getPtrCase(pos.getX() + 1, pos.getY())); // Droite
    aroundCase.push_back(env->getPtrCase(pos.getX(), pos.getY() - 1)); // Bas
    aroundCase.push_back(env->getPtrCase(pos.getX() - 1, pos.getY())); // Gauche

    // petit changement aleatoire de la direction
    direction.update();
    if (getVie() <= getSeuilRavitaillement() || mode == Mode::toHome) {
        moveToHome();
    } else {
        moveToFood();
    }

    setVie(getVie() - getPerteVie());

    // le cptTour permet de déposer de moins en moins de phéromone à chaque tour, pour ne pas en déposer à l'infini
    if (pos != getColonie()->getPos())
        cptTour++;
}


// --------------- DEPLACEMENT --------------------------------------------------------------------------------------
// déplacement vers la fourmillière
void FourmiGuerriere::moveToHome() {
    if (pos == getColonie()->getPos()) {
        if (nourr > 0) {
            dropNourriture();
        }
        
        if (getVie() <= getSeuilRavitaillement()) {
            eat();
        }
        
        lastPos = pos;
        cptTour = 0;

    } else {
        if (nourr > 0)
            env->addPheroToFood(pos, 2*cptTour);

        if (pos.isNextTo(getColonie()->getPos())) {
            setPos(getColonie()->getPos());
        } else {

            Case* casePhero = nullptr;
            Case* caseNour = nullptr;
            
            // On vérifie s'il y a de la phéromone à proximité et on sélectionne celle qui est la plus forte
            for(Case* & c : aroundCase ) {
                if ( c->isTherePheroToHome() ) {
                    if (casePhero == nullptr)
                        casePhero = c;
                    else if (c->getPheroToHome()->getAmount() > casePhero->getPheroToHome()->getAmount())
                        casePhero = c;
                }
            }

            if (casePhero != nullptr) {
                setPos(casePhero->getPos());

            // Sinon on continue de chercher aléatoirement
            } else {
                moveToDirection();
            }
        }
    }
}

// déplacement en mode recherche de nourriture
void FourmiGuerriere::moveToFood() {

    if (!(pos == getColonie()->getPos())) {
        env->addPheroToHome(pos, 2*cptTour);
    }

    Case* caseNour = nullptr;
    Case* casePhero = nullptr;
    // case sur laquelle se trouve la fourmi
    Case* casePos = env->getPtrCase(pos.getX(), pos.getY());
    int amountPos;

    if (casePos->isTherePheroToFood()) 
        amountPos = casePos->getPheroToFood()->getAmount();
    else
        amountPos = 0;

    
    // On vérifie si il y a de la nourriture ou de la phéromone à proximité
    for(Case* & c : aroundCase ) {
        // on vérifie s'il y a de la pheromone et si la case ne correspond pas à la derniere position
        if ( c->isTherePheroToFood() && (!(c->getPos() == lastPos)) && (c->getPheroToFood()->getAmount() > amountPos) ) {
            if (casePhero == nullptr)
                casePhero = c;
            else if (c->getPheroToFood()->getAmount() > casePhero->getPheroToFood()->getAmount())
                casePhero = c;
        }
        if (c->getType() == Type::SrcNourr) {
            caseNour = c;
        }
    }

    // S'il y a de la nourriture, on en prend
    if (caseNour != nullptr) {
        grabNourriture(caseNour);
        cptTour = 0;
    }

    // Sinon on suit la pheromone
    else if (casePhero != nullptr) {
        setPos(casePhero->getPos());

    // Sinon on continue de chercher aléatoirement
    } else {
        moveToDirection();
    }
}

// se déplace vers la direction définie si elle le peut (sinon change jusqu'à pouvoir)
void FourmiGuerriere::moveToDirection() {
    while (!aroundCase[(int)direction.getCaseDir()]->getDeplacement()) {
        direction.update();
    }
    setPos(aroundCase[(int)direction.getCaseDir()]->getPos());
}

// change le mode de la fourmi toHome ou toFood
void FourmiGuerriere::setMode(Mode mode) { 
    this->mode = mode; 
}

// setter de position
void FourmiGuerriere::setPos(Position p) {
    lastPos = pos;
    pos = p;

    env->getPtrCase(pos.getX(), pos.getY())->addAffichage(CaseInfoAff::Fourmi);
    env->getPtrCase(lastPos.getX(), lastPos.getY())->deleteAffichage(CaseInfoAff::Fourmi);
}

// --------------- GESTION NOURRITURE -------------------------------------------------------------------------------
void FourmiGuerriere::grabNourriture(Case* caseNour) {
    nourr = caseNour->pickNourr(maxNourr);
    setMode(Mode::toHome);
    lastPos = pos;
}

void FourmiGuerriere::dropNourriture() {
    int colFood = getColonie()->getFood();
    int colFoodMax = getColonie()->getFoodMax();

    if (colFood + nourr <= colFoodMax) {
        getColonie()->addFood(nourr);
        nourr = 0;
        setMode(Mode::toFood);
    } else if (colFood < colFoodMax) {
        getColonie()->addFood(colFoodMax - colFood);
        nourr -= colFoodMax - colFood;
    }
}

void FourmiGuerriere::eat() {
    cptTour = 0;
    if (getColonie()->getFood() >= getConsoNourriture()) {
        getColonie()->substractFood(getConsoNourriture());
        giveLife();
    }
}