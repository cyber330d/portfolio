#include <Servo.h>
#include <LiquidCrystal.h>

// Initialize the LCD (RS, E, D4, D5, D6, D7)
LiquidCrystal lcd(12, 11, 10, 8, A1, A2);

// Servo motor for scanning
Servo servoMotor;

// Pin assignments for L298N motor driver (DC motors)
const int motorPin1 = 2;  // IN1 for Motor 1 (Direction)
const int motorPin2 = 3;  // IN2 for Motor 1 (Direction)
const int motorPin3 = 4;  // IN3 for Motor 2 (Direction)
const int motorPin4 = 7;  // IN4 for Motor 2 (Direction)
const int motorSpeed1 = 5; // ENA (PWM) for Motor 1 speed control
const int motorSpeed2 = 6; // ENB (PWM) for Motor 2 speed control

// IR sensor connected to A0
const int irSensorPin = A0;

// Servo motor control pin
const int servoPin = 9;

// Variables to store sensor data and timing for movement
int distanceValue;
int servoAngle = 0;
int movementSpeed = 70;  // Adjust this to control car speed (PWM)

// Setup function
void setup() {
  // Initialize the LCD
  lcd.begin(16, 2);
  lcd.print("Starting...");

  // Servo setup
  servoMotor.attach(servoPin);

  // Set pin modes for motor control
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(motorSpeed1, OUTPUT);
  pinMode(motorSpeed2, OUTPUT);

  // IR sensor setup (analog input)
  pinMode(irSensorPin, INPUT);

  // Initialize motors at low speed
  analogWrite(motorSpeed1, movementSpeed);  // Slow motor 1 speed
  analogWrite(motorSpeed2, movementSpeed);  // Slow motor 2 speed
}

void loop() {
  // Move the car forward slowly
  moveForward();

  // Read the IR sensor value
  distanceValue = analogRead(irSensorPin);

  // Convert the analog value to a readable voltage
  float voltage = distanceValue * (5.0 / 1023.0);
  
  // Display the distance value on the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(0, 1);
  lcd.print(voltage);
  lcd.print(" V");

  // Move the servo slowly for scanning
  scanWithServo();

  // Small delay for stability
  delay(200);
}

// Function to move the car forward
void moveForward() {
  digitalWrite(motorPin1, HIGH);  // Motor 1 forward
  digitalWrite(motorPin2, LOW);   // Motor 1 forward
  digitalWrite(motorPin3, HIGH);  // Motor 2 forward
  digitalWrite(motorPin4, LOW);   // Motor 2 forward
}

// Function to stop the car (if needed)
void stopCar() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
}

// Function to rotate the servo slowly between 0 and 180 degrees
void scanWithServo() {
  // Sweep the servo back and forth slowly for triangulation
  for (servoAngle = 0; servoAngle <= 180; servoAngle += 2) {
    servoMotor.write(servoAngle);  // Set servo angle
    delay(30);  // Delay to control the servo speed
  }
  for (servoAngle = 180; servoAngle >= 0; servoAngle -= 2) {
    servoMotor.write(servoAngle);  // Set servo angle
    delay(30);  // Delay to control the servo speed
  }
}
