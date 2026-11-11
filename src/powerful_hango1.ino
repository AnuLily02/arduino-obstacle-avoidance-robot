#include <Servo.h>

// --- Pin Definitions ---
const int ENA = 3;  // Left motor PWM speed pin
const int IN1 = 4;  // Left motor direction 1
const int IN2 = 5;  // Left motor direction 2
const int IN3 = 6;  // Right motor direction 1
const int IN4 = 7;  // Right motor direction 2
const int ENB = 9;  // Right motor PWM speed pin

const int trigPin = 10;
const int echoPin = 11;

const int servoPin = 12;
Servo headServo;

const int safeDistance = 25; // Obstacle threshold in centimeters

void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  headServo.attach(servoPin);
  headServo.write(90); // Face straight ahead

  Serial.begin(9600);
}

void loop() {
  int distance = getDistance();

  // If an obstacle is detected within the safe distance threshold
  if (distance > 0 && distance < safeDistance) {
    stopCar();
    backwardCar();
    delay(300);
    stopCar();

    // Scan surroundings
    int leftDist = lookLeft();
    int rightDist = lookRight();

    // Turn toward the clearer path
    if (leftDist > rightDist) {
      turnLeft();
      delay(500);
    } else {
      turnRight();
      delay(500);
    }
  } else {
    forwardCar();
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  int distance = duration * 0.034 / 2;
  return distance;
}

int lookLeft() {
  headServo.write(170);
  delay(500);
  int dist = getDistance();
  headServo.write(90);
  delay(300);
  return dist;
}

int lookRight() {
  headServo.write(10);
  delay(500);
  int dist = getDistance();
  headServo.write(90);
  delay(300);
  return dist;
}

void forwardCar() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void backwardCar() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void turnLeft() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void turnRight() {
  analogWrite(ENA, 180);
  analogWrite(ENB, 180);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void stopCar() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}