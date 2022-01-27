// Duration of light: 10s
const int DURATION = 10000;

// LED coords
int redX;
int redY;
int greenX;
int greenY;

// Pins for reading coords
// If left disconnected, reading is random
// VCC = 1
// GND = 0
const int X0 = 2;
const int X1 = 3;
const int X2 = 4;
const int Y0 = 5;
const int Y1 = 6;
const int Y2 = 7;

// Intensity levels
const int FULL = 255;
const int HALF = 128;
const int QUARTER = 64;

// Digital pins to light LEDs
const int RED_OUT = 9;
const int GREEN_OUT = 10;

// Ananlog pins to detect faults
const int RED_FAULT = A3;
const int GREEN_FAULT = A2;

// Digital pins to detect movement
const int RED_MOVE = 11;
const int GREEN_MOVE = 12;

// Times at which the LEDs lit up
long redStart = -1;
long greenStart = -1;

// Target intensities for each LED
int redTarget = QUARTER;
int greenTarget = QUARTER;

// Events for LEDs
// The callback onReceive function should set these variables
int redEvent;
int greenEvent;

// Possible events
enum Event {
  TIME = 0,
  MOVEMENT = 1,
  PREDICT = 2,
  ADJACENT = 3,
  NOTHING = 4,
  FAIL = 254,
  OK = 255
};


bool isFirst = true;

void setup() {
  Serial.begin(9600);

  // Set pin modes
  pinMode(RED_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);
  pinMode(RED_MOVE, INPUT);
  pinMode(GREEN_MOVE, INPUT);
  pinMode(X0, INPUT);
  pinMode(X1, INPUT);
  pinMode(X2, INPUT);
  pinMode(Y0, INPUT);
  pinMode(Y1, INPUT);
  pinMode(Y2, INPUT);

  // Turn off LEDs
  digitalWrite(RED_OUT, LOW);
  digitalWrite(GREEN_OUT, LOW);
  
  readCoords();
}

void loop() {
  // Read sensors
  int greenSensor;
  int redSensor;
  // Could not get button to work
  // in order to simulate event
  // only the first loop iteration detects movement
  if (isFirst) {
    isFirst = false;
    redSensor = HIGH; //digitalRead(RED_MOVE);
    greenSensor = HIGH; //digitalRead(GREEN_MOVE);
  } else {
    redSensor = LOW; //digitalRead(RED_MOVE);
    greenSensor = LOW; //digitalRead(GREEN_MOVE);
  }

  // Decide actions
  // Eventually have to deal with predictable movement
  if (redSensor == HIGH) {
    redEvent = MOVEMENT;
  } else {
    redEvent = NOTHING;
  }
  
  if (greenSensor == HIGH) {
    greenEvent = MOVEMENT;
  } else {
    greenEvent = NOTHING;
  }

  // Perform actions
  redLED();
  greenLED();
  
  delay(100);
}

void readCoords() {
  redX = digitalRead(X0) + digitalRead(X1) * 2 + digitalRead(X2) * 4;
  redY = digitalRead(Y0) + digitalRead(Y1) * 2 + digitalRead(Y2) * 4;

  greenX = redX + 1;
  greenY = redY;
}

void redLED() {
  // Do red event
  switch (redEvent) {
    case MOVEMENT:
      // Do math for day/night
      // Send to other devices
      redStart = millis();
      redTarget = FULL;
      break;

    switch ADJACENT:
      redStart = millis();
      redTarget = HALF;
      break;
      
    default:
      break;
  }

  // Perform fade effect
  long elapsed = millis() - redStart;
  float percentage = (float) elapsed / (float) DURATION;
  float multiplier = constrain(percentage, 0, 1);
  analogWrite(RED_OUT, redTarget * (1 - multiplier));
}

void greenLED() {
  // Do green event
  switch (greenEvent) {
    case MOVEMENT:
      // Do math for day/night
      // Send to other devices
      greenStart = millis();
      greenTarget = FULL;
      break;

    case ADJACENT:
      greenStart = millis();
      greenTarget = HALF;
      break;
      
    default:
      break;
  }

  // Perform fade effect
  long elapsed = millis() - greenStart;
  float percentage = (float) elapsed / (float) DURATION;
  float multiplier = constrain(percentage, 0, 1);
  analogWrite(GREEN_OUT, greenTarget * (1 - multiplier));
}
