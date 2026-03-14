#include <Arduino.h>

// ====== MENU DE TEST DES COMPOSANTES ======

char commande;

// ---------- Déclaration des pins ----------
const unsigned long debounceDelayJoy = 1000;

int joyLastReading = HIGH;
int joyStableState = HIGH;
unsigned long joyLastDebounceTime = 0;

// Moteur vibrant
const int pinMoteurVibrant = 23;

// DEL
const int pinDELVerte = 24;
const int pinDELRouge = 25;

// Boutons / interrupteurs
const int pinReload1 = 27;
const int pinReload2 = 27;
const int pinGachette = 28;

// Joystick
const int pinJoyX = A0;
const int pinJoyY = A1;
const int pinJoySW = 33;

// Accéléromètre analogique
const int pinAccelX = A2;
const int pinAccelY = A3;
const int pinAccelZ = A4;

// Encodeur
const int pinEncA = 2;
const int pinEncB = 3;

// ---------- 7 segments ----------
int segments[7] = {30, 31, 32, 33, 34, 35, 36};

// ordre : a b c d e f g
int chiffres[10][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}  // 9
};

// ---------- Déclarations des fonctions ----------
void afficherMenu();

void testMoteurVibrant();
void test7Segments();
void testEncodeur();
void testAccelerometre();
void testJoystick();
void testDELVerte();
void testDELRouge();
void testReload1();
void testReload2();
void testGachette();
bool boutonJoystickAppuyeDebounce();

void afficherChiffre(int n);
void eteindre7Segments();

// =================================================

void setup() {
  Serial.begin(9600);
  delay(1000);

  pinMode(pinMoteurVibrant, OUTPUT);

  pinMode(pinDELVerte, OUTPUT);
  pinMode(pinDELRouge, OUTPUT);

  pinMode(pinReload1, INPUT_PULLUP);
  pinMode(pinReload2, INPUT_PULLUP);
  pinMode(pinGachette, INPUT_PULLUP);

  pinMode(pinJoySW, INPUT);

  pinMode(pinEncA, INPUT_PULLUP);
  pinMode(pinEncB, INPUT_PULLUP);

  for (int i = 0; i < 7; i++) {
    pinMode(segments[i], OUTPUT);
  }

  eteindre7Segments();

  Serial.println("Demarrage...");
  afficherMenu();
}

void loop() {
  if (Serial.available() > 0) {
    commande = Serial.read();

    if (commande == '\n' || commande == '\r') {
      return;
    }

    switch (commande) {
      case '1':
        testMoteurVibrant();
        break;

      case '2':
        test7Segments();
        break;

      case '3':
        testEncodeur();
        break;

      case '4':
        testAccelerometre();
        break;

      case '5':
        testJoystick();
        break;

      case '6':
        testDELVerte();
        break;

      case '7':
        testDELRouge();
        break;

      case '8':
        testReload1();
        break;

      case '9':
        testReload2();
        break;

      case 'a':
      case 'A':
        testGachette();
        break;

      case 'm':
      case 'M':
        afficherMenu();
        break;

      default:
        Serial.println("Commande invalide.");
        Serial.println("Tape M pour reafficher le menu.");
        break;
    }
  }
}

// ================= MENU =================

void afficherMenu() {
  Serial.println();
  Serial.println("==================================");
  Serial.println("       MENU DE TEST ARDUINO       ");
  Serial.println("==================================");
  Serial.println("1  - Moteur vibrant");
  Serial.println("2  - 7 segments");
  Serial.println("3  - Encodeur");
  Serial.println("4  - Accelerometre");
  Serial.println("5  - Joystick");
  Serial.println("6  - DEL verte");
  Serial.println("7  - DEL rouge");
  Serial.println("8  - Reload 1");
  Serial.println("9  - Reload 2");
  Serial.println("A  - Gachette");
  Serial.println("M  - Reafficher le menu");
  Serial.println("==================================");
  Serial.println();
}

// ================= TESTS =================

void testMoteurVibrant() {
  Serial.println("Test moteur vibrant pendant 3 secondes...");
  digitalWrite(pinMoteurVibrant, HIGH);
  delay(3000);
  digitalWrite(pinMoteurVibrant, LOW);
  Serial.println("Test moteur vibrant termine.");
}

void test7Segments() {
  Serial.println("Test 7 segments...");
  Serial.println("Affichage de 0 a 9, 1 seconde par chiffre.");


  afficherChiffre(30);
  /*for (int i = 0; i < 10; i++) {
    afficherChiffre(i);
    delay(1000);*/
  delay(10000);

  eteindre7Segments();
  Serial.println("Test 7 segments termine.");
}

void testEncodeur() {
  Serial.println("Test encodeur pendant 10 secondes...");
  Serial.println("Tourne l'encodeur manuellement.");

  int ancienA = digitalRead(pinEncA);
  unsigned long t0 = millis();

  while (millis() - t0 < 10000) {
    int actuelA = digitalRead(pinEncA);

    if (actuelA != ancienA) {
      if (digitalRead(pinEncB) != actuelA) {
        Serial.println("Sens horaire");
      } else {
        Serial.println("Sens antihoraire");
      }
    }

    ancienA = actuelA;
    delay(2);
  }

  Serial.println("Test encodeur termine.");
}

void testAccelerometre() {
  Serial.println("Test accelerometre pendant 10 secondes...");
  unsigned long t0 = millis();

  while (millis() - t0 < 10000) {
    int x = analogRead(pinAccelX);
    int y = analogRead(pinAccelY);
    int z = analogRead(pinAccelZ);

    Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Z = ");
    Serial.println(z);

    delay(500);
  }

  Serial.println("Test accelerometre termine.");
}

void testJoystick() {
  Serial.println("Test joystick pendant 10 secondes...");
  unsigned long t0 = millis();

  while (millis() - t0 < 10000) {
    int x = analogRead(pinJoyX);
    int y = analogRead(pinJoyY);
    int sw = digitalRead(pinJoySW);

    Serial.print("X = ");
    Serial.print(x);
    Serial.print(" | Y = ");
    Serial.print(y);
    Serial.print(" | Switch = ");

    if (sw == HIGH) {
      Serial.println("Appuye");
    } else {
      Serial.println("Relache");
    }

    delay(500);
    
  }
  Serial.println("Test joystick termine.");
}
/*bool boutonJoystickAppuyeDebounce() {
  int reading = digitalRead(pinJoySW);

  if (reading != joyLastReading) {
    joyLastDebounceTime = millis();
    joyLastReading = reading;
  }

  if ((millis() - joyLastDebounceTime) > debounceDelayJoy) {
    if (reading != joyStableState) {
      joyStableState = reading;

      if (joyStableState == LOW) {
        return true;
      }
    }
  }

  return false;
}
*/
void testDELVerte() {
  Serial.println("Test DEL verte pendant 5 secondes...");

  for (int i = 0; i < 10; i++) {
    digitalWrite(pinDELVerte, HIGH);
    delay(250);
    digitalWrite(pinDELVerte, LOW);
    delay(250);
  }

  Serial.println("Test DEL verte termine.");
}

void testDELRouge() {
  Serial.println("Test DEL rouge pendant 5 secondes...");

  for (int i = 0; i < 10; i++) {
    digitalWrite(pinDELRouge, HIGH);
    delay(250);
    digitalWrite(pinDELRouge, LOW);
    delay(250);
  }

  Serial.println("Test DEL rouge termine.");
}

void testReload1() {
  Serial.println("Test Reload 1 pendant 10 secondes...");
  Serial.println("Appuie sur Reload 1.");

  unsigned long t0 = millis();

  while (millis() - t0 < 10000) {
    if (digitalRead(pinReload1) == LOW) {
      Serial.println("Reload 1 appuye");
    } else {
      Serial.println("Reload 1 relache");
    }
    delay(500);
  }

  Serial.println("Test Reload 1 termine.");
}

void testReload2() {
  Serial.println("Test Reload 2 pendant 10 secondes...");
  Serial.println("Appuie sur Reload 2.");

  unsigned long t0 = millis();

  while (millis() - t0 < 10000) {
    if (digitalRead(pinReload2) == LOW) {
      Serial.println("Reload 2 appuye");
    } else {
      Serial.println("Reload 2 relache");
    }
    delay(500);
  }

  Serial.println("Test Reload 2 termine.");
}

void testGachette() {
  Serial.println("Test gachette pendant 10 secondes...");
  Serial.println("Actionne la gachette.");

  unsigned long t0 = millis();

  while (millis() - t0 < 10000) {
    if (digitalRead(pinGachette) == LOW) {
      Serial.println("Gachette appuyee");
    } else {
      Serial.println("Gachette relachee");
    }
    delay(500);
  }

  Serial.println("Test gachette termine.");
}

// ================= 7 SEGMENTS =================

void afficherChiffre(int n) {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], chiffres[n][i]);
  }
}

void eteindre7Segments() {
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], LOW);
  }
}
