#include "JoyStick.h"

#include <Arduino.h>

joyStick::joyStick() {
  xVal = 0;
  yVal = 0;
}

void joyStick::lireValeur(int pinX, int pinY) {
  xVal = analogRead(pinX);
  yVal = analogRead(pinY);
}

int joyStick::getX() { return xVal; }

int joyStick::getY() { return yVal; }

/*void joyStick::afficherValeurTerminal(){
    Serial.print("axe X = ");
    Serial.print(xVal);
    Serial.print(", axe Y = ");
    Serial.print(yVal);
    Serial.print("\n");
}

void joyStick::afficherValeurLCD(LiquidCrystal& lcd){
    lcd.setCursor(0, 0);
    lcd.print("                ");
    lcd.setCursor(0, 1);
    lcd.print("                ");
    lcd.setCursor(0, 0);
    lcd.print("X= ");
    lcd.print(xVal);
    lcd.setCursor(0, 1);
    lcd.print("Y= ");
    lcd.print(yVal);
}*/