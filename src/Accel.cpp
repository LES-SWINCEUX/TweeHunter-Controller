#include "Accel.h"

OutputAccel Accel::readValues() {
  int valeurx = analogRead(Xpin);
  int valeury = analogRead(Ypin);
  int valeurz = analogRead(Zpin);
  float somme = valeurx + valeury + valeurz;
    if (somme>=1000.0){
      return {valeurx, valeury, valeurz, true};
}
  else {
    return {valeurx, valeury, valeurz, false};
  }
}