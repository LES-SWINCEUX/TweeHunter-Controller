/*
 * incremental.cpp
 *
 * Serge Caron, feb 2026
 *
 * Decode cheap rotary encoder. Contrary to a quadrature encoder, some rotary
 * encoders always send 2 pulses per detend (1 falling edge and 1 rising edge
 * per channel) before going back to an idle state. In such case, all you have
 * to do is interrupt on the falling edge of one channel. When it occurs, the
 * state of the second channel tells you the direction of rotation. Original
 * code is from there:
 * https://arduino.stackexchange.com/questions/61785/cant-you-easily-use-quadrature-incremental-rotary-encoders-at-2x-or-4x-their
 *
 * ArduinoMega digital pin usable for interrupt: 2, 3, 18, 19, 20, 21
 */

#include "incremental.h"

#include <Arduino.h>

// internal variable
int rotaryPinA = 2;   // this is your interrupt pin
int rotaryPinB = 3;   // this can be any digital input
int rotaryValue = 0;  // the actual count

// *********************************************************************
// encode()
// ISR that decodes your cheap encoder
// The count is kept in rotaryValue
// *********************************************************************
void encode() {
  // state of Pin B at falling edge of Pin A tells us the direction of rotation
  bool pinBState = digitalRead(rotaryPinB);
  rotaryValue += (pinBState) ? -1 : 1;
}

// *********************************************************************
// setup_encoder()
// intPinA is the interrupt pin; PinB can be any other digital input pin
// return -1 if failed to setup interrupt
// *********************************************************************
int setup_encoder(int intPinA, int PinB) {
  if (digitalPinToInterrupt(intPinA) == -1)
    return -1;  // not a valid interrupt pin
  else {
    rotaryPinA = intPinA;
    rotaryPinB = PinB;
    pinMode(intPinA, INPUT);
    pinMode(PinB, INPUT);
    attachInterrupt(digitalPinToInterrupt(intPinA), encode, FALLING);
    return 0;  // setup is done
  }
}

// *********************************************************************
// read_encoder()
// return the content of rotaryValue
// *********************************************************************
int read_encoder() {
  static int lastValue = 0;
  int currentValue;

  noInterrupts();
  currentValue = rotaryValue;
  interrupts();

  int delta = currentValue - lastValue;
  lastValue = currentValue;

  if (delta > 0) return 1;   // sens horaire
  if (delta < 0) return -1;  // sens antihoraire
  return 0;                  // pas de mouvement
}

// *********************************************************************
// write_encoder()
// set the content of rotaryValue
// *********************************************************************
void write_encoder(int value) {
  noInterrupts();
  rotaryValue = value;
  interrupts();
}

/* endoffile */
