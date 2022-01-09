#include <Wire.h>

#define VREF 26
#define H 2

double vcmp = VREF;

const int TEMP = A0;
const int LIGHT = A1;
const int POTEN = A3;
const int BUS = 8;


void setup() {
  Wire.begin();
  // Serial.begin(9600);
}

void loop() {
  // Read light intensity
  char light = readSensorToByte(LIGHT);

  // Read potentiometer
  char poten = readSensorToByte(POTEN);

  // Read teperature
  char temp = readTemperature(TEMP);


  // Transmit data to slave
  Wire.beginTransmission(BUS);
  Wire.write(light);
  Wire.write(poten);
  Wire.write(temp);
  Wire.endTransmission();
  
  delay(100);
}

// Maps value of a sensor into a byte
char readSensorToByte(int sensor) {
  int sensorValue = analogRead(sensor);
  
  // Sensor goes from 0 to 1024, byte goes from 0 to 255
  char result = map(sensorValue, 0, 1024, 0, 256);

  return result;
}

// Maps value from temperature sensor to real temperature
char readTemperature(int sensor) {
  char out;
  int sensorValue = analogRead(sensor);

  // Sensor goes from 0 to 1024, temperature values was derived from reading the datasheet
  double temp = map(sensorValue, 0, 1024, -48.77, 444.82);

  // Schmitt trigger
  if (temp < vcmp) {
    out = 0;
    vcmp = VREF + H/2;
  } else {
    out = 1;
    vcmp = VREF - H/2;
  }

  return out;
}
