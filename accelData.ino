/* Version 1.1
   Displays XYZ acceleration and supports openFramework ESP graph software
*/

// Libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

// i2c (accelerometer/compass/gyro)
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

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

// Configurations
const int buttonPin = 4; // Change to whatever Digital Pin button is at
// Don't Modify: 
int sample = 0;
boolean readStat = false;


void setup() {
  Serial.begin(9600);
  delay(500);
  Serial.println("STARTED");
  // Try to initialise and warn if we couldn't detect the chip
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS0 9DOF");  Serial.println("");  Serial.println("");
}

void loop() {
  while (buttonPin == HIGH) {
    lsm.read(); // grab data off i2c
    Serial.print((int)lsm.accelData.x); Serial.print("\t");
    Serial.print((int)lsm.accelData.y); Serial.print("\t");
    Serial.println((int)lsm.accelData.z);
    readStat = true;
  }
  if (readStat == true) {
    sample += 1;
    Serial.print("X\tY\tZ");
    Serial.print("\n----------==========----------\n\t");
    Serial.print("  Sample: "); Serial.print(sample);
    Serial.println("\n----------==========----------\n");
    readStat = false;
  }
}
