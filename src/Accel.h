#ifndef Accel_h
#define Accel_h
#include <Arduino.h>

struct OutputAccel {
  int x;
  int y;
  int z;
};

class Accel {
 private:
  int Xpin = A1;
  int Ypin = A2;
  int Zpin = A3;

 public:
  Accel(int xPin, int yPin, int zPin) : Xpin(xPin), Ypin(yPin), Zpin(zPin) {}
  OutputAccel readValues();
};
#endif