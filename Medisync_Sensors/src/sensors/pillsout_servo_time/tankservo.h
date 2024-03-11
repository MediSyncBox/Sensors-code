// tankservo.h
#ifndef tankservo_h
#define tankservo_h

#include <Arduino.h>
#include <ESP32Servo.h>

class tankservo {
public:
    tankservo(int fingerprint_pin, int servoPin);  // Constructor
    void initialize();
    void moveServo();

    

private:
    int _fingerprint_pin;
    int _servoPin;
    Servo servoMotor;

};

#endif