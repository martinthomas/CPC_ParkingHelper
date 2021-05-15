// Ultrasonic code here
#ifndef SENSOR_H
#define SENSOR_H

class UltrasonicSensor {
  private:
    int trigP;
    int echoP;

  public:
    UltrasonicSensor(int trigPin, int echoPin){
      trigP = trigPin;
      echoP = echoPin;
    }
    
    ~UltrasonicSensor(){}

    void start(){
      pinMode(trigP, OUTPUT);  // Sets the trigPin as an Output
      pinMode(echoP, INPUT);   // Sets the echoPin as an Input
    }

    float getDistance(){
      digitalWrite(trigP, LOW);   // Makes trigPin low
      delayMicroseconds(2);       // 2 micro second delay 
      
      digitalWrite(trigP, HIGH);  // trigPin high
      delayMicroseconds(10);      // trigPin high for 10 micro seconds
      digitalWrite(trigP, LOW);   // trigPin low
      
      float interval = pulseIn(echoP, HIGH);   //Read echo pin, time in microseconds
      float estDistance= interval*0.034/2;        //Calculating actual/real distance
      return estDistance;
    }
};

#endif
