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
int lastButtonState = 0; // Variable to store the previous state of the button
int selectedServo = 0;   // Variable to store the selected servo (1 or 2 or 3)
int numTimes = 0;        // Variable to store the number of times to run the motion code

HX711 scale;
unsigned long buzzerStartTime = 0; // Variable to store the time when the weight last became non-zero
bool buzzerActive = false; // Flag to track if the buzzer is currently active

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
      // Stop the buzzer
      noTone(BUZZER_PIN);
      buzzerActive = false;
    }
  }

  // Add a delay to prevent continuous checks
  delay(1000); // Adjust as needed to control the frequency of weight checks

  // servos

  if (Serial.available() >= 2) { // Check if there are at least 2 characters available
    char servoSelection = Serial.read(); // Read the servo selection (A, B, or C)

    // Process servo selection
    switch(servoSelection) {
      case 'A':
        selectedServo = 1; // Set selected servo to 1 (servo A)
        Serial.println("Servo A selected.");
        break;
      case 'B':
        selectedServo = 2; // Set selected servo to 2 (servo B)
        Serial.println("Servo B selected.");
        break;
      case 'C':
        selectedServo = 3; // Set selected servo to 3 (servo C)
        Serial.println("Servo C selected.");
        break;
      default:
        Serial.println("Invalid servo selection.");
        return; // Exit loop if servo selection is invalid
    }

    // Read the number of times
    char timesInput = Serial.read(); // Read the first digit of the number
    if (timesInput >= '1' && timesInput <= '5') {
      numTimes = timesInput - '0'; // Convert character to integer
      Serial.print(numTimes);
      Serial.println(" times selected.");
    } else {
      Serial.println("Invalid number of times.");
      return; // Exit loop if number of times is invalid
    }

    // Wait for the button press
    while (digitalRead(BUTTON_PIN) == LOW) {
      // Wait for the button to be released
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

