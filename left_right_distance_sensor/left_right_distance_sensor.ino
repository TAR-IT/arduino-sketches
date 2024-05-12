/*
  SR04 Ultrasonic Left And Right Distance Sensor

  This sketch reads a SR04 ultrasonic rangefinder and returns the distance
  to the closest object in range. To do this, it sends a pulse to the sensor to
  initiate a reading, then listens for a pulse to return. The length of the
  returning pulse is proportional to the distance of the object from the sensor.
  
*/

const int triggerPinR = 2;
const int echoPinR = 3;
const int triggerPinL = 4;
const int echoPinL = 5;
const int firstLedPinR = 6;
const int secondLedPinR = 7;
const int thirdLedPinR = 8;
const int fourthLedPinR = 9;
const int firstLedPinL = 10;
const int secondLedPinL = 11;
const int thirdLedPinL = 12;
const int fourthLedPinL = 13;

void setup() {
  // initialize serial communication:
  Serial.begin(9600);
  pinMode(triggerPinR, OUTPUT);
  pinMode(echoPinR, INPUT);
  pinMode(triggerPinL, OUTPUT);
  pinMode(echoPinL, INPUT);
  pinMode(firstLedPinR, OUTPUT);
  pinMode(secondLedPinR, OUTPUT);
  pinMode(thirdLedPinR, OUTPUT);
  pinMode(fourthLedPinR, OUTPUT);
  pinMode(firstLedPinL, OUTPUT);
  pinMode(secondLedPinL, OUTPUT);
  pinMode(thirdLedPinL, OUTPUT);
  pinMode(fourthLedPinL, OUTPUT);
}

void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  long durationR, cmR, durationL, cmL;
  
  digitalWrite(triggerPinR, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPinR, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPinR, LOW);
  durationR = pulseIn(echoPinR, HIGH);
  
  // convert the time into a distance
  cmR = microsecondsToCentimeters(durationR);
  
  if (cmR < 10){
    digitalWrite(firstLedPinR, HIGH);
    digitalWrite(secondLedPinR, HIGH);
    digitalWrite(thirdLedPinR, HIGH);
    digitalWrite(fourthLedPinR, HIGH);
  }
  else if (cmR < 30) {
    digitalWrite(firstLedPinR, HIGH);
    digitalWrite(secondLedPinR, HIGH);
    digitalWrite(thirdLedPinR, HIGH);
  }
  else if (cmR < 50) {
    digitalWrite(firstLedPinR, HIGH);
    digitalWrite(secondLedPinR, HIGH);
  }
  else if (cmR < 80) {
    digitalWrite(firstLedPinR, HIGH);
  }
  else {
    digitalWrite(firstLedPinR, LOW);
    digitalWrite(secondLedPinR, LOW);
    digitalWrite(thirdLedPinR, LOW);
    digitalWrite(fourthLedPinR, LOW);
  }
  
  digitalWrite(triggerPinL, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPinL, HIGH);
  delayMicroseconds(5);
  digitalWrite(triggerPinL, LOW);
  durationL = pulseIn(echoPinL, HIGH);


  cmL = microsecondsToCentimeters(durationL);

  if (cmL < 10){
    digitalWrite(firstLedPinL, HIGH);
    digitalWrite(secondLedPinL, HIGH);
    digitalWrite(thirdLedPinL, HIGH);
    digitalWrite(fourthLedPinL, HIGH);
  }
  else if (cmL < 30) {
    digitalWrite(firstLedPinL, HIGH);
    digitalWrite(secondLedPinL, HIGH);
    digitalWrite(thirdLedPinL, HIGH);
  }
  else if (cmL < 50) {
    digitalWrite(firstLedPinL, HIGH);
    digitalWrite(secondLedPinL, HIGH);
  }
  else if (cmL < 80) {
    digitalWrite(firstLedPinL, HIGH);
  }
  else {
    digitalWrite(firstLedPinL, LOW);
    digitalWrite(secondLedPinL, LOW);
    digitalWrite(thirdLedPinL, LOW);
    digitalWrite(fourthLedPinL, LOW);
  }

  Serial.print(cmR);
  Serial.print("cm right");
  Serial.println();
  Serial.print(cmL);
  Serial.print("cm left");
  Serial.println();


  delay(100);
}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
