// TemperatureHumiditySensor.h
#ifndef TemperatureHumiditySensor_h
#define TemperatureHumiditySensor_h

#include <Arduino.h>
#include <DHT.h>

class TemperatureHumiditySensor { // class define
public:
    TemperatureHumiditySensor(int dhtPin, int dhtType); //constructor including the attributes

    void initialize(); 
    void readSensor();

private:
    int _dhtPin;
    int _dhtType;
    DHT _dht;

};

#endif
