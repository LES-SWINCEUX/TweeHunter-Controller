#include "Communication.h"

#include <Arduino.h>
#include <ArduinoJson.h>

// Variables définies dans main.cpp
extern int score;
extern int equipement;

void traiterMessage(String message);
void envoyerStatus();

String inputBuffer = "";

void initCommunication() { Serial.begin(115200); }

void handleSerial() {
  while (Serial.available()) {
    char c = Serial.read();

    if (c == '\n') {
      traiterMessage(inputBuffer);
      inputBuffer = "";
    } else {
      inputBuffer += c;
    }
  }
}

void traiterMessage(String message) {
  StaticJsonDocument<200> doc;
  DeserializationError error = deserializeJson(doc, message);
  if (error) return;

  const char* type = doc["type"];
  if (!type) return;

  if (strcmp(type, "config") == 0) {
    if (doc["nb_balles"].is<int>()) nbBalles = doc["nb_balles"];

    if (doc["score"].is<int>()) score = doc["score"];

    if (doc["equipement"].is<int>()) equipement = doc["equipement"];
  }
}

void envoyerStatus() {
  StaticJsonDocument<100> doc;

  doc["type"] = "status";
  doc["nb_balles"] = nbBalles;

  serializeJson(doc, Serial);
  Serial.println();
}

void envoyerJoystick(int x, int y) {
  StaticJsonDocument<100> doc;

  doc["type"] = "joystick";
  doc["x"] = x;
  doc["y"] = y;

  serializeJson(doc, Serial);
  Serial.println();
}

void envoyerBouton(const bool gachette, const bool reload, const bool accel,
                   int encodeur) {
  StaticJsonDocument<100> doc;

  doc["type"] = "event";
  if (gachette) {
    doc["btn"] = 1;

  } else {
    doc["btn"] = 0;
  }

  if (reload) {
    doc["btn1"] = 1;

  } else {
    doc["btn1"] = 0;
  }

  if (accel) {
    doc["btn2"] = 1;

  } else {
    doc["btn2"] = 0;
  }

  doc["encodeur"] = encodeur;
  // doc["btn"] = nomBouton;

  serializeJson(doc, Serial);
  Serial.println();
}
// void envoyerBouton1(const bool nomBouton) {
//   StaticJsonDocument<100> doc;

//   doc["type"] = "event1";
//   if (nomBouton) {
//     doc["btn1"] = 1;

//   } else {
//     doc["btn1"] = 0;
//   }
//   // doc["btn"] = nomBouton;

//   serializeJson(doc, Serial);
//   Serial.println();
// }
// void envoyerBouton2(const bool nomBouton) {
//   StaticJsonDocument<100> doc;

//   doc["type"] = "event2";
//   if (nomBouton) {
//     doc["btn2"] = 1;

//   } else {
//     doc["btn2"] = 0;
//   }
//   // doc["btn"] = nomBouton;

//   serializeJson(doc, Serial);
//   Serial.println();
// }
