#include "Environnement.h"
#include "Case.h"

Case::Case(Environnement* e) {
    env = e;
    setType(Type::Normal);
}

Case::~Case() {
    delete(srcNour);
}

void Case::setPos(Position pos) {
    this->pos = pos;
}

void Case::setPos(int x, int y) {
    pos.setX(x);
    pos.setY(y);
}

// déduit la quantité de nourriture sur la source associée, et renvoit la quantité qui a été ramassée
int Case::pickNourr(int nourr) {
    int tmp = srcNour->pickNourr(nourr);
    if (srcNour->getquantite() <= 0) {
        delete srcNour;
        srcNour = nullptr;
        setType(Type::Normal);
        
        deleteAffichage(CaseInfoAff::SrcNourr);
    }
    return tmp;
}

// change le type de la case
void Case::setType(Type type) {
    switch (type)
    {
    case Type::Obstacle:
        deplacement = false;
        addAffichage(CaseInfoAff::Obstacle);
        break;
    case Type::SrcNourr:
        deplacement = false;
        if (srcNour == nullptr)
            srcNour = new SourceNourr();
        addAffichage(CaseInfoAff::SrcNourr);
        break;

    default:
        this->type = Type::Normal;
        deplacement = true;
        break;
    }

    this->type = type;
}

// vérifie si de la pheromone toFood est présente sur la case
bool Case::isTherePheroToFood() {
    if (pheroToFood == nullptr)
        return false;

    if (pheroToFood->getAmount() > 0)
        return true;
    else
        return false;
}

// vérifie si de la pheromone toHome est présente sur la case
bool Case::isTherePheroToHome() {
    if (pheroToHome == nullptr)
        return false;

    if (pheroToHome->getAmount() > 0)
        return true;
    else
        return false;
}

// setter de pheromone toFood
void Case::setPheroToFood(Pheromone* ph) {
    pheroToFood = ph;
}

// setter de pheromone toHome
void Case::setPheroToHome(Pheromone* ph) {
    pheroToHome = ph;
}

// ajoute de la phero toFood seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Case::addReducPheroToFood(int reduc) {
    pheroToFood->addReducAmount(reduc);
}

// ajoute de la phero toHome seulement si la quantité deja présente est inférieure à ce qu'on veut mettre
void Case::addReducPheroToHome(int reduc) {
    pheroToHome->addReducAmount(reduc);
}


// ajoute un élément CaseInfoAff à afficher sur la case
void Case::addAffichage(CaseInfoAff infoAff){
    CaseInfoAff temp = getInfoAff();
    listAffichage.insert(infoAff);

    if (getInfoAff() != temp)
        env->addCaseAffichage(this);
}

// supprime un élément CaseInfoAff à enlever de la case
void Case::deleteAffichage(CaseInfoAff infoAff){
    CaseInfoAff temp = getInfoAff();

	std::unordered_set<CaseInfoAff>::const_iterator it = listAffichage.find (infoAff);
	if ( it != listAffichage.end() )
    	listAffichage.erase(it);

    if (getInfoAff() != temp)
        env->addCaseAffichage(this);
}

// renvoit l'élément CaseInfoAff à afficher sur la case
CaseInfoAff Case::getInfoAff() {
    CaseInfoAff returnInfoAff = CaseInfoAff::Rien;

    for (CaseInfoAff infoAff : listAffichage) {
        if (infoAff > returnInfoAff ) {
            returnInfoAff = infoAff;
        }
    }

    return returnInfoAff;
}