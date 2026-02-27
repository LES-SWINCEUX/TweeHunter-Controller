#include "Communication.h"

#include <Arduino.h>
#include <ArduinoJson.h>

// Variable externe définie ailleurs
extern int nbBalles;

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

  if (strcmp(type, "config") == 0) {
    if (doc.containsKey("nb_balles")) {
      nbBalles = doc["nb_balles"];
      envoyerStatus();
    }
  }

  if (strcmp(type, "command") == 0) {
    const char* cmd = doc["cmd"];

    if (strcmp(cmd, "remove_ball") == 0) {
      if (nbBalles > 0) nbBalles--;
      envoyerStatus();
    }

    if (strcmp(cmd, "reset") == 0) {
      nbBalles = 0;
      envoyerStatus();
    }
  }
}

void envoyerStatus() {
  StaticJsonDocument<200> doc;

  doc["type"] = "status";
  doc["nb_balles"] = nbBalles;

  serializeJson(doc, Serial);
  Serial.println();
}

void envoyerJoystick(int x, int y) {
  JsonDocument doc;

  doc["type"] = "joystick";
  doc["x"] = x;
  doc["y"] = y;

  serializeJson(doc, Serial);
  Serial.println();
}