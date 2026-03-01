#ifndef MILLIS_TIMER_H
#define MILLIS_TIMER_H

#include "Arduino.h"

class MillisTimer {
private:
    unsigned long lastMillis;
    unsigned long currentMillis;
    unsigned long interval;

public:
    MillisTimer(unsigned long interval);
    void reset();
    bool finished();
};

#endif