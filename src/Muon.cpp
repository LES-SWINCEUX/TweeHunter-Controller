#include "Muon.h"

volatile int buffer[N];
volatile uint16_t indexBuf = 0;
volatile uint32_t muonCount = 0;
volatile bool aboveThreshold = false;
volatile uint32_t lastDetection = 0;
volatile bool muonSeuilAtteint = false;

void initMuon() {
  // ADC
  ADCSRA = (ADCSRA & 0b11111000) | 0b010;

  // Timer1 à 10 kHz
  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;

  OCR1A = (16000000 / (8 * FS)) - 1;

  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11);
  TIMSK1 |= (1 << OCIE1A);

  interrupts();
}

ISR(TIMER1_COMPA_vect) {
  int raw = analogRead(A7);

  int centered = raw - 512;
  int scaled = centered * SCALE_FACTOR;

  uint32_t now = micros();

  if (scaled > THRESHOLD && !aboveThreshold &&
      (now - lastDetection > DEAD_TIME_US)) {
    muonCount++;
    aboveThreshold = true;
    lastDetection = now;

    if (muonCount >= SEUIL_MUONS) {
      muonSeuilAtteint = true;
      muonCount = 0;  // reset
    }
  }

  if (scaled < THRESHOLD) {
    aboveThreshold = false;
  }

  int sample = scaled + 512;
  if (sample < 0) sample = 0;
  if (sample > 1023) sample = 1023;

  buffer[indexBuf] = sample;
  indexBuf++;
  if (indexBuf >= N) indexBuf = 0;
}