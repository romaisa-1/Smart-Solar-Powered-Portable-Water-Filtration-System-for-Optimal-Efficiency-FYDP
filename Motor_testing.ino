// Motor control pins for Motor 1
const int motor1EnablePin = 5;  // PWM pin for motor 1 speed control
const int motor1Pin1 = 6;       // Control pin 1 for motor 1
const int motor1Pin2 = 7;       // Control pin 2 for motor 1

void setup() {
  // Set motor control pins as outputs
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
}

void loop() {
  // Motor at full speed (255) for 2 seconds
  motorControl(255, HIGH, LOW);
  delay(2000);

  // Motor at medium speed (150) for 3 seconds
  motorControl(150, HIGH, LOW);
  delay(3000);

  // Motor at low speed (75) for 4 seconds
  motorControl(75, HIGH, LOW);
  delay(4000);

  // Stop the motor
  motorControl(0, LOW, LOW);
  delay(2000); // Motor stays stopped for 2 seconds before repeating
}

// Function to control the motor
void motorControl(int speed, int dir1, int dir2) {
  analogWrite(motor1EnablePin, speed);  // Set the motor speed using PWM
  digitalWrite(motor1Pin1, dir1);        // Set the motor direction
  digitalWrite(motor1Pin2, dir2);        // Set the motor direction
}
