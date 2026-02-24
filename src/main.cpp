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

int previous = 1;
// int segPins[7] = {30,31,32,33,34,35,36};
// int nbBalles = 0;
// AffichageNbBalles affichage(segPins);

void setup() {
  // {"type":"config","nb_balles":7}
  Serial.begin(115200);
  delay(1000);
  // affichage.begin();
  // initCommunication();

  /*Serial.println("Incremental Encoder tester");
  if( setup_encoder(18, 19) == -1 )
    Serial.println("Failed to setup interrupt.");
  write_encoder(6);  // set initial count value*/
}

/*void loop()
{

//handleSerial();

//affichage.setNbBalles(nbBalles);
//affichage.update();

}*/

/*Code pour increment decrement

int lecture = read_encoder();

 // watch and print encoder count
 if( lecture != previous )
 {
   Serial.println( lecture );
   previous = lecture;
 }
 delay(50);








/* endoffile */

/*Code pour menu lcd print 1 quand incrémente et -1 quand décrémente*/
int mode = 0;
int lastValue = 0;

void loop() {
  int val = read_encoder();

  if (val != lastValue) {
    mode += (val - lastValue);
    lastValue = val;

    if (mode < 0) mode = 0;
    if (mode > 2) mode = 2;

    // lcd.clear();

    switch (mode) {
      case 0:
        // lcd.print("Mode 0");
        break;
      case 1:
        // lcd.print("Mode 1");
        break;
      case 2:
        // lcd.print("Mode 2");
        break;
    }
  }
}