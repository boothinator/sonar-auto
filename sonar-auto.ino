#include <Servo.h>

const int SERVO_PIN = 3;
const int MIN_ANGLE_PULSE = 700;
const int MAX_ANGLE_PULSE = 2400;
const int SONAR_ECHO_PIN = A4;  
const int SONAR_TRIGGER_PIN = A5; 

Servo servo;

// Measure distance in centimeters
int measureDistance() {
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIGGER_PIN, HIGH);
  delayMicroseconds(20);
  digitalWrite(SONAR_TRIGGER_PIN, LOW);

  unsigned long distancePulse = pulseIn(SONAR_ECHO_PIN, HIGH);
  
  int distanceCentimeters = (int)(distancePulse / 58);
  return distanceCentimeters;
}

void driveForward() {
  /* Left motors */
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(5, 128);
  
  /* Right motors */
  digitalWrite(9, LOW);
  digitalWrite(11, HIGH);
  analogWrite(6, 128);
}

void driveBackward() {
  /* Left motors */
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(5, 128);
  
  /* Right motors */
  digitalWrite(9, HIGH);
  digitalWrite(11, LOW);
  analogWrite(6, 128);
}

void coast() {
  /* Left motors */
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  
  /* Right motors */
  digitalWrite(9, LOW);
  digitalWrite(11, LOW);
}

void brake() {
  /* Left motors */
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  
  /* Right motors */
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
}

void turnLeft() {
  /* Left motors */
  digitalWrite(7, LOW);
  digitalWrite(8, HIGH);
  analogWrite(5, 128);
  
  /* Right motors */
  digitalWrite(9, LOW);
  digitalWrite(11, HIGH);
  analogWrite(6, 128);
}

void turnRight() {
  /* Left motors */
  digitalWrite(7, HIGH);
  digitalWrite(8, LOW);
  analogWrite(5, 128);
  
  /* Right motors */
  digitalWrite(9, HIGH);
  digitalWrite(11, LOW);
  analogWrite(6, 128);
}

void setup() {
  Serial.begin(9600);
  
  //servo.attach(SERVO_PIN, MIN_ANGLE_PULSE, MAX_ANGLE_PULSE);

  // Set up drive motor pins
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(6, OUTPUT);

  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);
}

void loop() {
  int distanceCentimeters = measureDistance();;

  // Drive forward until distance is less than 20cm
  while(distanceCentimeters >= 20) {

    driveForward();

    delay(50);
    distanceCentimeters = measureDistance();
  }
  brake();

  // Turn right about 90 degrees
  turnRight();
  delay(750);
  brake();

  

  // Stop forever
  while(true) {}
}
