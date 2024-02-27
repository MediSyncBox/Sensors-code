// #include <Arduino.h>
// #include <Wire.h> 

// // put function declarations here:
// const int ldrPin = A7; // LDR connected to pin A7
// const int ledPin = 2;  // LED connected to pin D2


// void setup() {
//   Serial.begin(9600); 
//   pinMode(A7, INPUT);
//   pinMode(2, OUTPUT);
// }

// void loop() {
//   int ldrValue = analogRead(ldrPin);
//   Serial.print("LDR Value: ");
//   Serial.println(ldrValue);

//   if (ldrValue <=5) {
//     digitalWrite(ledPin,   HIGH);
//     } else {
//       digitalWrite(ledPin,   LOW);
//     }
  
//   delay(500);
// }

// LightSensor.cpp
#include "LightSensor.h"

// Constructor
LightSensor::LightSensor(int ldrPin, int ledPin) : _ldrPin(ldrPin), _ledPin(ledPin) {}

// Member function to initialize the sensor
void LightSensor::initialize() {
    pinMode(_ldrPin, INPUT);
    pinMode(_ledPin, OUTPUT);
    Serial.begin(9600);
}

// Member function to read sensor values
void LightSensor::readSensor() {
    int ldrValue = analogRead(_ldrPin);
    Serial.print("LDR Value: ");
    Serial.println(ldrValue);

    if (ldrValue <= 5) {
        digitalWrite(_ledPin, HIGH);
    } else {
        digitalWrite(_ledPin, LOW);
    }

    delay(500);
}