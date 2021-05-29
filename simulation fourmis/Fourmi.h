#pragma once

class Fourmi
{
protected:
    /* data */
    // int posx;
    // int posy;
    int maxVie = 50;
    int vie = maxVie;
    int seuilRavitaillement = 20;

public: 
    // void Fourmi::eat();
    // virtual void update();
    int getVie() {return vie;}
};