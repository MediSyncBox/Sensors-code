// IRservo.h
#ifndef IRservo_h
#define IRservo_h

#include <Arduino.h>
#include <ESP32Servo.h>

class IRservo {
public:
    IRservo(int irPin, int servoPin);  // Constructor
    void initialize();
    void moveServo();
    

private:
    int _irPin;
    int _servoPin;
    Servo IRSERVO;

};

#endif