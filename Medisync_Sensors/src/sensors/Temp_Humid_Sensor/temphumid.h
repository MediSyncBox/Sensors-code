// TemperatureHumiditySensor.h
#ifndef TemperatureHumiditySensor_h
#define TemperatureHumiditySensor_h

#include <Arduino.h>
#include <DHT.h>

class TemperatureHumiditySensor {
public:
    TemperatureHumiditySensor(int dhtPin, int dhtType);

    void initialize();
    void readSensor();

private:
    int _dhtPin;
    int _dhtType;
    DHT _dht;

};

#endif
