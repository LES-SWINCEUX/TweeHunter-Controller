#include <Arduino.h>

/*
 * incremental.ino
 *
 * Serge Caron, feb 2026
 *
 * Decode cheap rotary encoder. Contrary to a quadrature encoder, some rotary
encoders always send 2 pulses per detend (1 falling edge and 1 rising edge per
channel)
 * before going back to an idle state.
 * In such case, all you have to do is interrupt on the falling edge of one
channel. When it occurs, the state of the second channel tells you the direction
of rotation.
 * Original code is from there:
 * https://arduino.stackexchange.com/questions/61785/cant-you-easily-use-quadrature-incremental-rotary-encoders-at-2x-or-4x-their
 *
 * ArduinoMega digital pin usable for interrupt: 2, 3, 18, 19, 20, 21
 *  {"type":"config","nb_balles":9}
    {"type":"command","cmd":"remove_ball"}

    json j;
j["type"] = "config";
j["nb_balles"] = nbBalles;

std::string msg = j.dump() + "\n";
arduino.writeSerialPort(msg.c_str(), msg.length());
 */

#include "AffichageNbBalles.h"
#include "Communication.h"
#include "incremental.h"
#include "JoyStick.h"
#include "Accel.h"
#include "LiquidCrystal.h"

int segPins[7] = {30,31,32,33,34,35,36};
int nbBalles = 0;

AffichageNbBalles affichage(segPins);
joyStick js;   // 🔥 joystick

unsigned long lastSend = 0;
const unsigned long interval = 25; // 20 Hz

void setup() {

  Serial.begin(115200);
  delay(1000);

  affichage.begin();
  initCommunication();
}

void loop() {

  handleSerial();

  affichage.setNbBalles(nbBalles);
  affichage.update();

  unsigned long currentTime = millis();

  if (currentTime - lastSend >= interval) {

    lastSend = currentTime;

    
    js.lireValeur(A0, A7);

    envoyerJoystick(js.getX(), js.getY());
  }
}