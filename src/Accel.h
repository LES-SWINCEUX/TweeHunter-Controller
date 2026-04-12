#ifndef ACCEL_H
#define ACCEL_H

#include <Arduino.h>

struct OutputAccel {
  int x;
  int y;
  int z;
  bool isActive;
};

class Accel {
 private:
  int Xpin;
  int Ypin;
  int Zpin;

 public:
  Accel(int xPin, int yPin, int zPin);

  OutputAccel readValues();
};

#endif