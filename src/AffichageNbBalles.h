#ifndef AFFICHAGENBBALLES_H
#define AFFICHAGENBBALLES_H

#include <Arduino.h>

class AffichageNbBalles {
  private:
    int segments[7];
    int nb_balles;

    static const int chiffres[10][7];

  public:
    AffichageNbBalles(int segPins[7], int valeurInitiale = 0);

    void begin();
    void setNbBalles(int valeur);
    int getNbBalles();
    void update();
};

#endif