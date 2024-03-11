// main.cpp
#include <Arduino.h>
#include "sensors/Light_Sensor/LightSensor.h"
#include "sensors/Temp_Humid_Sensor/temphumid.h"
#include "sensors/pillsout_servo_time/tankservo.h"
//#include "sensors/IR_finalout/IRout.h"
#include "sensors/Weight_takepills/weight.h"
#include <WiFi.h>

const int ldrPin = A7; // LDR connected to pin A7
const int ledPin = 2;  // LED connected to pin D2
const int dhtPin = A6;     // DHT sensor connected to pin A6
const int dhtType = DHT22; // DHT sensor type
const int fingerprint_pin = 8; 
const int servoPin = 5;
const int weightPin = A5;
const int buzzerPin = 3;


LightSensor lightSensor(ldrPin, ledPin);
TemperatureHumiditySensor tempHumidSensor(dhtPin, dhtType);
weightnotify weightsensor(weightPin, buzzerPin);
tankservo tankservom(fingerprint_pin, servoPin);


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

    lightSensor.initialize();
    tempHumidSensor.initialize();
    weightsensor.initialize();
    tankservom.initialize();

}

void loop() {
    lightSensor.readSensor();
    tempHumidSensor.readSensor();
    weightsensor.checkWeight();
    tankservom.moveServo();
    
    }
    
