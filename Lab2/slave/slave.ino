#include <Wire.h>

const int YELLOW = 4;
const int RED = 3;
const int BLUE = 2;
const int BUS = 8;
const int TEMP_THRES = 0;

int lightValue = 0;
int blinkTime = 0;
boolean blinkState = false;
int tempBool = 0;


unsigned long last_change = 0;


void setup()
{
  Wire.begin(BUS);
  Wire.onReceive(callbackFunction);

  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); // use builtin LED as paused indicator

  digitalWrite(YELLOW, LOW); // turn the LED off (LOW is the voltage level)
  digitalWrite(RED, LOW);    // turn the LED off (LOW is the voltage level)
  digitalWrite(BLUE, LOW);   // turn the LED off (LOW is the voltage level)

  Serial.begin(9600);

  last_change = millis();
}

void loop()
{
  redLED();
  yellowLED();
  blueLED();
}

void redLED() {
  analogWrite(RED, lightValue);
}

void yellowLED() {
  if (millis() - last_change >= blinkTime) {
    blinkState = !blinkState;
    digitalWrite(YELLOW, blinkState  ? HIGH : LOW);
    last_change = millis();
  }
}

void blueLED() {
  digitalWrite(BLUE, tempBool>0 ? HIGH : LOW);
}

void callbackFunction(int i) {
  while (Wire.available()) {
    // Read light sensor - RED LED
    int c = Wire.read(); // read the next byte as a char
    //Serial.println(c);
    lightValue = 255 - c;
    //Serial.write("Light");
    // Serial.println(lightValue);

    // Read potentiometer sensor - YELLOW LED
    c = Wire.read(); // read the next byte as a char
    blinkTime = map(c, 0, 256, 1, 500);
    //Serial.write("Blink");
    //Serial.println(blinkTime);


    // Read temperature sensor - BLUE LED
    c = Wire.read(); // read the next byte as a char
    tempBool = c;
    Serial.println(tempBool);
    
  }
}
