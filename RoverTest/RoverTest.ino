
#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>


Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *RMotor = AFMS.getMotor(1);
Adafruit_DCMotor *LMotor = AFMS.getMotor(2);

Servo myservo;  // create servo object to control a servo

int defaultspeed = 90; //60(low) to 255(max)
int pos = 0;    // variable to store the servo position


void setup() 
{
  AFMS.begin();
  RMotor->setSpeed(defaultspeed); 
  LMotor->setSpeed(defaultspeed);
  myservo.attach(9);  // pin 10 for Servo 1 and pin 9 for Servo 2
}

void loop() {
  RMotor->run(FORWARD);
  LMotor->run(FORWARD);
  
  delay(1000);  //how long motor is on for

  RMotor->run(RELEASE);
  LMotor->run(RELEASE);

  delay(1000);
  
  RMotor->run(BACKWARD);
  LMotor->run(FORWARD);

  delay(1000);
  
  RMotor->run(RELEASE);
  LMotor->run(RELEASE);

  delay(1000);
  

}
