#ifndef JOYSTICK_H
#define JOYSTICK_H

class joyStick {
 private:
  int xVal;
  int yVal;

 public:
  joyStick();
  void lireValeur(int pinX, int pinY);
  int getX();
  int getY();

  // void afficherValeurTerminal() ;
};

#endif