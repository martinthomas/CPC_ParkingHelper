#include <Adafruit_CircuitPlayground.h>
#include "Adjuster.h"
#include "UltrasonicSensor.h"
#include "Display.h"

const int trigPin = 10;
const int echoPin = 9;
const int MINIMUM_SAFE_DISTANCE = 15*2.54; // 15 inches
const int DELAY = 250;

UltrasonicSensor usensor(trigPin, echoPin);
Display pixels(MINIMUM_SAFE_DISTANCE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  CircuitPlayground.begin();
  usensor.start();
  pixels.start();
  delay(1000);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int d = usensor.getDistance();
  Serial.print("Distance: ");
  Serial.println(d);
  
  pixels.displayDistance(d);
  
  delay(DELAY);
}
