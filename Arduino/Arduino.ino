#define FASTLED_ALLOW_INTERRUPTS 0
#include <FastLED.h>
FASTLED_USING_NAMESPACE
CRGB leds[4];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812B,10,GRB>(leds, 4).setCorrection( TypicalLEDStrip );
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 2000);
}

int sensorValue;
String inputString;

int onTime = -1;
int minimum = 50;
int channel = 1;
int lastToggleTime = micros();
bool toggleState = true;
void loop() {
  while(Serial.available()) {
    inputString = Serial.readString();
    channel = inputString.substring(1,3).toInt();
    minimum = inputString.substring(4,7).toInt();
    Serial.print("Channel:");
    Serial.print(channel);
    Serial.print(" Minimum:");
    Serial.println(minimum);
  }
  
  EVERY_N_MILLISECONDS(20) {
    Serial.println(minimum);
    if (sensorValue < minimum)
    {
      if (millis() - lastToggleTime > 10000)
      {
        lastToggleTime = millis();
        toggleState != toggleState;
      }
      if (toggleState)
      {
        fill_solid(leds, 4, CRGB( map(sensorValue, 100, 0, 0, 255), 0, map(sensorValue, 0, 100, 0, 255))); 
      }
      else 
      {
        fill_solid(leds, 4, CRGB(0, 0, 0));   
      }
      
    }
    else 
    {
      fill_solid(leds, 4, CRGB( map(sensorValue, 100, 0, 0, 255), 0, map(sensorValue, 0, 100, 0, 255)));
    }    
    FastLED.show();
  }
  sensorValue = map(analogRead(9), 525, 230, 0, 100); 
  if (sensorValue < 0)
  { 
    sensorValue = 0;
  }
  if (sensorValue > 100)
  {
    sensorValue = 100;
  }
  delay(1);        // delay in between reads for stability
}
