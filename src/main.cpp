
#include "Accel.cpp"

Accel* accel = nullptr;
void setup() {
  Serial.begin(9600);
  accel = new Accel(A1, A2, A3);
}

void loop() {
  OutputAccel output = accel->readValues();
  Serial.print("X : ");
  Serial.print(output.x);
  Serial.print(" | Y : ");
  Serial.print(output.y);
  Serial.print(" | Z : ");
  Serial.println(output.z);
}
