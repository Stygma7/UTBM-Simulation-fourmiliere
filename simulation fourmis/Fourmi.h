#ifndef __FOURMI_H__
#define __FOURMI_H__

class Fourmiliere;

class Fourmi
{
private:
    int m_MAX_VIE;
    int m_vie;

    // pointeur sur la colonie de la fourmi
    Fourmiliere* m_colonie;
    // seuil de vie pour lequel la fourmi cherchera à se ravitailler
    int m_seuilRavitaillement;
    // nombre de points de vie perdue par une fourmi par tour
    int m_perteVie;
    // quantité de nourriture consommée lors du ravitaillement
    int m_consoNourriture;

public: 

    Fourmi(Fourmiliere*, int max_vie, int perteVie, int consoNourriture, int seuilRavitaillement);
    ~Fourmi();

    int getVie() {return m_vie;}
    void setVie(int vie) { m_vie = vie; }

    int getMAX_VIE() { return m_MAX_VIE; }
    Fourmiliere* getColonie() { return m_colonie; }
    int getSeuilRavitaillement() { return m_seuilRavitaillement; }
    int getPerteVie() { return m_perteVie; }
    int getConsoNourriture() { return m_consoNourriture; }
    void giveLife();
    bool isAlive();
    virtual void eat();
};

#endif