// main.cpp
#include <Arduino.h>
#include "sensors/Light_Sensor/LightSensor.h"
#include "sensors/Temp_Humid_Sensor/temphumid.h"
#include "sensors/IR_pillsout_servo/IRservo.h"
#include "sensors/IR_countpills/IRcount.h"

const int ldrPin = A7; // LDR connected to pin A7
const int ledPin = 2;  // LED connected to pin D2
const int dhtPin = A6;     // DHT sensor connected to pin A6
const int dhtType = DHT22; // DHT sensor type
const int irPin = 8; 
const int servoPin = 5;
const int ircountPin = 12;

LightSensor lightSensor(ldrPin, ledPin);
TemperatureHumiditySensor tempHumidSensor(dhtPin, dhtType);
IRservo IRservom(irPin, servoPin);
IRcounting ircount(ircountPin);


void setup() {
    lightSensor.initialize();
    tempHumidSensor.initialize();
    IRservom.initialize();
    ircount.initialize();
}

void loop() {
    lightSensor.readSensor();
    tempHumidSensor.readSensor();
    IRservom.moveServo();
    ircount.readSensor();
    }
    
