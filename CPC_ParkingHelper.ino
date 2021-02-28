#include <Adafruit_CircuitPlayground.h>
#include "Adjuster.h"
#include "UltrasonicSensor.h"
#include "Display.h"

const int trigPin = 10;
const int echoPin = 9;
const int MINIMUM_SAFE_DISTANCE = 15*2.54;
const int DELAY = 250;

UltrasonicSensor usensor(trigPin, echoPin);
Display pixels;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);      // Open serial channel at 115200 baud rate
  CircuitPlayground.begin();
  usensor.start();
  pixels.start();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int d = usensor.getDistance();
  Serial.print("Distance: ");
  Serial.println(d);
  if (d < MINIMUM_SAFE_DISTANCE){
    pixels.alert();
  } else {
    Serial.print("distance ");
    Serial.println(d);
    pixels.graph((d - MINIMUM_SAFE_DISTANCE)/10, CircuitPlayground.strip.Color(0, 255, 0));
  }
  delay(DELAY*2);
}
