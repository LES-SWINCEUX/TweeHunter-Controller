#include <swinceur.h>

Swinceur::Swinceur(int extend_pin, int retract_pin){
    this->extend_pin = extend_pin;
    this->retract_pin = retract_pin;

    pinMode(extend_pin, OUTPUT);
    pinMode(retract_pin, OUTPUT);

    digitalWrite(extend_pin, LOW);
    digitalWrite(retract_pin, LOW);
}

void Swinceur::fullSwince(){
    //extend 5.5 sec
    digitalWrite(retract_pin, LOW);
    delay(100);
    digitalWrite(extend_pin, HIGH); 
    delay(5500);
    digitalWrite(extend_pin, LOW); 

    // Pause 1 s
    delay(1000);

    // Retract 5.5 s
    digitalWrite(extend_pin, LOW);
    delay(100);
    digitalWrite(retract_pin, HIGH); 
    delay(5500);
    digitalWrite(retract_pin, LOW);  
}

void Swinceur::partialSwince(int time){
    swinceTime += time;
    if (swinceTime < 5.5){
        digitalWrite(retract_pin, LOW);
        delay(100);
        digitalWrite(extend_pin, HIGH); 
        delay(time*1000);
        digitalWrite(extend_pin, LOW);
    }

    else {
        // Pause 1 s
        delay(1000);

        // Retract 5.5 s
        digitalWrite(extend_pin, LOW);
        delay(100);
        digitalWrite(retract_pin, HIGH); 
        delay(5500);
        digitalWrite(retract_pin, LOW);
    }
}
