#include <Wire.h>

#define address(x, y) (x / 2) << 4 | y
#define time() (millis() - avgDelta)

// Schmitt variables
#define VREF 1000
#define H 10

// Duration of light: 10s
#define DURATION 10000

// Pins for reading coords
#define X0 2
#define X1 3
#define X2 4
#define Y0 5
#define Y1 6
#define Y2 7

// Intensity levels
#define FULL 1023
#define HALF 516
#define QUARTER 256

// Digital pins to lamp cells
#define RED_OUT 9
#define GREEN_OUT 10

// Analog pins to detect faults
#define RED_FAULT A3
#define GREEN_FAULT A2

// Analog pin for reading ambient light
#define AMBIENT A0

// Digital pins to detect movement
#define RED_MOVE 11
#define GREEN_MOVE 12

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978
#define REST 0

// change this to make the song slower or faster
int tempo = 114;

// change this to whichever pin you want to use
int buzzer = 8;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Never Gonna Give You Up - Rick Astley
  // Score available at https://musescore.com/chlorondria_5/never-gonna-give-you-up_alto-sax
  // Arranged by Chlorondria

  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 4, NOTE_A4, 8, //7
  NOTE_A5, 8, REST, 8, NOTE_A5, 8, NOTE_E5, -4, REST, 4,
  NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_E5, 8, REST, 8,
  REST, 8, NOTE_CS5, 8, NOTE_B4, 8, NOTE_A4, -4, REST, 4,
  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_A4, 4,
  NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 4, REST, 4,

  NOTE_D5, 2, NOTE_E5, 8, NOTE_FS5, 8, NOTE_D5, 8, //13
  NOTE_E5, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 4, NOTE_A4, 4,
  REST, 2, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8,
  REST, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,

  NOTE_E5, -8, NOTE_E5, -8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, -8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16, //18
  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 8, NOTE_A4, 8, NOTE_A4, 8,
  NOTE_E5, 4, NOTE_D5, 2, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_A5, 4, NOTE_CS5, 8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,

  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 4, NOTE_A4, 8, //23
  NOTE_E5, 4, NOTE_D5, 2, REST, 4,
  REST, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_D5, 8, NOTE_E5, 4, REST, 8,
  REST, 8, NOTE_CS5, 8, NOTE_B4, 8, NOTE_A4, -4, REST, 4,
  REST, 8, NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_A4, 4,
  REST, 8, NOTE_A5, 8, NOTE_A5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_D5, 8,

  REST, 8, NOTE_A4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, //29
  REST, 8, NOTE_CS5, 8, NOTE_B4, 8, NOTE_A4, -4, REST, 4,
  NOTE_B4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, NOTE_A4, 4, REST, 8,
  REST, 8, NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 4, NOTE_E5, -4,
  NOTE_D5, 2, NOTE_D5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 4,
  NOTE_E5, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, 8, NOTE_A4, 8, NOTE_A4, 4,

  REST, -4, NOTE_A4, 8, NOTE_B4, 8, NOTE_CS5, 8, NOTE_D5, 8, NOTE_B4, 8, //35
  REST, 8, NOTE_E5, 8, NOTE_FS5, 8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_FS5, -8, NOTE_FS5, -8, NOTE_E5, -4, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_E5, -8, NOTE_E5, -8, NOTE_D5, -8, NOTE_CS5, 16, NOTE_B4, 8, NOTE_A4, 16, NOTE_B4, 16, NOTE_D5, 16, NOTE_B4, 16,
  NOTE_D5, 4, NOTE_E5, 8, NOTE_CS5, -8, NOTE_B4, 16, NOTE_A4, 4, NOTE_A4, 8,

  NOTE_E5, 4, NOTE_D5, 2, REST, 4
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

// Ambient light threshold
int ambientCmp = VREF;

// Cell coords
int redX;
int redY;
int greenX;
int greenY;

// Cell address
int address;

// Number of synced cells
int synced = 0;
// Time delta between cells
long deltas[8];
long avgDelta = 0;

// Times at which the LEDs lit up
long redStart = -1;
long greenStart = -1;

// Target intensities for each LED
int redTarget;
int greenTarget;

// Events for LEDs
// The callback onReceive function should set these variables
int redEvent;
int greenEvent;

// Possible events
enum Event
{
  TIME = 0,
  MOVEMENT = 1,
  PREDICT = 2,
  ADJACENT = 3,
  NOTHING = 4,
  FAIL = 254,
  OK = 255
};

struct Message
{
  byte targetX;
  byte targetY;
  byte sourceX;
  byte sourceY;
  Event event;
  long time;
};

// Sensor readings
int redSensor;
int greenSensor;
int ambientSensor;

void setup()
{
  // Get start time
  long start = time();
  // Start serial communication
  Serial.begin(9600);
  // Set pin modes
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(RED_OUT, OUTPUT);
  pinMode(GREEN_OUT, OUTPUT);
  pinMode(RED_MOVE, INPUT_PULLUP);
  pinMode(GREEN_MOVE, INPUT_PULLUP);
  pinMode(X0, INPUT_PULLUP);
  pinMode(X1, INPUT_PULLUP);
  pinMode(X2, INPUT_PULLUP);
  pinMode(Y0, INPUT_PULLUP);
  pinMode(Y1, INPUT_PULLUP);
  pinMode(Y2, INPUT_PULLUP);

  digitalWrite(LED_BUILTIN, HIGH);
  // Read cell coordinates
  readCoords();
  // Start I2C communication
  Wire.begin(address);
  Wire.onReceive(receiveEvent);

  // Synchronize with other cells
  syncClock(start);
  digitalWrite(LED_BUILTIN, LOW);

  // Turn off LEDs
  digitalWrite(RED_OUT, LOW);
  digitalWrite(GREEN_OUT, LOW);
}

void loop()
{
  // // Update cell coordinates
  // readCoords();

  // // Read sensors
  // readSensors();

  // // Schmitt trigger to detect daytime
  // if (ambientSensor < ambientCmp) // cloudy or night time
  // {
  //     ambientCmp = VREF + H / 2;
  // }
  // else // day time
  // {
  //     ambientSensor = FULL;
  //     ambientCmp = VREF - H / 2;
  // }

  // // Perform actions
  // redCell(ambientSensor);
  // greenLED();

  while (time() < 8000)
    ;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2)
  {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0)
    {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    }
    else if (divider < 0)
    {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }

  delay(100);
}

void readSensors()
{
  // Read sensors
  redSensor = digitalRead(RED_MOVE);
  greenSensor = digitalRead(GREEN_MOVE);
  ambientSensor = analogRead(AMBIENT);
  // Serial.println(ambientSensor);

  // Decide actions
  // Eventually have to deal with predictable movement
  if (redSensor == LOW)
  {
    redEvent = MOVEMENT;
  }
  else
  {
    redEvent = NOTHING;
  }

  if (greenSensor == LOW)
  {
    greenEvent = MOVEMENT;
  }
  else
  {
    greenEvent = NOTHING;
  }
}

void readCoords()
{
  // Read DIP switch and update cell coordinates
  redX = digitalRead(X0) ^ 1 || (digitalRead(X1) ^ 1) << 1 || (digitalRead(X2) ^ 1) << 2;
  redY = digitalRead(Y0) ^ 1 || (digitalRead(Y1) ^ 1) << 1 || (digitalRead(Y2) ^ 1) << 2;
  Serial.print(redX);
  Serial.print("~");
  Serial.println(redY);

  greenX = redX + 1;
  greenY = redY;

  address = address(redX, redY);
}

void syncClock(long startTime)
{
  // Initialize 8 neighbour coordinates
  int neighbours[][2] = {
    {0, 1},
    {1, 0},
    {0, -1},
    { -1, 0}
  };
  delay(1000);
  Serial.println("Sending messages");
  // Send message from red cell (x,y) and green cell (x+1, y)
  for (int i = 0; i < 2; i++)
  {
    // Send message to all neighbours
    for (int i = 0; i < 4; i++)
    {
      Serial.print("Sending to ");
      Message message;
      message.targetX = redX + i + neighbours[i][0];
      message.targetY = redY + neighbours[i][1];
      Serial.print(message.targetX);
      Serial.print("-");
      Serial.println(message.targetY);

      message.sourceX = redX + i;
      message.sourceY = redY;
      message.event = TIME;
      message.time = time() / 10;

      // Send message
      sendEvent(message);

    }
  }

  Serial.println("waiting for deadline");
  //  Wait for messages from all neighbours
  while (millis() - startTime < 5000 and synced < 8)
    ;

  // calculate average time delta
  for (int i = 0; i < synced; i++)
  {
    Serial.println("adjusting for delta");
    avgDelta += deltas[i];
  }
  avgDelta /= synced;
  avgDelta *= 10;
  Serial.println(avgDelta);
}

void redCell(int ambientSensor)
{
  // Do red event
  switch (redEvent)
  {
    case MOVEMENT:
      // Send to other devices
      redStart = time();
      redTarget = FULL;
      break;

    case ADJACENT:
      redStart = time();
      redTarget = HALF;
      break;

    default:
      break;
  }

  // Adjust brightness according to ambient light
  int intensity = redTarget - ambientSensor;
  intensity = constrain(intensity, 0, 1024);
  intensity = map(intensity, 0, 1024, 0, 256);

  long elapsed = time() - redStart;
  analogWrite(RED_OUT, intensity * (elapsed < DURATION));
}

void greenLED()
{
  // Do green event
  switch (greenEvent)
  {
    case MOVEMENT:
      // Do math for day/night
      // Send to other devices
      greenStart = time();
      greenTarget = FULL;
      break;

    case ADJACENT:
      greenStart = time();
      greenTarget = HALF;
      break;

    default:
      break;
  }

  long elapsed = time() - greenStart;
  analogWrite(GREEN_OUT, greenTarget * (elapsed < DURATION));
}

void sendEvent(Message msg)
{
  if ((msg.targetX == redX && msg.targetY == redY) ||
      (msg.targetX == greenX && msg.targetY == greenY))
  {
    Serial.println("own msg!");
    handleEvent(&msg);
  }
  if (msg.targetX == 255 || msg.targetY == 255) {
    return;
  }

  // Send message over I2C
  Wire.beginTransmission(address(msg.targetX, msg.targetY));
  Wire.write(msg.targetX << 4 | msg.targetY);
  Wire.write(msg.sourceX << 4 | msg.sourceY);
  Wire.write(msg.event);
  Wire.write(msg.time >> 24);
  Wire.write(msg.time >> 16);
  Wire.write(msg.time >> 8);
  Wire.write(msg.time);
  Wire.endTransmission();

  Serial.println("Sent");
}

void handleEvent(Message *msg)

{
  Serial.print("got a msg");
  switch (msg->event)
  {
    case TIME:
      // Update synced
      deltas[synced] = millis() / 10 - msg->time;
      synced++;
      Serial.print(msg->sourceX);
      Serial.print(":");
      Serial.println(msg->sourceY);
      break;
    case MOVEMENT:
      // TODO
      break;
    case PREDICT:
      // TODO
      break;
    case ADJACENT:
      // TODO
      break;
    case NOTHING:
      // TODO
      break;
    case FAIL:
      // TODO
      break;
    case OK:
      // TODO
      break;
    default:
      break;
  }
  free(msg);
}

void receiveEvent(int numBytes)
{
  Message *msg = (Message *)malloc(sizeof(Message));
  while (Wire.available() > 0)
  {
    // Read 8 bits for target cell coordinates
    int cell = Wire.read();
    msg->targetX = cell >> 4;
    msg->targetY = cell & 0x0F;

    // Read 8 bit for source
    int source = Wire.read();
    msg->sourceX = source >> 4;
    msg->sourceY = source & 0x0F;
    // Read 8 bit for event
    msg->event = (Event)Wire.read();
    // Read 32 bit for time
    msg->time = (long)Wire.read() << 24 | (long)Wire.read() << 16 | (long)Wire.read() << 8 | (long)Wire.read();
  }

  handleEvent(msg);
}
