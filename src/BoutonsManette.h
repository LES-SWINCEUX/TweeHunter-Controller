#ifndef BOUTONSMANETTE_H
#define BOUTONSMANETTE_H

#include <Arduino.h>

class Boutons {
 public:
  Boutons(int pinGachette, int pinReload);

  void begin();
  void update();

  // Événements (détection d’appui unique)
  bool gachettePressed();
  bool reloadPressed();

  // États continus (bouton maintenu)
  bool gachetteState();
  bool reloadState();

  unsigned long _lastGachetteTime = 0;
  unsigned long _lastReloadTime = 0;
  const int _debounceDelay = 50;

 private:
  int _pinGachette;
  int _pinReload;

  bool _gachetteState;
  bool _reloadState;

  bool _lastGachetteState;
  bool _lastReloadState;
};

#endif