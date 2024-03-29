// // main.cpp
// #include <Arduino.h>
// #include "sensors/Light_Sensor/LightSensor.h"
// #include "sensors/Temp_Humid_Sensor/temphumid.h"
// //#include "sensors/IR_pillsout_servo/IRservo.h"
// #include <ESP32Servo.h>


// const int ldrPin = A7; // LDR connected to pin A7
// const int ledPin = 2;  // LED connected to pin D2
// const int dhtPin = A6;     // DHT sensor connected to pin A6
// const int dhtType = DHT22; // DHT sensor type
// const int irPin = 4; 
// const int servoPin = 10;

// //LightSensor lightSensor(ldrPin, ledPin);
// //TemperatureHumiditySensor tempHumidSensor(dhtPin, dhtType);
// //IRservo IRservom(irPin, servoPin);
// Servo IRSERVO;

// void setup() {

//     Serial.println("initialising"); 
//     IRSERVO.attach(servoPin);
//     //pinMode(servoPin, OUTPUT);
//     Serial.begin(9600);

// }

// void loop() {
//         Serial.println("Moving servo"); 
//             //(digitalRead(_irPin) == HIGH) {
//         // If the IR sensor detects something, move the servo motor to 90 degrees backward
//     for (int i = 180; i >= 0; i--) {
//         IRSERVO.write(i);    
//         delay(15); // Adjust the delay as needed for smooth motion
//     }
//         delay(1000); // Optional delay between backward and forward motion
        
//         // Move the servo motor to 90 degrees forward
//     for (int i = 0; i <= 180; i++) {
//         IRSERVO.write(i);
//         delay(15); // Adjust the delay as needed for smooth motion
//     }
       

//     delay(1000); // Optional delay to avoid continuous triggering
//     }
    
