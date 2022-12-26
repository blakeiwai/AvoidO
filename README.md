# Project *AvoidO*
Autonomous rover that detects incoming obstacles and chooses the best path around. This project is like a small roomba that moves in a straight line until it encounters an obstacle. It then scans the surrounding area and decides the best direction to continue moving in (left, right, or backwards). 

Covid gave me a chance to look at the devices used around my house, such as my roomba or smart security system, in a more critical lense. I got bored and wanted to understand these devices from top-to-bottom. Project *AvoidO* is but one of my several explorations into the innerworkings of common household devices.

Future iterations of this will focus on implementing a cleaning mechanism that either sweeps up or vacuums up debris. The plan is to develop a better roomba than the one currently sold by iRobot.

## Process:

1. Design Chassis Assembly in Solidworks

   * Complete the robot assembly with housing for all electronic components
   * Ultrasonic sensor has to be pointing towards the front end of the chassis and attached to a sweeper servo (90 degrees)
2. Drive the motors and use the sweeping ultrasonic function
3. Assemble and test robot

   * Fine-tune motors to drive in a straight line

## Final Assembly of Robot

![finalproduct](https://user-images.githubusercontent.com/109624276/209011483-974c34bf-84ae-4801-a71a-f2e3e1f66a8e.jpg)

## Components Used:

* Ultrasonic Sensor (HC-SR04)
* 4 x DC Gearbox Motors
* Arduino Uno
* Adafruit Motor Shield v2
* SG90 Servo Motor
* 9 Volt Battery
* Jumper Wires

## Approximate Rover Radius

The red circle is thick on purpose! According to the datasheet, this ultrasonic sensor (HC-SRO4) has an accuracy of 0.3 cm, not bad but I did some testing on my own to verify these results. The range of vision of the AvoidO is set at approximately 30 cm, at this range I found that the sensor exhibited an accuracy of around 0.6 cm. This is most likely due to the extra noise coming from the surrounding environment, the sensor's proximity to the ground, and the imperfect orientation of the echo-trigger sensors along the theta axis (spherical). 

![roverradius](https://user-images.githubusercontent.com/109624276/209019045-7b107efd-9642-4583-9cb6-770a47c04432.jpg)

## Arduino and Adafruit Motor Shield V2:

Refer to the official [website](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-headers) for more detailed information. The Adafruit Motor Shield offers a simple way to drive the servo motors with two dedicated 5V connections. Adafruit has also created an Arduino library that makes communication with the motors very simple

* Ensure you have the Arduino [IDE](https://www.arduino.cc/en/software) installed
* In the IDE make sure you also install the [library](https://learn.adafruit.com/adafruit-motor-shield-v2-for-arduino/install-software) (Link to V2 library)

In this repository I have all the code I used to test each part of the project including:
* Driving the Motors
* Sweeping the Ultrasonic Sensor
* Ultrasonic Sensor Calibration

## Putting it all together

Assembly of the robot was about 20% of the project, 80% of the time was spent writing and debugging code ensuring it does what I want it to.  
