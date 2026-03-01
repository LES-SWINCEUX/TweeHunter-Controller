#ifndef SWINCEUR_H
#define SWINCEUR_H

#include <Arduino.h>

class Swinceur
{
    private:
        int extend_pin;
        int retract_pin;
        float swinceTime;

    public:
        Swinceur(int extend_pin, int retract_pin);
        void fullSwince();
        void partialSwince(int time);       //temps en seconde de swince
};

#endif