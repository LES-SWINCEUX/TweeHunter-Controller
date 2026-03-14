#ifndef BOUTONSMANETTE_H
#define BOUTONSMANETTE_H

#include <Arduino.h>

class Boutons {
 public:
  Boutons(int pinGachette, int pinReload);

  void begin();
  void update();

  bool gachettePressed();
  bool reloadPressed();

 private:
  int _pinGachette;
  int _pinReload;

  bool _gachetteState;
  bool _reloadState;

  bool _lastGachetteState;
  bool _lastReloadState;
};

#endif