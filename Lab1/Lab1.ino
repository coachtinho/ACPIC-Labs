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
  pinMode(LED_BUILTIN, OUTPUT); // use builtin LED as paused indicator

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
  wait(1000); // wait 1000ms
}

// Function to blink the LED
void blink(int led, int duration) {
  digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
  wait(duration); // wait 1000ms
  digitalWrite(led, LOW); // turn the LED off by making the voltage low
}

// Our interpretation of the guide is that the system remains paused between button presses
// and not while the button is pressed
void wait(int duration) {
  unsigned int current_time = millis();
  bool paused = false;

  while (millis() - current_time < duration) {
  
    // Toggle paused state when button is pressed
    if (digitalRead(BUTTON) == HIGH) {
      paused = !paused;
      duration -= millis() - current_time; // Deduct already elapsed time from duration
      delay(500); // Buffer wait to allow button to depress
    }
    
    // Freeze time when state is paused
    if (paused) {
      digitalWrite(LED_BUILTIN, HIGH);
      current_time = millis();
    } else {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}
