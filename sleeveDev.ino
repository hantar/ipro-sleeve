// Libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

// i2c (accelerometer/compass/gyro)
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

// Variables
const int flexPin = A0;
const int vibPin = 3;
int bendVal = 0;

void setupLSM() {
  // 1.) Set the accelerometer range
  lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_2G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_4G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_6G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_8G);
  //lsm.setupAccel(lsm.LSM9DS0_ACCELRANGE_16G);
  // 2.) Set the magnetometer sensitivity
  lsm.setupMag(lsm.LSM9DS0_MAGGAIN_2GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_4GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_8GAUSS);
  //lsm.setupMag(lsm.LSM9DS0_MAGGAIN_12GAUSS);
  // 3.) Setup the gyroscope
  lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_245DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_500DPS);
  //lsm.setupGyro(lsm.LSM9DS0_GYROSCALE_2000DPS);
}
void setup() {
  pinMode(vibPin, OUTPUT); // Set Vibrating Motor Disc as OUTPUT
  Serial.begin(9600);
  delay(500);
  Serial.println("STARTED");
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS0 9DOF");
  Serial.println("");
  Serial.println("");
}
void loop() {
  bendVal = analogRead(flexPin); // Send Flex value to bendVal
  Serial.println(bendVal); // Output value
  bendVal = map(bendVal, 700, 900, 0, 255); // Convert numerical value range from 700-900 to 0-255 (FIX: Calibrate to equate to degrees)

  //delay(100);
  if (bendVal > 85) { // If within range, vibrate to indicate PERFECT!
    digitalWrite(vibPin, HIGH); // Start vibration
    Serial.print(bendVal); Serial.println("  --  PERFECT!"); // Display value and indicate PERFECT
  } else { // Otherwise, keep displaying degrees in Serial
    digitalWrite(vibPin, LOW); // Stop vibration
    Serial.print("Degrees: "); Serial.print(bendVal); Serial.write(176); Serial.println(""); // Displays degree value
  }
  //bendVal = bendVal + 1;
  lsm.read(); // grab data off i2c
  //Display grouping of data
  Serial.print("Accel X: "); Serial.print((int)lsm.accelData.x);   Serial.println(" ");
  Serial.print("Y: ");       Serial.print((int)lsm.accelData.y);   Serial.println(" ");
  Serial.print("Z: ");       Serial.println((int)lsm.accelData.z); Serial.println(" ");
  Serial.print("Mag X: ");   Serial.print((int)lsm.magData.x);     Serial.println(" ");
  Serial.print("Y: ");       Serial.print((int)lsm.magData.y);     Serial.println(" ");
  Serial.print("Z: ");       Serial.println((int)lsm.magData.z);   Serial.println(" ");
  Serial.print("Gyro X: ");  Serial.print((int)lsm.gyroData.x);    Serial.println(" ");
  Serial.print("Y: ");       Serial.print((int)lsm.gyroData.y);    Serial.println(" ");
  Serial.print("Z: ");       Serial.println((int)lsm.gyroData.z);  Serial.println(" ");
  Serial.print("Temp: ");    Serial.println((int)lsm.temperature); Serial.println(" "); Serial.println(" "); Serial.println(" ");
  delay(500);
}
