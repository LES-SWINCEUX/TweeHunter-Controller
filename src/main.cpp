#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Accel.h"
#include "AffichageNbBalles.h"
#include "BoutonsManette.h"
#include "Communication.h"
#include "JoyStick.h"
#include "incremental.h"

// LCD
const int RS = 12, EN = 11, D4 = 5, D5 = 4, D6 = 3, D7 = 2;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);
#define MENU_BALLES 0
#define MENU_SCORE 1
#define MENU_EQUIPEMENT 2

// 7SEG
int segPins[7] = {30, 31, 32, 33, 34, 35, 36};
AffichageNbBalles affichage(segPins);

// accel
Accel accel(A2, A3, A4);

joyStick js;
Boutons boutons(27, 28);
bool comboLastState = false;

// vARIABLE JEU
int nbBalles = 0;
int score = 0;
int equipement = 1;

int menuActif = 0;
int lastMenu = -1;

// frequence envoie joystick
unsigned long lastSend = 0;
const unsigned long interval = 25;  // 40 Hz

void setup() {
  Serial.begin(115200);

  affichage.begin();

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("init");
  delay(1000);
  lcd.clear();

  boutons.begin();
  initCommunication();
}

void loop() {
  // Com PC
  handleSerial();

  // MAJ 7 segments
  affichage.setNbBalles(nbBalles);
  affichage.update();

  // LCD MENU (rafraîchit seulement si menu change)
  if (menuActif != lastMenu) {
    lcd.clear();
    lcd.setCursor(0, 0);

    switch (menuActif) {
      case MENU_BALLES:
        lcd.print("Balles: ");
        lcd.print(nbBalles);
        break;

      case MENU_SCORE:
        lcd.print("Score: ");
        lcd.print(score);
        break;

      case MENU_EQUIPEMENT:
        lcd.print("Equip: ");
        lcd.print(equipement);
        break;
    }

    lastMenu = menuActif;
  }

  // Gestion Bouton
  boutons.update();

  // état actuel de la combinaison
  bool comboNow = boutons.gachetteState() && boutons.reloadState();

  if (comboNow && !comboLastState) {
    envoyerBouton("menu_pause");
  }

  comboLastState = comboNow;

  // si pas en combo, gérer boutons normaux
  if (!comboNow) {
    if (boutons.gachettePressed()) {
      envoyerBouton("gachette");
    }

    else if (boutons.reloadPressed() && accel.readValues().isActive) {
      envoyerBouton("demande_recharge");
    }
  }
  // Joystick valeur en continu
  unsigned long currentTime = millis();

  if (currentTime - lastSend >= interval) {
    lastSend = currentTime;

    js.lireValeur(A0, A1);
    envoyerJoystick(js.getX(), js.getY());
  }

  // Encodeur pour menu
  int lecture = read_encoder();

  if (lecture == 1) {
    menuActif++;
    if (menuActif > 2) menuActif = 0;
  }

  if (lecture == -1) {
    menuActif--;
    if (menuActif < 0) menuActif = 2;
  }
}