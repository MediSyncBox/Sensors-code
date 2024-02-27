// // IRcount.h
#ifndef IRcounting_h
#define IRcounting_h

#include <Arduino.h>

class IRcounting {
public:
    IRcounting(int ircountPin);
    
    void initialize();
    void readSensor();

private:
    int _ircountPin;
};

#endif