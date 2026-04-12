#include "AffichageNbBalles.h"

// Tableau 0-9
const int AffichageNbBalles::chiffres[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1},  // 2
    {1, 1, 1, 1, 0, 0, 1},  // 3
    {0, 1, 1, 0, 0, 1, 1},  // 4
    {1, 0, 1, 1, 0, 1, 1},  // 5
    {1, 0, 1, 1, 1, 1, 1},  // 6
    {1, 1, 1, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 1, 1, 1, 0, 1, 1}   // 9
};

AffichageNbBalles::AffichageNbBalles(int segPins[7], int valeurInitiale) {
  for (int i = 0; i < 7; i++) {
    segments[i] = segPins[i];
  }
  nb_balles = valeurInitiale;
}

void AffichageNbBalles::begin() {
  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }
  update();
}

void AffichageNbBalles::setNbBalles(int valeur) {
  if (valeur < 0) valeur = 0;
  if (valeur > 9) valeur = 9;
  nb_balles = valeur;
}

int AffichageNbBalles::getNbBalles() { return nb_balles; }

void AffichageNbBalles::update() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], chiffres[nb_balles][i]);
  }
}
