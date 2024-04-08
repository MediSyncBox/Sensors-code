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
const int dhtPin1 = A3;
const int dhtPin2 = A4;
const int dhtPin3 = A5;     // DHT sensor connected to pin A6
const int dhtType = DHT22; // DHT sensor type
const int weightPin = A6;
const int buzzerPin = 5;
//const int fingerprint_pin = 9; 
//const int servoPin = 6;


LightSensor lightSensor1(ldrPin1, ledPin1, 1);
LightSensor lightSensor2(ldrPin2, ledPin2, 2);
LightSensor lightSensor3(ldrPin3, ledPin3, 3);
TemperatureHumiditySensor tempHumidSensor1(dhtPin1, dhtType, 1);
TemperatureHumiditySensor tempHumidSensor2(dhtPin2, dhtType, 2);
TemperatureHumiditySensor tempHumidSensor3(dhtPin3, dhtType, 3);
//weightnotify weightsensor(weightPin, buzzerPin);
//tankservo tankservom(fingerprint_pin, servoPin);

const char* ssid;
const char* password;
int boxId;
const char* serverUrl = "https://medisyncconnection.azurewebsites.net/api/setTankInfo/";


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
    tempHumidSensor1.initialize();
    tempHumidSensor2.initialize();
    tempHumidSensor3.initialize();
    //weightsensor.initialize();
    //tankservom.initialize();

}

void loop() {
    lightSensor1.readSensor();
    lightSensor2.readSensor();
    lightSensor3.readSensor();
    tempHumidSensor1.readSensor();
    tempHumidSensor2.readSensor();
    tempHumidSensor3.readSensor();

    
  int tankNumber1;
  float temperature1;
  float humidity1; 
  int lightValue1;
  tempHumidSensor1.getTankData(tankNumber1, temperature1, humidity1);
  lightSensor1.getTankSensorData(tankNumber1, lightValue1);

  int tankNumber2;
  float temperature2;
  float humidity2; 
  int lightValue2;
  tempHumidSensor2.getTankData(tankNumber2, temperature2, humidity2);
  lightSensor2.getTankSensorData(tankNumber2, lightValue2);

  int tankNumber3;
  float temperature3;
  float humidity3; 
  int lightValue3;
  tempHumidSensor3.getTankData(tankNumber3, temperature3, humidity3);
  lightSensor3.getTankSensorData(tankNumber3, lightValue3);
  
  // Create JSON payload
  String payload = "[";
  payload += "{\"tankNumber\":" + String(tankNumber1) + ",\"temperature\":" + String(temperature1) + ",\"humidity\":" + String(humidity1) + ",\"lightValue\":" + String(lightValue1) + "},";
  payload += "{\"tankNumber\":" + String(tankNumber2) + ",\"temperature\":" + String(temperature2) + ",\"humidity\":" + String(humidity2) + ",\"lightValue\":" + String(lightValue2) + "},";
  payload += "{\"tankNumber\":" + String(tankNumber3) + ",\"temperature\":" + String(temperature3) + ",\"humidity\":" + String(humidity3) + ",\"lightValue\":" + String(lightValue3) + "}";
  payload += "]";

  // Append box ID to the server URL
  String url = serverUrl + String(boxId);
    // Send HTTP POST request
  HTTPClient http;
  http.begin(url);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
        String response = http.getString();
        Serial.println("HTTP POST response:");
        Serial.println(httpResponseCode);
        Serial.println(response);
    } else {
        Serial.println("HTTP POST request failed");
    }
  http.end();

  delay(5000);
 

    
    
    }
    
