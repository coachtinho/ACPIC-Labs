// Schmitt variables
#define VREF 1000
#define H 10

// Duration of light: 10s
#define DURATION 10000

// Pins for reading coords
// If left disconnected, reading is random
// VCC = 1
// GND = 0
#define X0 2
#define X1 3
#define X2 4
#define Y0 5
#define Y1 6
#define Y2 7

// Intensity levels
#define FULL 255
#define HALF 128
#define QUARTER 64

// Digital pins to light LEDs
#define RED_OUT 9
#define GREEN_OUT 10

// Ananlog pins to detect faults
#define RED_FAULT A3
#define GREEN_FAULT A2

// Analog pin for reading ambient light
#define AMBIENT A0

// Digital pins to detect movement
#define RED_MOVE 11
#define GREEN_MOVE 12

// LED coords
int redX;
int redY;
int greenX;
int greenY;

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


void setup() {
  Serial.begin(9600);

  // Set pin modes
  pinMode(RED_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);
  pinMode(RED_MOVE, INPUT_PULLUP);
  pinMode(GREEN_MOVE, INPUT_PULLUP);
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
  int redSensor = digitalRead(RED_MOVE);
  int greenSensor = digitalRead(GREEN_MOVE);
  int ambientSensor = analogRead(AMBIENT);
  Serial.println(ambientSensor);

  // Decide actions
  // Eventually have to deal with predictable movement
  if (redSensor == LOW) {
    redEvent = MOVEMENT;
  } else {
    redEvent = NOTHING;
  }
  
  if (greenSensor == LOW) {
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

    case ADJACENT:
      redStart = millis();
      redTarget = HALF;
      break;
      
    default:
      break;
  }

  long elapsed = millis() - redStart;
  analogWrite(RED_OUT, redTarget * (elapsed < DURATION));
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

  long elapsed = millis() - greenStart;
  analogWrite(GREEN_OUT, greenTarget * (elapsed < DURATION));
}
