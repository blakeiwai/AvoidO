# Project-AvoidO
Autonomous rover that detects incoming obstacles and chooses the best path around.

## Process:

1. Design Chassis Assembly in Solidworks

   * Assembly comes complete with housing for all electronic components
2. Drive the motors and use the sweeping ultrasonic function
3. Assemble and test robot

   * Fine-tune motors to drive in a straight line
### Final Assembly of Robot

![finalproduct](https://user-images.githubusercontent.com/109624276/209011483-974c34bf-84ae-4801-a71a-f2e3e1f66a8e.jpg)

## Approximate Rover Radius
![roverradius](https://user-images.githubusercontent.com/109624276/209019045-7b107efd-9642-4583-9cb6-770a47c04432.jpg)


## Sweep Function Test

Use this section to test out how to code the ultrasonic sensor and implement it with the Arduino and micro servo. The annotated code below shows which pins to connect to on the board (ensure the VCC pin is connected to 5V) as well as how each block works.

```
// Blake Iwaisako
// 11 August 2022

#include <Servo.h>

Servo sweepServo;

const int trig = 12;  // Trig pin 
const int echo = 13;  // Echo pin
int pos = 0;          // Initial position integer
long dur;             // Initialize long variables: duration of ultrasonic pulse 
long tocm;            // microseconds to cm variable
bool returningToZero; // Create boolean for returning to zero

void setup() {
  Serial.begin(9600);        // Connect to serial monitor
  pinMode(echo, INPUT);      // echo pin corresponds to "echo" on Ultrasonic Sensor
  pinMode(trig, OUTPUT);     // "trig" pin on sensor
  sweepServo.attach(9);
  sweepServo.write(0);
}

bool objectDetected(long tocm)    // Create boolean to detect object 
{
  if (tocm < 20)     // Any objects within 20 cm will be noticed
  {
    return true;
  } else {
    return false;
  }
}

void loop()
{
  digitalWrite(trig, LOW);    // Momentarily turns off trigger
  delayMicroseconds(2);       
  digitalWrite(trig, HIGH);   // Turn on trigger to send a pulse for 
  delayMicroseconds(10);      // 10 microseconds
  digitalWrite(trig, LOW);    // Turn off trigger 
  dur = pulseIn(echo, HIGH);      // Records ultrasonic pulse via the echo pin
  tocm = microsecondsToCentimeters(dur);    // Determine in cm distance of object based on pulse duration
  if (objectDetected(tocm))       // If variable tocm is within 20 cm threshold
  {
    Serial.print("Object detected. Object's distance: ");   // This block prints out the distance of the detected object
    Serial.print(tocm);                                     // and the angle of the servo in which the object was found
    Serial.print(". Servo's angle: ");                      // this stops the servo from sweeping as long as the object is seen
    Serial.println(pos);
  } else {
    if (pos < 180 && returningToZero == false)    // This block rotates the servo in intervals of 10cm back and forth
    {
      sweepServo.write(pos);
      pos += 10;
      Serial.print("Searching for object. Servo's angle: ");
      Serial.println(pos);
      if (pos == 180)                   // When the servo reaches the maximum angle 180 it returns to zero
        returningToZero = true;
    } else if (returningToZero == true) {
      pos -= 10;
      Serial.print("Searching for object. Servo's angle: ");
      Serial.println(pos);
      sweepServo.write(pos);
      if (pos == 0)                    // When the servo reaches minimum angle it returns to zero
        returningToZero = false;    
    }
  }
  delay(200);
}

long microsecondsToCentimeters(long microseconds)   // Converter for microseconds to cm
{
  return microseconds / 29.155 / 2;
}
```


