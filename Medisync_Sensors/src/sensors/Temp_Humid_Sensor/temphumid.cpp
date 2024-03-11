// #include <Arduino.h>
// #include <Wire.h> 
// #include <DHT.h>

// #define DHTPIN A6
// #define DHTTYPE DHT22

// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   Serial.begin(9600); 
//   dht.begin();
// }

// void loop() {

//   float h = dht.readHumidity();
//   float t = dht.readTemperature();

//   // Check if any reads failed and exit early
//   if (isnan(h) || isnan(t)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }

//   // Print DHT sensor data label
//   Serial.println("\n----- DHT Sensor Data -----");

//   // Check temperature and humidity conditions
//   if (t > 30) {
//     Serial.println("Pill box overheat");
//   }

//   if (t < 15) {
//     Serial.println("Pill box underheat");
//   }

//   if (h > 60) {
//     Serial.println("Pill box overhumid");
//   }

//   // Print temperature and humidity readings
//   Serial.print("Humidity: ");
//   Serial.print(h);
//   Serial.print(" %\t");
//   Serial.print("Temperature: ");
//   Serial.print(t);
//   Serial.println(" *C");

//   // Delay before next iteration
//   delay(2000);
// }

// TemperatureHumiditySensor.cpp
#include "temphumid.h"

TemperatureHumiditySensor::TemperatureHumiditySensor(int dhtPin, int dhtType) : _dhtPin(dhtPin), _dhtType(dhtType), _dht(dhtPin, dhtType) {}

void TemperatureHumiditySensor::initialize() {
    Serial.begin(9600);
    _dht.begin();
}

void TemperatureHumiditySensor::readSensor() {
    float h = _dht.readHumidity();
    float t = _dht.readTemperature();

    // Check if any reads failed and exit early
    if (isnan(h) || isnan(t)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    // Check temperature and humidity conditions
    if (t > 30) {
        Serial.println("Pill box overheat");
    }

    if (t < 15) {
        Serial.println("Pill box underheat");
    }

    if (h > 60) {
        Serial.println("Pill box overhumid");
    }

    // Print temperature and humidity readings
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" *C");

    // Delay before next iteration
    delay(500);
}
