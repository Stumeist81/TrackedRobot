#include <Servo.h>

// Define Motor Shield Constants 

const int rightPolarity=12;
const int leftPolarity=13;
const int rightBrake=9;
const int leftBrake=8;
const int rightSpeed=3;
const int leftSpeed=11;

// Define Ultrasonic Constants

const int trigPin = 7;
const int echoPin = 2; 


// Define Servo object

Servo myservo;

// Define program logic

int pos = 0;
int runState = 0;

// function prototypes

bool checkObstacleFront();
void setupMotors();
void startMotors();
void brakeMotors();
int checkDirection();
float checkDistance();
void turnLeft();
void turnRight();

void setup() {
  // setup motors
  pinMode(rightPolarity, OUTPUT);
  pinMode(leftPolarity, OUTPUT);
  pinMode(rightBrake, OUTPUT);
  pinMode(leftBrake, OUTPUT);
  
  //setup ultrasonioc sensor
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // setup Servo
  myservo.attach(6);  // attaches the servo on pin 6 to the servo object

  //Serial for debug
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  switch (runState) {
    case 0:
      setupMotors();
      startMotors();
      runState = 1;
      break;
    case 1:
      //Leave motors running and just check for obstacles ahead
           
      if (checkObstacleFront())
      {
        brakeMotors();
        runState = 2;
      }
      break;
    case 2:
    //TODO: Add servo code, check left and right see which has longest distance
    //TODO: Add code for IMU, gotta get them tigh 90 degree turns in.
    checkDirection();
    

    break;
  }


}

void setupMotors()
{
  digitalWrite(rightPolarity, HIGH);
  digitalWrite(leftPolarity, HIGH);
  analogWrite(rightSpeed, 150);
  analogWrite(leftSpeed, 255);
}

void startMotors()
{
  digitalWrite(rightBrake, LOW);
  digitalWrite(leftBrake, LOW);
}

void brakeMotors()
{
  digitalWrite(rightBrake, HIGH);
  digitalWrite(leftBrake, HIGH);
}


bool checkObstacleFront()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  // Convert this value to cm
  float distance = (duration * 0.0343) / 2;
  Serial.println(distance);
  if(distance <= 20)
  {
    Serial.println("true");
    return true;        
  }
  else
  {
    Serial.println("false");
    return false;
  }
}

int checkDirection()
{
  //Check to the left
  myservo.write(180);
  float leftDistance = checkDistance();


  //Check to the right
  myservo.write(10);
  float rightDistance = checkDistance();


  //Back to facing front
  myservo.write(90);

  if (rightDistance < leftDistance)
  {
    turnRight();
  }
  else
  {
    turnLeft();
  }
}

float checkDistance()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  // Convert this value to cm
  float distance = (duration * 0.0343) / 2;
  return distance;
}

void turnLeft()
{
  digitalWrite(rightPolarity, LOW);
  digitalWrite(leftPolarity, HIGH);
  analogWrite(rightSpeed, 150);
  analogWrite(leftSpeed, 255);
  
  startMotors();
}

void turnRight()
{
  digitalWrite(rightPolarity, HIGH);
  digitalWrite(leftPolarity, LOW);
  analogWrite(rightSpeed, 150);
  analogWrite(leftSpeed, 255);

  startMotors();
}




