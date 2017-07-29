#include <Servo.h>

int motorLeftPos = 6;
int motorLeftNeg = 7;
int motorRightPos = 8;
int motorRightNeg = 9;
int trigPin = 11;
int echoPin = 12;

Servo neckRotate;

long int duration;
int distance;
bool obsCheck;

void setup() {
  pinMode(motorLeftPos,OUTPUT);
  pinMode(motorLeftNeg,OUTPUT);
  pinMode(motorRightPos,OUTPUT);
  pinMode(motorRightNeg,OUTPUT);

  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);

  neckRotate.attach(3);
}

void stopMotor(){
  digitalWrite(motorLeftPos,LOW);
  digitalWrite(motorLeftNeg,LOW);
  digitalWrite(motorRightPos,LOW);
  digitalWrite(motorRightNeg,LOW);
}

bool checkLeft(){
  delay(500);
  neckRotate.write(180);
  obsCheck = checkObstacle();
  delay(500);
  neckRotate.write(90);
  return obsCheck;
}

bool checkRight(){
  delay(500);
  neckRotate.write(0);
  obsCheck = checkObstacle();
  delay(500);
  neckRotate.write(90);
  return obsCheck;
}

void turnLeft(){
  digitalWrite(motorLeftPos,LOW);
  digitalWrite(motorLeftNeg,HIGH);
  digitalWrite(motorRightPos,LOW);
  digitalWrite(motorRightNeg,HIGH);
  delay(500);
  stopMotor();
}

void turnRight(){
  digitalWrite(motorLeftPos,HIGH);
  digitalWrite(motorLeftNeg,LOW);
  digitalWrite(motorRightPos,HIGH);
  digitalWrite(motorRightNeg,LOW);
  delay(500);
  stopMotor();
}

void moveForward(){
  neckRotate.write(90);
  digitalWrite(motorLeftPos,LOW);
  digitalWrite(motorLeftNeg,HIGH);
  digitalWrite(motorRightPos,HIGH);
  digitalWrite(motorRightNeg,LOW);
}

void turnAround(){
  digitalWrite(motorLeftPos,HIGH);
  digitalWrite(motorLeftNeg,LOW);
  digitalWrite(motorRightPos,HIGH);
  digitalWrite(motorRightNeg,LOW);
  delay(900);
  stopMotor();
}

bool checkObstacle(){
  digitalWrite(trigPin,LOW);
  digitalWrite(echoPin,LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  
  duration = pulseIn(echoPin,HIGH);
  distance = duration*0.0343/2;
  
  if(distance<10){
    stopMotor();
    return false;
  }
  else
    return true;
}


void loop() {
  while(checkObstacle()){
    moveForward();
  }
  if(checkLeft())
    turnLeft();
  else if(checkRight())
    turnRight();
  else
    turnAround();
  stopMotor();
}
