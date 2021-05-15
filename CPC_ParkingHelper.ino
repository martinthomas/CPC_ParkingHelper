#include <Adafruit_CircuitPlayground.h>
#include "Adjuster.h"
#include "UltrasonicSensor.h"
#include "Display.h"

const unsigned int trigPin = 10;
const unsigned int echoPin = 9;

const float INCH_AS_CM = 2.54;
const float SAFE_DISTANCE = 15*INCH_AS_CM; // 15 inches
const float MINIMUM_DISTANCE = 8*INCH_AS_CM;
const float SCARY_DISTANCE = 4*INCH_AS_CM;
const int DELAY = 100;

UltrasonicSensor usensor(trigPin, echoPin);
Display pixels(SCARY_DISTANCE);

void setup() {
  delay(1000);
  // put your setup code here, to run once:
  Serial.begin(115200);
  CircuitPlayground.begin();
  usensor.start();
  pixels.start();
  
}

void loop() {

  pixels.displayDistance(
    usensor.getDistance(), 
    CircuitPlayground.slideSwitch()? MINIMUM_DISTANCE: SAFE_DISTANCE
  );  
  delay(DELAY);
}
