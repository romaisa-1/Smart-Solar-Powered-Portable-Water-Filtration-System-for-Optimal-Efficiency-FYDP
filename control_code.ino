// Pin Definitions 
const int turbidityPin = A0;      // Turbidity sensor analog pin
const int tdsPin = A1;            // TDS sensor analog pin
const int pHpin = A2;             // pH sensor analog pin

const int motor1EnablePin = 5;    // ENA pin for Motor 1 (PWM control)
const int motor1In1Pin = 4;       // IN1 pin for Motor 1 direction

const int motor2EnablePin = 6;    // ENA pin for Motor 2 (PWM control)
const int motor2In1Pin = 7;       // IN1 pin for Motor 2 direction

// Sensor Variables
float voltage = 0.0;
int turbidityValue = 0;
int tdsValue = 0;
int pHValue = 0;
float turbidityNTU = 0.0;
float tdsPPM = 0.0;
float pH = 0.0;

void setup() {
  Serial.begin(9600);

  // Motor 1
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor1In1Pin, OUTPUT);
  digitalWrite(motor1In1Pin, HIGH); // Set direction forward

  // Motor 2
  pinMode(motor2EnablePin, OUTPUT);
  pinMode(motor2In1Pin, OUTPUT);
  digitalWrite(motor2In1Pin, HIGH); // Set direction forward
}

void loop() {
  // Read turbidity sensor
  turbidityValue = analogRead(turbidityPin);
  voltage = turbidityValue * (5.0 / 1023.0);
  turbidityNTU = (3.0 - voltage) * 100.0; // Rough estimate

  // Read TDS sensor
  tdsValue = analogRead(tdsPin);
  voltage = tdsValue * (3.3 / 1023.0);
  tdsPPM = (133.42 * voltage * voltage * voltage) 
           - (255.86 * voltage * voltage) 
           + (857.39 * voltage);

  // Read pH sensor
  pHValue = analogRead(pHpin);
  pH = (pHValue * 5.0 / 1023.0) * 3.5;  // Rough scaling for pH (calibration required)

  // Display sensor values
  Serial.print("Turbidity (NTU): ");
  Serial.print(turbidityNTU);
  Serial.print(" | TDS (ppm): ");
  Serial.print(tdsPPM);
  Serial.print(" | pH: ");
  Serial.print(pH);

  // Decision logic for Motor 1 speed
  int motor1Speed = 0;
  if (turbidityNTU < 100 && tdsPPM < 300) {
    motor1Speed = 255;  // Fast
    Serial.println(" | Water: Clean | Motor1: FAST");
  } else if ((turbidityNTU >= 100 && turbidityNTU < 300) || (tdsPPM >= 300 && tdsPPM < 600)) {
    motor1Speed = 150;  // Medium
    Serial.println(" | Water: Moderate | Motor1: MEDIUM");
  } else {
    motor1Speed = 100;   // Slow
    Serial.println(" | Water: Dirty | Motor1: SLOW");
  }

  // Motor 2 speed is fixed at 200
  int motor2Speed = 200;

  // Control motors
  analogWrite(motor1EnablePin, motor1Speed);
  analogWrite(motor2EnablePin, motor2Speed);

  delay(1000);
}