#include "Fourmi.h"
#include "Fourmiliere.h"

// la fourmi est elle vivante ? (vie > 0)
bool Fourmi::isAlive() {
    if (m_vie > 0)
        return true;
    else
        return false;
}

Fourmi::Fourmi(Fourmiliere* colonie, int max_vie, int perteVie, int consoNourriture, int seuilRavitaillement) :
    m_MAX_VIE(max_vie),
    m_vie(m_MAX_VIE),
    m_colonie(colonie),
    m_perteVie(perteVie),
    m_consoNourriture(consoNourriture),
    m_seuilRavitaillement(seuilRavitaillement)
{
}

Fourmi::~Fourmi() {

}

// redonne le max de vie à la fourmi
void Fourmi::giveLife() {
    m_vie = m_MAX_VIE;
}

// la fourmi se nourrit
void Fourmi::eat() {
    if (m_colonie->getFood() >= m_consoNourriture) {
        m_colonie->substractFood(m_consoNourriture);
        giveLife();
    }
}