#include <Wire.h>

const int BUS = 8;
const int TRIES = 10;
const char PAYLOAD = 'A';

const int bufferSize[] = {1, 2, 3, 4, 20, 30, 40, 50, 60, 70, 80, 90, 100};
int bufferIndex = 0;
int currentTry = 0;
int status = 0;
unsigned long startTime = 0;
unsigned long stopTime = 0;

void setup()
{
  Wire.begin();
  Serial.begin(9600);
}

void loop()
{
  if (currentTry >= TRIES)
  {
    if (bufferIndex == sizeof(bufferSize) / sizeof(int))
    {
      bufferIndex = 0;
    }
    else
    {
      bufferIndex++;
    }
    currentTry = 0;
  }
  currentTry++;

  // Transmit data to slave
  Wire.beginTransmission(BUS);
  for (int i = 0; i < bufferSize[bufferIndex]; i++)
    Wire.write(PAYLOAD);

  startTime = micros();
  status = Wire.endTransmission();
  stopTime = micros();

  if (status == 0)
  {
    Serial.print(bufferSize[bufferIndex]);
    Serial.print(" bytes sent, transmission time: ");    
    Serial.println(stopTime - startTime);
  }
  else
  {
    Serial.print("Transmission failed: ");
    Serial.println(status);
  }

  delay(2000);
}
