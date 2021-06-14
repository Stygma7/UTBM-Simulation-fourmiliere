#ifndef __FOURMI_H__
#define __FOURMI_H__

class Fourmi
{
protected:
    int MAX_VIE = 50;
    int vie = MAX_VIE;
    // seuil de vie pour lequel la fourmi cherchera à se ravitailler
    int seuilRavitaillement = 20;
    // nombre de points de vie perdue par une fourmi par tour
    int perteVie = 1;
    // quantité de nourriture consommée lors du ravitaillement
    int consoNourriture = 1;

public: 
    int getVie() {return vie;}
    void giveLife();
    bool isAlive();
};

#endif