const int TEMP = A0;
const int LIGHT = A1;
const int POTEN = A3;


void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(LIGHT);
  float temp = map(sensorValue, 0, 1024, -55.26, 471.05);
  Serial.println(sensorValue);
  delay(100);
}
