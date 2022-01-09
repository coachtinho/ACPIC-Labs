int analogPin = A3;
int val = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin );
  
  // Serial.println(val);
  if (val == 1023) // Open circuit detected
    Serial.println("Led's broken!");

  delay(200);

}
