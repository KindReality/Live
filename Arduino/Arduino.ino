void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(9);
  sensorValue = map(sensorValue, 525, 230, 0, 100);
  if (sensorValue < 0)
  {
    sensorValue = 0;
  }
  if (sensorValue > 100)
  {
    sensorValue = 100;
  }
  Serial.println(sensorValue);
  delay(1);        // delay in between reads for stability
}
