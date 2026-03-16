#ifndef COMMUNICATION_H
#define COMMUNICATION_H

int nbBalles;

void initCommunication();
void handleSerial();

void envoyerJoystick(int x, int y);
void envoyerBouton(const bool gachette, const bool reload, const bool accel,
                   int encodeur);

// void envoyerBouton1(const bool nomBouton);
// void envoyerBouton2(const bool nomBouton);

void envoyerStatus();

int getNb_balles() { return nbBalles; }

#endif