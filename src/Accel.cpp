#include "Accel.h"

Accel::Accel(int xPin, int yPin, int zPin) {
  Xpin = xPin;
  Ypin = yPin;
  Zpin = zPin;
}

OutputAccel Accel::readValues() {
  int valeurx = analogRead(Xpin);
  int valeury = analogRead(Ypin);
  int valeurz = analogRead(Zpin);

  float somme = valeurx + valeury + valeurz;

  if (somme >= 1000.0) {
    return {valeurx, valeury, valeurz, true};
  } else {
    return {valeurx, valeury, valeurz, false};
  }
}