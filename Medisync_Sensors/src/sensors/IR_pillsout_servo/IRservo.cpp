// IRservo.cpp
#include "IRServo.h"

IRservo::IRservo(int irPin, int servoPin) :   _irPin(irPin), _servoPin(servoPin) {}

void IRservo::initialize() {
    //.attach(_servoPin);
    pinMode(_irPin, INPUT);
    pinMode(_servoPin, OUTPUT);
}

void IRservo::moveServo() {

    int irSensorValue = digitalRead(_irPin);

    if (irSensorValue == LOW){

    

    for (int i = 180; i >= 0; i--) {
        IRSERVO.write(i);    
        delay(15); // Adjust the delay as needed for smooth motion
    }
        delay(2000); // Optional delay between backward and forward motion
        
        // Move the servo motor to 90 degrees forward
    for (int i = 0; i <= 180; i++) {
        IRSERVO.write(i);
        delay(15); // Adjust the delay as needed for smooth motion
    }
    }
    delay(1000); // Optional delay to avoid continuous triggering
}


