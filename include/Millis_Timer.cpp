#include "Millis_Timer.h"

MillisTimer::MillisTimer(unsigned long interval){
    this->interval = interval;
    lastMillis = millis();
}

void MillisTimer::reset(){
    lastMillis = millis();
}

bool MillisTimer::finished(){
    currentMillis = millis();

    if (currentMillis - lastMillis >= interval){
        lastMillis = currentMillis;
        return true;
    }
    return false;
}