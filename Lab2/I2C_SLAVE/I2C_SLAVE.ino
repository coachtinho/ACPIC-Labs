#include <Wire.h>

const int BUS = 8;

void setup()
{
  Wire.begin(BUS);
  Wire.onReceive(callbackFunction);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
}

void callbackFunction(int i)
{
  digitalWrite(LED_BUILTIN, HIGH);
  while (Wire.available())
  { 
    Wire.read();
  }
  digitalWrite(LED_BUILTIN, LOW);
}
