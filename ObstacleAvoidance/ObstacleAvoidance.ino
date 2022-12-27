// Implemented by Blake Iwaisako
// 1 August 2022

// Code made available by Micheal Klements from the-diy-life.com

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include "utility/Adafruit_MS_PWMServoDriver.h"
#include <Servo.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 

Adafruit_DCMotor *RFMotor = AFMS.getMotor(4);
Adafruit_DCMotor *LFMotor = AFMS.getMotor(1);
Adafruit_DCMotor *RBMotor = AFMS.getMotor(3);
Adafruit_DCMotor *LBMotor = AFMS.getMotor(2);

Servo sweepServo;

byte trig = 2;                                    //trigger pin
byte echo = 13;                                   //echo pin
byte maxDist = 150;                               //maximum distance for sensing (outside of this distance objects are ignored)
byte stopDist = 50;                               //closest distance to an object allowable
float timeOut = 2*(maxDist+10)/100/134*1000000;   //Max time to wait for return signal

byte motorSpeed = 70;                             //Max motor speed (do not exceed 70)
byte motorOffset = 10;                            //Change to account for one motor being to powerful
int turnSpeed = 60;                               //Amount to add to motor during turns



void setup() {
  AFMS.begin();
  RFMotor->setSpeed(motorSpeed);                   //Set motor speed
  LFMotor->setSpeed(motorSpeed);
  RBMotor->setSpeed(motorSpeed); 
  LBMotor->setSpeed(motorSpeed);

  RFMotor->run(RELEASE);                            //Release all motors before loop
  LFMotor->run(RELEASE);
  RBMotor->run(RELEASE);
  LBMotor->run(RELEASE);

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  sweepServo.attach(10);
}

void loop() 
{
  sweepServo.write(90);                             //Set servo to look straight ahead

  delay(500);
  int distance = getDistance();                     //check for objects directly ahead 
  if(distance >= stopDist)                          //if there are no objects within the stopping distance, move forward
  {
    moveForward();
  }
  while(distance >= stopDist)                       //keep checking the object distance until it is within the minimum stopping distance
  {
    distance = getDistance();
    delay(250);
  }
  stopMove();                                       //stop the motors 
  int turnDir = checkDirection();                   //check the left and right object distances and get the turning instruction
  Serial.print(turnDir);
  switch (turnDir)                                  //turn left, turn around or turn right depending on the instruction 
  {
    case 0:                                         //turn left
      turnLeft(1000);
      break;
    case 1:
      turnLeft(2000);                                //turn around
      break;
    case 2:
      turnRight(1000);                               //turn right
      break;
  }
}

//create functions for movement and scanning

void accelerate()                                   //function to accelerate motors from 0 to full speed
{
  for (int i=0; i<motorSpeed; i++)
  {
    RFMotor->setSpeed(i); 
    LFMotor->setSpeed(i);
    RBMotor->setSpeed(i); 
    LBMotor->setSpeed(i);
    delay(10);
  }
}

void decelerate()                                     //function to decelerate motors from full speed to zero
{
  for(int i=motorSpeed; i!=0; i--)
  {
    RFMotor->setSpeed(i); 
    LFMotor->setSpeed(i);
    RBMotor->setSpeed(i); 
    LBMotor->setSpeed(i);
    delay(10);
  
  }
}

void moveForward()                                     //set all motors to run FORWARD
{
  RFMotor->run(FORWARD); 
  LFMotor->run(FORWARD);
  RBMotor->run(FORWARD); 
  LBMotor->run(FORWARD);
}

void stopMove()                                        //set all motors to stop
{
  RFMotor->run(RELEASE); 
  LFMotor->run(RELEASE);
  RBMotor->run(RELEASE); 
  LBMotor->run(RELEASE);
}

void turnLeft(int duration)                           //set motors to turn left for a certain duration variable
{
  RFMotor->setSpeed(motorSpeed+turnSpeed);            //set motors to turning speed
  LFMotor->setSpeed(motorSpeed+turnSpeed);
  RBMotor->setSpeed(motorSpeed+turnSpeed); 
  LBMotor->setSpeed(motorSpeed+turnSpeed);
  RFMotor->run(FORWARD); 
  RBMotor->run(FORWARD);
  LFMotor->run(BACKWARD);   
  LBMotor->run(BACKWARD);
  delay(duration);
  RFMotor->setSpeed(motorSpeed);                      //bring back to motor speed 
  LFMotor->setSpeed(motorSpeed);
  RBMotor->setSpeed(motorSpeed); 
  LBMotor->setSpeed(motorSpeed);
  RFMotor->run(RELEASE);
  LFMotor->run(RELEASE);
  RBMotor->run(RELEASE);
  LBMotor->run(RELEASE);
}

void turnRight(int duration)
{
  RFMotor->setSpeed(motorSpeed+turnSpeed); 
  LFMotor->setSpeed(motorSpeed+turnSpeed);
  RBMotor->setSpeed(motorSpeed+turnSpeed); 
  LBMotor->setSpeed(motorSpeed+turnSpeed);
  RFMotor->run(BACKWARD); 
  RBMotor->run(BACKWARD);
  LFMotor->run(FORWARD);   
  LBMotor->run(FORWARD);
  delay(duration);
  RFMotor->setSpeed(motorSpeed);                   
  LFMotor->setSpeed(motorSpeed);
  RBMotor->setSpeed(motorSpeed); 
  LBMotor->setSpeed(motorSpeed);
  RFMotor->run(RELEASE);
  LFMotor->run(RELEASE);
  RBMotor->run(RELEASE);
  LBMotor->run(RELEASE);
}

int getDistance()                                       // use snesor to measure distance to an object                                     
{
  unsigned long pulseTime;                              // variable stores pulse travel time
  int distance;                                         // create a variable to store the calculated distance
  digitalWrite(trig, HIGH);                             // generate a 10 microsecond pulse
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  pulseTime = pulseIn(echo, HIGH, timeOut);             // measure time for pulse to return
  distance = (float)pulseTime * 340 / 2 / 10000;        // calculate the object distance on the pulse time 
  return distance; 
}

int checkDirection()                                    // check the left and right directions and decide which way to turn
{
  int distances [2] = {0,0};                            // Left and Right distances 
  int turnDir = 1;                                      // direction to turn, 0 Left, 1 Reverse, 2 Right
  sweepServo.write(180);                                // turn servo to look Left
  delay(500);
  distances [0] = getDistance();                        // get the left object distance
  sweepServo.write(0);                                  // turn servo to look right
  delay(1000);
  distances [1] = getDistance();                        // get the right object distance   
  if (distances[0] >= 200 && distances[1] >= 200)       // if both directions are clear, turn left
    turnDir = 0;
  else if (distances[0] <= stopDist && distances[1]<=stopDist)  // if both directions are blocked, turn around
    turnDir = 1;
  else if (distances[0] >= distances[1])                 // if left has more space, turn left     
    turnDir = 0;
  else if (distances[0]<distances[1])                    // if right has more space, turn right
    turnDir = 2;
  return turnDir;
}
