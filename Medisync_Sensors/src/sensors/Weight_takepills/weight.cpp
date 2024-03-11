// #include <Arduino.h>
// #include <Wire.h> 
// #include <DHT.h>
#include "weight.h"

weightnotify::weightnotify(int weightPin, int buzzerPin) : _weightPin(weightPin), _buzzerPin(buzzerPin), _timer(0) {}

void weightnotify::initialize() {
    pinMode(_weightPin, INPUT);
    pinMode(_buzzerPin, OUTPUT);
}

void weightnotify::checkWeight() {

    int weight = analogRead(_weightPin);

    if (weight > 10) { // If weight is detected
        if (_timer == 0) { // If timer is not running
            _timer = millis(); // Start the timer
        }
        if (millis() - _timer >= 300000) { // If 5 minutes have passed
            Serial.println("Please take your pills!"); // Notify the user to take pills
            digitalWrite(_buzzerPin, HIGH); // Turn on the buzzer
        }
    } else { // If weight is 0
        _timer = 0; // Reset the timer
        digitalWrite(_buzzerPin, LOW); // Turn off the buzzer
    }
}

