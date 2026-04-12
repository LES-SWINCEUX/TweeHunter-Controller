#ifndef MUON_H
#define MUON_H

#include <Arduino.h>

#define FS 10000
#define N 100
#define SCALE_FACTOR 13
#define THRESHOLD 220
#define DEAD_TIME_US 100
#define SEUIL_MUONS 2  // seuil a ajuter pour le nmbre de x envoyé

extern volatile int buffer[N];
extern volatile uint16_t indexBuf;
extern volatile uint32_t muonCount;
extern volatile bool aboveThreshold;
extern volatile uint32_t lastDetection;

extern volatile bool muonSeuilAtteint;
void initMuon();

extern volatile bool mustRead;
void updateMuon(int rawValue);

#endif