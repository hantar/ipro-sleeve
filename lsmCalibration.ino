// Libraries
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_Sensor.h>

// i2c (accelerometer/compass/gyro)
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

// Variables
const int ledPin = 9;
float x = 0;
float y = 0;
float z = 0;
float xyz = 0;
float xZ = 1300;

float minX = 0;
float maxX = 0;
float minY = 0;
float maxY = 0;
float minZ = 0;
float maxZ = 0;

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
  pinMode(ledPin, OUTPUT);
}
void loop() {
  lsm.read(); // grab data off i2c
  /* ------ Sample Data ------
    for (int i = 0; i < 1000; i++) {
    lsm.read();
    if (lsm.accelData.x < minX) minX = lsm.accelData.x;
    if (lsm.accelData.x > maxX) maxX = lsm.accelData.x;
    if (lsm.accelData.y < minY) minY = lsm.accelData.y;
    if (lsm.accelData.y > maxY) maxY = lsm.accelData.y;
    if (lsm.accelData.z < minZ) minZ = lsm.accelData.z;
    if (lsm.accelData.z > maxZ) maxZ = lsm.accelData.z;
    }
    Serial.println(" ");
    Serial.print(minX); Serial.print(" , "); Serial.println(maxX);
    Serial.print(minY); Serial.print(" , "); Serial.println(maxY);
    Serial.print(minZ); Serial.print(" , "); Serial.println(maxZ);
    delay(1000);
  */
  //digitalWrite(ledPin, HIGH);
  if (lsm.accelData.x > 0) { 
    digitalWrite(ledPin, HIGH);
    Serial.println("HIGH");
  }
  if (lsm.accelData.x < 0) {
    digitalWrite(ledPin, LOW);
    Serial.println("low");
  }
  
  /*------ Calibration ------/
    for (int i = 0; i < 9600; i++) {
    x = lsm.accelData.x + x;
    }
    x = x / 9600;
    //x = map(x, -25000, 25000, -100, 100);
    //x = lsm.accelData.x;
    y = lsm.accelData.y;
    z = lsm.accelData.z;
    //x = map(x, -400
    xyz = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    Serial.print("x: "); Serial.println(x);
    Serial.print("y: "); Serial.println(y);
    Serial.print("z: "); Serial.println(z);
    Serial.print("xyz: "); Serial.println(xyz);
    //delay(1000);
    /*/

  /* ----- LSM VARS ------
    lsm.accelData.x
    lsm.accelData.y
    lsm.accelData.z
    lsm.magData.x
    lsm.magData.y
    lsm.magData.z
    lsm.gyroData.x
    lsm.gyroData.y
    lsm.gyroData.z
    lsm.temperature
  */
}
