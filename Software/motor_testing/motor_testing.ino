#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Arduino.h>
#include <ArduinoQueue.h>
#include <Wire.h>
#include <SparkFun_Qwiic_OTOS_Arduino_Library.h>
#include <Servo.h>

Adafruit_MotorShield motorShield = Adafruit_MotorShield();
Adafruit_DCMotor *motorL = motorShield.getMotor(1);
Adafruit_DCMotor *motorR = motorShield.getMotor(2);
Servo servoL;
Servo servoR;

QwiicOTOS myOtos;

// Speed settings
const int forwardSpeed = 86; // Adjust for your servo's neutral point
const int turnSpeed = 60;    // Adjust for turning
const int stopSpeed = 86;    // Neutral position

// Maze movement parameters
const int cellDistance = 1000; // Time to move one cell forward (ms)
const int turnTime = 500;      // Time to turn 90 degrees (ms)

void setup() {
  motorShield.begin();
  servoL.attach(10);
  servoR.attach(9);

  stopMotors();
  delay(20000); // Wait before starting
    // Example movement sequence (modify as needed)
    moveForward();
    delay(cellDistance);
    turnLeft();
    delay(turnTime);
    moveForward();
    delay(cellDistance);
    turnRight();
    delay(turnTime);
    moveForward();
    delay(cellDistance);
    stopMotors();
  // Initialize serial communication
  Serial.begin(115200);
  Serial.println("Qwiic OTOS Example 1 - Basic Readings");

  Wire.begin();

  // Attempt to begin the sensor
  while (myOtos.begin() == false)
  {
      Serial.println("OTOS not connected, check your wiring and I2C address!");
      delay(1000);
  }

  Serial.println("OTOS connected!");

  Serial.println("Ensure the OTOS is flat and stationary, then enter any key to calibrate the IMU");

  // Clear the serial buffer
  while (Serial.available())
      Serial.read();
  // Wait for user input
  while (!Serial.available())
      ;

  Serial.println("Calibrating IMU...");

  // Calibrate the IMU, which removes the accelerometer and gyroscope offsets
  myOtos.calibrateImu();

  // Reset the tracking algorithm - this resets the position to the origin,
  // but can also be used to recover from some rare tracking errors
  myOtos.resetTracking();

  
}

void loop() {
  // Check if the encoder value has changed
  //servoL.write(180);
  /*
  for(int i = 0; i < 1000; i++)
  {
    // Get the latest position, which includes the x and y coordinates, plus the
    // heading angle
    sfe_otos_pose2d_t myPosition;
    myOtos.getPosition(myPosition);

    // Print measurement
    Serial.println();
    Serial.println("Position:");
    Serial.print("X (Inches): ");
    Serial.println(myPosition.x);
    Serial.print("Y (Inches): ");
    Serial.println(myPosition.y);
    Serial.print("Heading (Degrees): ");
    Serial.println(myPosition.h);
    delay(1);

  }

  //servoL.write(0);
  while(true)
  {
    delay(100);
  }
  */
}
// Function to move forward
void moveForward() {
    servoL.write(forwardSpeed + 30);
    servoR.write(forwardSpeed - 30);
}

// Function to turn left
void turnLeft() {
    servoL.write(forwardSpeed-30);
    servoR.write(forwardSpeed-30);
}

// Function to turn right
void turnRight() {
    servoL.write(forwardSpeed+30);
    servoR.write(forwardSpeed+30);
}

// Function to stop motors
void stopMotors() {
    servoL.write(stopSpeed);
    servoR.write(stopSpeed);
}
