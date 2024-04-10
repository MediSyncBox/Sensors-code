// main.cpp
#include <Arduino.h>
#include "sensors/Light_Sensor/LightSensor.h"
#include "sensors/Temp_Humid_Sensor/temphumid.h"
#include "sensors/pillsout_servo_time/tankservo.h"
// #include "sensors/IR_finalout/IRout.h"
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
const int dhtPin3 = A5;    // DHT sensor connected to pin A6
const int dhtType = DHT22; // DHT sensor type
const int weightPin = A6;
const int buzzerPin = 5;
// const int fingerprint_pin = 9;
// const int servoPin = 6;

TemperatureHumiditySensor tempHumidSensors[] = {
    TemperatureHumiditySensor(dhtPin1, dhtType, 1),
    TemperatureHumiditySensor(dhtPin2, dhtType, 2),
    TemperatureHumiditySensor(dhtPin3, dhtType, 3)};

LightSensor lightSensors[] = {
    LightSensor(ldrPin1, ledPin1, 1),
    LightSensor(ldrPin2, ledPin2, 2),
    LightSensor(ldrPin3, ledPin3, 3)};

const int numSensors = sizeof(tempHumidSensors) / sizeof(tempHumidSensors[0]);

const char *ssid;
const char *password;
int boxId;
const char *SendToDatabaseUrl = "https://medisyncconnection.azurewebsites.net/api/setTankInfo/";

void setup()
{

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

    for (int i = 0; i < numSensors; i++)
    {
        tempHumidSensors[i].initialize();
        lightSensors[i].initialize();
    }
}

void loop()
{
    for (int i = 0; i < numSensors; i++)
    {
        tempHumidSensors[i].readSensor();
        lightSensors[i].readSensor();

        int tankNumber;
        float temperature;
        float humidity;
        int lightValue;
        tempHumidSensors[i].getTankSensorData(tankNumber, temperature, humidity);
        lightSensors[i].getTankSensorData(tankNumber, lightValue);

        if (!isnan(temperature) && !isnan(humidity))
        {
            String payload = "{\"servo_id\":" + String(tankNumber) + ",\"temperature\":" + String(temperature) + ",\"humidity\":" + String(humidity) + "}";

            Serial.println("Payload:");
            Serial.println(payload);

            String url = SendToDatabaseUrl + String(boxId);

            HTTPClient http;
            http.begin(url);
            http.addHeader("Content-Type", "application/json");
            int httpResponseCode = http.POST(payload);
            if (httpResponseCode > 0)
            {
                String response = http.getString();
                Serial.print("HTTP POST response: ");
                Serial.println(response);
            }
            else
            {
                Serial.print("HTTP POST request failed, error code: ");
                Serial.println(httpResponseCode);
            }
            http.end();
        }
    }
    delay(5000);
}
