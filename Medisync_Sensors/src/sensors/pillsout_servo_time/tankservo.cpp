// tankservo.cpp
#include "tankServo.h"
tankservo::tankservo(int fingerprint_pin, int servoPin) :   _fingerprint_pin(fingerprint_pin), _servoPin(servoPin) {}

void tankservo::initialize() {
    //.attach(_servoPin);
    pinMode(_fingerprint_pin, INPUT);
    servoMotor.attach(_servoPin);
    
}

void tankservo::moveServo() {

    int fingerprintsensorvalue = digitalRead(_fingerprint_pin);

    int getPillsToDispenseFromDatabase() {
        int pillsToDispense = fetchPillTakingSchedule();
        return pillsToDispense; 
    }

    if (fingerprintsensorvalue == HIGH){

        pillsToDispense = getPillsToDispenseFromDatabase(); 
    

    for (int j = 0; j < pillsToDispense; j++) {
      for (int i = 0; i <= 180; i++) {
        servoMotor.write(i);    
        delay(15); // Adjust the delay as needed for smooth motion
      }
      delay(1000); // Optional delay between backward and forward motion
      
      // Move the servo motor to 90 degrees forward
      for (int i = 180; i >= 0; i--) {
        servoMotor.write(i);
        delay(15); // Adjust the delay as needed for smooth motion
      }
      delay(1000);
        }
    }
}


