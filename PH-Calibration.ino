// Define the analog pin for the pH sensor
const int pHSensorPin = A2;  // Pin where the pH sensor is connected

// Calibration constants for pH sensor (These values may need adjustment for your sensor)
const float neutralVoltage = 2.5;  // Expected voltage at pH 7 (calibrate with a pH 7 buffer)
const float slope = 0.18;  // Voltage difference per pH unit, based on your sensor's calibration

float pHValue = 0.0;
int sensorValue = 0;
float voltage = 0.0;

void setup() {
  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the analog value from the pH sensor
  sensorValue = analogRead(pHSensorPin);
  
  // Convert the sensor value to voltage (since the Arduino's ADC range is 0-1023, corresponding to 0-5V)
  voltage = sensorValue * (5.0 / 1023.0); 
  
  // Calculate the pH value
  // pH value = (measured voltage - neutral voltage) / slope + 7
  pHValue = (voltage - neutralVoltage) / slope + 7;

  // Output the voltage and pH value to the Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.print(" V, pH Value: ");
  Serial.println(pHValue);

  // Delay for a second before taking another reading
  delay(1000);
}
