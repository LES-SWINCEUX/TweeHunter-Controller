#include "BoutonsManette.h"

Boutons::Boutons(int pinGachette, int pinReload) {
  _pinGachette = pinGachette;
  _pinReload = pinReload;
}

void Boutons::begin() {
  pinMode(_pinGachette, INPUT_PULLUP);
  pinMode(_pinReload, INPUT_PULLUP);

  _gachetteState = digitalRead(_pinGachette);
  _reloadState = digitalRead(_pinReload);

  _lastGachetteState = _gachetteState;
  _lastReloadState = _reloadState;
}

void Boutons::update() {
  _gachetteState = digitalRead(_pinGachette);
  _reloadState = digitalRead(_pinReload);
}

bool Boutons::gachettePressed() {
  bool event = false;

  if (_lastGachetteState == HIGH && _gachetteState == LOW) {
    event = true;
  }

  _lastGachetteState = _gachetteState;
  return event;
}

bool Boutons::reloadPressed() {
  bool event = false;

  if (_lastReloadState == HIGH && _reloadState == LOW) {
    event = true;
  }

  _lastReloadState = _reloadState;
  return event;
}