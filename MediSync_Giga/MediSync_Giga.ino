#include <Servo.h>

#include "HX711.h"
#include "Arduino_SensorKit.h"

#define BUTTON_PIN 7   // Pin connected to the button
#define SERVO_PIN_1 9  // Pin connected to servo 1
#define SERVO_PIN_2 10 // Pin connected to servo 2
#define SERVO_PIN_3 11 // Pin connected to servo 3

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch
#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2
#define BUZZER_PIN 5 // Define the pin for the buzzer

Servo servo1;      // Initialize servo objects
Servo servo2;
Servo servo3;
int buttonState = 0;     // Variable to store the state of the button
//int lastButtonState = 0; // Variable to store the previous state of the button
int selectedServo = 0;   // Variable to store the selected servo (1 or 2 or 3)

HX711 scale;
unsigned long buzzerStartTime = 0; // Variable to store the time when the weight last became non-zero
bool buzzerActive = false; // Flag to track if the buzzer is currently active
bool servoActivate = false;

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
int boxId;
int tankId;
const char* medicineName;
const char* scheduledTime;
const char* serverUrl = "https://your-azure-webapp.azurewebsites.net/medicine-reminder";
const char* updateUrl = "https://your-azure-webapp.azurewebsites.net/updateMedicineTaken";

void setup() {
  pinMode(BUTTON_PIN, INPUT);    // Set the button pin as input
  pinMode(BUZZER_PIN, OUTPUT);    // Set the buzzer pin as output

  servo1.attach(SERVO_PIN_1); // Attach servo 1 to its pin
  servo2.attach(SERVO_PIN_2); // Attach servo 2 to its pin
  servo3.attach(SERVO_PIN_3); // Attach servo 3 to its pin

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0

  Serial.begin(9600); // Initialize serial communication

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");

  HTTPClient http;
  http.begin(serverUrl);
  
}

void loop() {
  float weight = scale.get_units(); // Get the weight reading
  Serial.print("Reading: ");
  Serial.print(weight, 4); // scale.get_units() returns a float
  Serial.print(" lbs"); // You can change this to kg but you'll need to refactor the calibration_factor
  Serial.println();

  if (weight > 0.001) {
    // Check if the buzzer is not already active
    if (!buzzerActive) {
      buzzerStartTime = millis(); // Start the timer when the weight exceeds 0.01 lbs
      buzzerActive = true;
    } else {
      // Check if 5 minutes have passed since the buzzer started
      if (millis() - buzzerStartTime >= 0.03 * 60 * 1000) { // Convert 5 minutes to milliseconds
        // Trigger the buzzer
        tone(BUZZER_PIN, 1000);
      }
    }
  } else {
    // Weight is not greater than 0.01 lbs
    // Check if the buzzer was active
    if (buzzerActive) {
      selectedServo != -1 // the tank just dispensed 
      // Stop the buzzer
      noTone(BUZZER_PIN);
      buzzerActive = false;

      //update database that the pill was dispensed
      UpdateDatabase();
      //update selectedServo back to -1, ie do not trigger
      selectedServo = -1;
    }
  }

  // Add a delay to prevent continuous checks
  delay(1000); // Adjust as needed to control the frequency of weight checks

  // servos

  // servos

  //read if there is a trigger action: if there is no trigger, it returns -1, if it read a signal, it returns the tankId ie servoMotor id
  servoMotorId = handleMedicineReminder();
  
  if (servoMotorId != -1 && servoMotorId >= 1 && servoMotorId <= 3)  {
  //if (Serial.available() > 0) { // Check if there are characters available
  //  char input = Serial.read(); // Read the input from serial
 //   if (input >= '1' && input <= '3') { // Check if the input is a valid servo number
 //     selectedServo = input - '0'; // Convert character to integer
      selectedServo = servoMotorId;
      Serial.print("Servo ");
      Serial.print(selectedServo);
      Serial.println(" selected. Press the button to trigger.");

      // Wait for the button press
      while (digitalRead(BUTTON_PIN) == LOW) {
        // Wait for the button to be pressed
      }

      int numTimes = 0; // Variable to store the number of times to run the motion code

      // Assign numTimes based on the selected servo
      switch (selectedServo) {
        case 1:
          numTimes = 1; // Set the number of times for servo 1
          break;
        case 2:
          numTimes = 1; // Set the number of times for servo 2
          break;
        case 3:
          numTimes = 3; // Set the number of times for servo 3
          break;
        default:
          Serial.println("Invalid servo selection.");
          break;
      }

      // Trigger the selected servo the specified number of times
      for (int i = 0; i < numTimes; i++) {
        switch (selectedServo) {
          case 1:
            triggerServo(servo1);
            break;
          case 2:
            triggerServo(servo2);
            break;
          case 3:
            triggerServo(servo3);
            break;
          default:
            Serial.println("No servo selected.");
            break;
        }
      }
    } else {
      Serial.println("Invalid servo selection. Enter 1, 2, or 3.");
    }
  }
}

void triggerServo(Servo servo) {
  // Move the servo to a specific angle
  for (int i = 0; i <= 130; i++) {
    servo.write(i);
    delay(15); // Adjust the delay as needed for smooth motion
  }

  delay(1000); // Optional delay between backward and forward motion

  for (int i = 130; i >= 0; i--) {
    servo.write(i);
    delay(15); // Adjust the delay as needed for smooth motion
  }

  delay(1000);
}


int handleMedicineReminder() {

  int httpResponseCode = http.GET();
  
  if (httpResponseCode == HTTP_CODE_OK) {
    String response = http.getString();
    
    DynamicJsonDocument doc(1024);
    DeserializationError error = deserializeJson(doc, response);
    
    if (error) {
      Serial.println("No pills to be dispensed now");
      return -1;
    }
    Serial.println("Pills to dispense in tank");
    //boxId = doc["boxId"];
    tankId = doc["tankId"];
    Serial.println(tankId);
    medicineName = doc["medicineName"];
    scheduledTime = doc["scheduledTime"];
    
    return tankId;

  } else {
    Serial.print("HTTP error code: ");
    Serial.println(httpResponseCode);
    return -1
  }
  
  http.end();
}

void UpdateDatabase(){
  
  String payload = "{\"boxId\":" + String(boxId) + ",\"tankId\":" + String(tankId) + ",\"medicineName\":" + String(medicineName) + ",\"scheduledTime\":" + String(scheduledTime) + "}";

  Serial.println("Payload:");
  Serial.println(payload);

  String url = updateUrl;

  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(payload);
  if (httpResponseCode > 0) {
    String response = http.getString();
    Serial.println("HTTP POST response:")
    Serial.println(httpResponseCode);
    Serial.println(response);
  } else {
    Serial.println("HTTP POST request failed");
  }
  http.end();

}

