# 🎮 Manette de jeu — Firmware embarqué (Arduino Mega / PlatformIO)

## 📌 Description
Ce dépôt contient le firmware embarqué de la manette de jeu développée dans le cadre du projet universitaire.

La manette est basée sur un Arduino Mega 2560 et communique avec l’ordinateur via USB filaire.
Le firmware est programmé en C/C++ Arduino sous PlatformIO.

Cette section du projet couvre exclusivement :
- Acquisition des entrées physiques (boutons, joystick, gâchettes, accéléromètre)
- Traitement des signaux
- Communication USB avec l’ordinateur
- Architecture logicielle embarquée

---

## 🧰 Environnement de développement

### Logiciels requis
- VS Code
- Extension PlatformIO IDE
- Git

### Installation
1. Installer VS Code
2. Installer l’extension PlatformIO IDE
3. Cloner le dépôt :

```bash
git clone https://github.com/LES-SWINCEUX/TweeHunter-Controller
cd TweeHunter-Controller
```

4. Ouvrir le dossier dans VS Code
5. PlatformIO configurera automatiquement l’environnement

---

## ⚙️ Configuration matérielle

### Microcontrôleur
- Arduino Mega 2560
- Communication USB filaire avec PC

### Entrées utilisateur
La manette comporte :
- Boutons poussoirs numériques
- Joystick analogique (X, Y)
- Gâchettes analogiques
- Accéléromètre

### Capteurs et contrôles
| Élément | Type | Interface |
|--------|------|-----------|
| Boutons | Numérique | GPIO |
| Joystick | Analogique | ADC |
| Gâchettes | Analogique | ADC |
| Accéléromètre | Numérique | I2C |

---

## 📁 Structure du projet
include/  → headers  
src/      → code principal  
lib/      → librairies  
test/     → tests  
platformio.ini  
README.md  

---

## 🧠 Architecture logicielle
Le firmware fonctionne en boucle temps réel :

1. Lecture des entrées physiques
2. Filtrage et anti-rebond
3. Conversion analogique-numérique
4. Lecture accéléromètre
5. Traitement des données
6. Transmission USB vers PC

Structure principale :

```cpp
void setup() {
    // Logique d'initialisation
    // ...
}

void loop() {
    // Logique en boucle
    // ...
}
```

---

## 📍 Attribution des pins (exemple)
À adapter selon votre schéma final.

| Composant | Pin Arduino Mega |
|-----------|------------------|
| Bouton A | D22 |
| Bouton B | D23 |
| Bouton X | D24 |
| Bouton Y | D25 |
| Joystick X | A0 |
| Joystick Y | A1 |
| Gâchette gauche | A2 |
| Gâchette droite | A3 |
| Accéléromètre SDA | 20 |
| Accéléromètre SCL | 21 |

---

## 🔧 Compilation et téléversement

Compiler :
pio run

Upload :
pio run --target upload

Moniteur série :
pio device monitor

---

## 📡 Communication USB
Transmission :
- États boutons
- Joystick
- Gâchettes
- Accéléromètre

Exemple :
BTN:1,0,0,1 | JX:512 | JY:530 | LT:300 | RT:280 | AX:0.02 | AY:-0.98 | AZ:0.10

---

## 🧪 Procédure de test
- Tester tous les boutons
- Vérifier joystick
- Vérifier gâchettes
- Vérifier accéléromètre
- Vérifier communication USB

---

# 🗺️ Roadmap — Manette de jeu (Partie électronique & firmware)

## 🔵 Phase 1 — Définition des besoins
**Objectif :** définir l’architecture complète

- Choix du microcontrôleur (Arduino Mega)  
- Liste des entrées : boutons, joystick, gâchettes, accéléromètre  
- Type de communication : USB filaire  
- Nombre de pins nécessaires  
- Diagramme bloc du système  
- Répartition des tâches équipe  

**Livrables :**
- Diagramme bloc  
- Liste composants  
- Pin mapping initial  

---

## 🟡 Phase 2 — Conception électronique
**Objectif :** concevoir le circuit

- Mapping officiel des pins Arduino  
- Schéma électrique  
- Pull-up boutons  
- Connexion joystick  
- Connexion gâchettes  
- Connexion accéléromètre (I2C)  
- Gestion alimentation USB  

**Tests :**
- Validation breadboard  
- Test individuel des composants  

**Livrables :**
- Schéma final  
- Prototype breadboard fonctionnel  

---

## 🟠 Phase 3 — Développement firmware de base
**Objectif :** lecture des entrées

- Setup PlatformIO  
- Lecture boutons  
- Lecture joystick  
- Lecture gâchettes  
- Lecture accéléromètre  
- Debug Serial Monitor  

**Tests :**
- Chaque capteur fonctionne seul  
- Valeurs stables  

**Livrables :**
- Code lecture complet  
- Debug série fonctionnel  

---

## 🔴 Phase 4 — Traitement des données
**Objectif :** fiabiliser les entrées

- Anti-rebond boutons  
- Filtrage analogique  
- Calibration joystick  
- Calibration accéléromètre  
- Normalisation des valeurs  

**Livrables :**
- Code stable  
- Valeurs propres  
- Calibration documentée  

---

## 🟣 Phase 5 — Communication PC
**Objectif :** envoyer les données au PC

- Protocole série USB  
- Format des trames  
- Fréquence d’envoi  
- Tests réception côté PC  
- Optimisation latence  

**Livrables :**
- Communication stable  
- Protocole documenté  

---

## 🟢 Phase 6 — Intégration finale hardware
**Objectif :** manette complète

- Soudure finale  
- Intégration dans boîtier  
- Gestion câbles  
- Tests complets  

**Livrables :**
- Manette fonctionnelle  
- Prototype final  

---

## ⚫ Phase 7 — Optimisation finale
**Objectif :** version finale universitaire

- Optimisation latence  
- Code modulaire propre  
- Documentation GitHub  
- README final  
- Diagrammes architecture  

---

## 📅 Timeline

**Semaines 1–2 :** Architecture et schéma  
**Semaines 3–4 :** Breadboard et tests capteurs  
**Semaines 5–6 :** Firmware complet  
**Semaines 7–8 :** Communication PC et intégration  
**Semaines 9+ :** Optimisation et démo finale  

---

## 👤 Auteur

Développé par les GOAT **Vincent Gravel**, **Vadym Dupuis**, **Owen Le Bolloch**, **Médérik Vachon** et **Justin Brunelle**

---

## 📝 Contexte académique
Projet universitaire en systèmes embarqués : conception et programmation complète d’une manette physique pour TweeHunter.