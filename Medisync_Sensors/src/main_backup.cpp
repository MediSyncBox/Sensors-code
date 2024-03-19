// main.cpp
#include <Arduino.h>
#include "sensors/Light_Sensor/LightSensor.h"
#include "sensors/Temp_Humid_Sensor/temphumid.h"
#include "sensors/pillsout_servo_time/tankservo.h"
//#include "sensors/IR_finalout/IRout.h"
#include "sensors/Weight_takepills/weight.h"
#include <WiFi.h>

const int ldrPin1 = A0; // LDR connected to pin A7
const int ledPin1 = 2;  // LED connected to pin D2
const int ldrPin2 = A1; // LDR connected to pin A7
const int ledPin2 = 3;
const int ldrPin3 = A2; // LDR connected to pin A7
const int ledPin3 = 4;
//const int dhtPin1 = A3;
const int dhtPin2 = A4;
const int dhtPin3 = A5;     // DHT sensor connected to pin A6
const int dhtType = DHT22; // DHT sensor type
const int weightPin = A6;
const int buzzerPin = 5;
const int fingerprint_pin = 9; 
const int servoPin = 6;


LightSensor lightSensor1(ldrPin1, ledPin1, 1);
LightSensor lightSensor2(ldrPin2, ledPin2, 2);
LightSensor lightSensor3(ldrPin3, ledPin3, 3);
//TemperatureHumiditySensor tempHumidSensor1(dhtPin1, dhtType, 1);
TemperatureHumiditySensor tempHumidSensor2(dhtPin2, dhtType, 2);
TemperatureHumiditySensor tempHumidSensor3(dhtPin3, dhtType, 3);
//weightnotify weightsensor(weightPin, buzzerPin);
//tankservo tankservom(fingerprint_pin, servoPin);


void setup() {

    Serial.begin(115200);
    delay(1000); // Wait for serial monitor to initialize

    // Print device MAC address
    // uint8_t mac[6];
    // WiFi.macAddress(mac);
    // Serial.print("Device MAC Address: ");
    // for (int i = 0; i < 6; i++) {
    //     Serial.print(mac[i], HEX);
    //     if (i < 5) {
    //         Serial.print(":");
    //     }
    // }
    // Serial.println();

    // // Connect to WiFi
    // Serial.println("Connecting to WiFi...");
    // WiFi.begin(ssid, password);
    // while (WiFi.status() != WL_CONNECTED) {
    //     delay(500);
    //     Serial.print(".");
    // }
    // Serial.println("WiFi connected");

    // // Initialize Azure IoT Hub client
    // iothubClient = IoTHubClient_LL_CreateFromConnectionString(connectionString, MQTT_Protocol);
    // if (iothubClient == NULL) {
    //     Serial.println("Failed to create IoT Hub client handle");
    //     while (1);
    // }
    // IoTHubClient_LL_SetMessageCallback(iothubClient, ReceiveMessageCallback, NULL);

    lightSensor1.initialize();
    lightSensor2.initialize();
    lightSensor3.initialize();
    //tempHumidSensor1.initialize();
    tempHumidSensor2.initialize();
    tempHumidSensor3.initialize();
    //weightsensor.initialize();
    //tankservom.initialize();

}

void loop() {
    lightSensor1.readSensor();
    lightSensor2.readSensor();
    lightSensor3.readSensor();
    //tempHumidSensor1.readSensor();
    tempHumidSensor2.readSensor();
    tempHumidSensor3.readSensor();
    //weightsensor.checkWeight();
    //tankservom.moveServo();
    
    }
    
