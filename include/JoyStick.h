#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>
#include <LiquidCrystal.h>

class joyStick {
    private:
        int xVal;
        int yVal;

    public:
        void lireValeur(int pinX, int pinY);
        void afficherValeurTerminal();
        void afficherValeurLCD(LiquidCrystal& lcd);
};

#endif