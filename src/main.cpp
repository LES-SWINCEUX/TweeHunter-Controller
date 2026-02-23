#include <Arduino.h>
#include <LiquidCrystal.h> 
#include "JoyStick.h"

const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

#define X_pin A0
#define Y_pin A1

joyStick joyStick1;

void setup(){
     Serial.begin(9600);
     lcd.begin(16, 2);
     lcd.setCursor(0, 0);
     lcd.print("init");
     delay(1000);
     lcd.clear();
}

void loop(){
    joyStick1.lireValeur(X_pin, Y_pin);
    joyStick1.afficherValeurTerminal();
    joyStick1.afficherValeurLCD(lcd);
    delay(200);
}