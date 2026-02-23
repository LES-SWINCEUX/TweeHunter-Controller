#include "Accel.h"

OutputAccel Accel::readValues() {
  int valeurx = analogRead(Xpin);
  int valeury = analogRead(Ypin);
  int valeurz = analogRead(Zpin);

  return {valeurx, valeury, valeurz};
}