#define TdsSensorPin A0 // TDS sensor connected to A0
#define VREF 5.0        // Reference voltage for Arduino
#define ADC_RES 1024.0  // ADC resolution (10-bit ADC)

void setup() {
  Serial.begin(9600); // Start Serial communication
  pinMode(TdsSensorPin, INPUT); // Set TDS sensor pin as input
}

void loop() {
  int sensorValue = analogRead(TdsSensorPin); // Read analog value
  float voltage = (sensorValue * VREF) / ADC_RES; // Convert to voltage
  float tdsValue = (voltage / 2) * 1000; // Convert to TDS (ppm)

  if (voltage > 4.5 || voltage < 0.1) { // Voltage out of expected range
    Serial.println("Sensor reading out of range. Check connections or water sample.");
  } else {
    // Determine water quality based on TDS value
    String waterQuality;
    if (tdsValue < 300) {
      waterQuality = "Excellent";
    } else if (tdsValue >= 300 && tdsValue < 600) {
      waterQuality = "Good";
    } else if (tdsValue >= 600 && tdsValue < 1000) {
      waterQuality = "Fair";
    } else {
      waterQuality = "Poor";
    }

    // Print results
    Serial.print("Voltage: ");
    Serial.print(voltage, 2);
    Serial.print(" V, TDS: ");
    Serial.print(tdsValue, 2);
    Serial.print(" ppm, Water Quality: ");
    Serial.println(waterQuality);
  }

  delay(1000); // Delay 1 second between readings
}
