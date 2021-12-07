const int GREEN = 5;
const int RED = 4;
const int BLUE = 3;
const int YELLOW = 2;
const int BUTTON = 11;

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(GREEN, LOW); // turn the LED off (LOW is the voltage level)
  digitalWrite(RED, LOW); // turn the LED off (LOW is the voltage level)
  digitalWrite(BLUE, LOW); // turn the LED off (LOW is the voltage level)
  digitalWrite(YELLOW, LOW); // turn the LED off (LOW is the voltage level)
}

void loop() {
  // 1st
  blink(RED, 1000);

  // 2nd
  blink(GREEN, 1000);

  // 3rd
  blink(BLUE, 1000);

  // 4th
  blink(YELLOW, 1000);

  // 5th
  delay(1000); // wait 1000ms
}

void blink(int led, int duration) {
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
  delay(duration); // wait 1000ms
  digitalWrite(led, LOW); // turn the LED off by making the voltage low
}
