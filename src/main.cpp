#include <Arduino.h>
#include <LiquidCrystal.h>

#include "Accel.h"
#include "AffichageNbBalles.h"
#include "BoutonsManette.h"
#include "Communication.h"
#include "JoyStick.h"
#include "Millis_Timer.h"
#include "Muon.h"
#include "incremental.h"

// LCD
const int RS = 12, EN = 11, D4 = 7, D5 = 6, D6 = 5, D7 = 4;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

#define MENU_BALLES 0
#define MENU_SCORE 1
#define MENU_EQUIPEMENT 2

// 7SEG
int segPins[7] = {31, 30, 35, 34, 33, 32, 37};
AffichageNbBalles affichage(segPins);

// accel
Accel accel(A2, A3, A4);

joyStick js;
Boutons boutons(28, 27);
bool comboLastState = false;

// Moeteur
int Start_Moteur = 0;
unsigned long tempsMoteur = 0;
bool moteurActif = false;

// VARIABLES JEU
int nbBalles = 0;
int score = 0;
int equipement = 1;

int menuActif = 0;
int lastMenu = -1;

// frequence envoie joystick
unsigned long lastSend = 0;
const unsigned long interval = 25;  // 40 Hz

const int pinDELRouge = 25;
const int pinDELVert = 24;

// gestion flash LED tir
unsigned long ledRougeTimer = 0;
bool ledRougeActive = false;
const int ledDuration = 100;  // ms

// Ajout pour fix l'affichage lcd
int lastScore = -1;
int lastBalles = -1;
int lastEquipement = -1;

unsigned long ledVertTimer = 0;
bool ledVertActive = false;

// swinceur
int swince = 0;
bool swinceActive = false;
const int pinSwince = 40;

void setup() {
  Serial.begin(115200);
  Serial3.begin(9600);

  // encodeur
  setup_encoder(2, 3);

  affichage.begin();

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("init");
  delay(1000);
  lcd.clear();

  pinMode(pinDELRouge, OUTPUT);
  pinMode(pinDELVert, OUTPUT);
  pinMode(23, OUTPUT);  // Pin moteur
  pinMode(pinSwince, OUTPUT);
  boutons.begin();
  initCommunication();
  initMuon();

  digitalWrite(pinSwince, LOW);

  // digitalWrite(pinDELVert, HIGH);
}

void loop() {
  // Com PC
  handleSerial();
  nbBalles = getNb_balles();

  js.lireValeur(A1, A0);
  updateMuon(analogRead(A7));  // A7 en dernier

  // MAJ 7 segments
  affichage.setNbBalles(nbBalles);
  affichage.update();

  // LCD MENU (rafraîchit seulement si menu change)
  if (menuActif != lastMenu || score != lastScore || nbBalles != lastBalles ||
      equipement != lastEquipement) {
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
    lastScore = score;
    lastBalles = nbBalles;
    lastEquipement = equipement;
  }

  // Gestion Bouton
  boutons.update();

  if (boutons.gachettePressed()) {
    digitalWrite(pinDELRouge, HIGH);
    ledRougeTimer = millis();
    ledRougeActive = true;
  }
  int lecture = read_encoder();

  envoyerBouton(boutons.gachettePressed(), boutons.reloadPressed(),
                accel.readValues().isActive, lecture);

  // extinction automatique LED tir
  if (ledRougeActive && millis() - ledRougeTimer > ledDuration) {
    digitalWrite(pinDELRouge, LOW);
    ledRougeActive = false;
  }

  // Joystick valeur en continu
  unsigned long currentTime = millis();

  if (currentTime - lastSend >= interval) {
    lastSend = currentTime;

    // js.lireValeur(A1, A0);
    envoyerJoystick(js.getX(), js.getY());
  }

  // Encodeur pour menu
  // int lecture = read_encoder();

  if (lecture == 1) {
    menuActif++;

    if (menuActif > 2) menuActif = 0;
  }

  if (lecture == -1) {
    menuActif--;

    if (menuActif < 0) menuActif = 2;
  }

  // Serial.println(menuActif);

  // Moteur vibranb

  if (Start_Moteur == 1 && !moteurActif) {
    moteurActif = true;
    tempsMoteur = millis();
    digitalWrite(23, HIGH);
    Start_Moteur = 0;
  }

  if (moteurActif && millis() - tempsMoteur >= 2000) {
    digitalWrite(23, LOW);
    moteurActif = false;
  }

  if (muonSeuilAtteint) {
    envoyerMuon();
    digitalWrite(pinDELVert, HIGH);
    ledVertTimer = millis();
    ledVertActive = true;
    muonSeuilAtteint = false;
  }

  if (ledVertActive && millis() - ledVertTimer > 200) {
    digitalWrite(pinDELVert, LOW);
    ledVertActive = false;
  }

  //  mets une pin a high pour envoyer la commande de swincer
  if (getSwinceVal() == 1 && swinceActive == false) {
    swinceActive = true;
    Serial3.println("SWINCE_FULL");
    MillisTimer(10000);  // delay pour effectuer la swince
    swinceActive = false;
    resetSwinceVal();
  }
}
