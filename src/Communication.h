#ifndef COMMUNICATION_H
#define COMMUNICATION_H

void initCommunication();
void handleSerial();

void envoyerJoystick(int x, int y);
void envoyerBouton(const char* nomBouton);
void envoyerStatus();

#endif