#include <Servo.h>

Servo scanner;

const int out = 12;
const int in = 13;
int pos = 0;
long dur;
long dis;
long tocm;
bool returningToZero;

void setup() {
  Serial.begin(9600);
  pinMode(in, INPUT);
  pinMode(out, OUTPUT);
  scanner.attach(9);
  scanner.write(0);
}

bool objectDetected(long tocm)
{
  if (tocm < 20)
  {
    return true;
  } else {
    return false;
  }
}

void loop()
{
  digitalWrite(out, LOW);
  delayMicroseconds(2);
  digitalWrite(out, HIGH);
  delayMicroseconds(10);
  digitalWrite(out, LOW);
  dur = pulseIn(in, HIGH);
  tocm = microsecondsToCentimeters(dur);
  if (objectDetected(tocm))
  {
    Serial.print("Object detected. Object's distance: ");
    Serial.print(tocm);
    Serial.print(". Servo's angle: ");
    Serial.println(pos);
  } else {
    if (pos < 180 && returningToZero == false)
    {
      scanner.write(pos);
      pos += 3;
      Serial.print("Searching for object. Servo's angle: ");
      Serial.println(pos);
      if (pos == 180)
        returningToZero = true;
    } else if (returningToZero == true) {
      pos -= 3;
      Serial.print("Searching for object. Servo's angle: ");
      Serial.println(pos);
      scanner.write(pos);
      if (pos == 0)
        returningToZero = false;
    }
  }
  delay(200);
}

long microsecondsToCentimeters(long microseconds)
{
  return microseconds / 29.155 / 2;
}
