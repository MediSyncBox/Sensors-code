// LightSensor.h
#ifndef LightSensor_h
#define LightSensor_h

#include <Arduino.h>

class LightSensor {
public:
    LightSensor(int ldrPin, int ledPin);  // Constructor
    void initialize();
    void readSensor();
    
private:
    int _ldrPin;
    int _ledPin;
};

#endif