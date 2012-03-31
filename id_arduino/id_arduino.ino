/*
 *  Based on SERB code from here: http://www.oomlout.com/serb 
 */ 

// LIBRARIES
//---------------------------------------------------------------------------------

#include <Servo.h>

Servo leftServo;
Servo rightServo;

// DEFINE PINS
//--------------------------------------------------------------------------------- 

#define LEFTSERVOPIN  10
#define RIGHTSERVOPIN  9
#define rightLightSensor  2
#define leftLightSensor  1
#define proxSensor 3

// MISC VARS
//--------------------------------------------------------------------------------- 

int SensorLeft;
int SensorRight;
int SensorDifference;
int proxVal = 500;

// SETTINGS
//--------------------------------------------------------------------------------- 

int speed = 50;             // sets the speed of the robot (both servos) between 0 and 90
int servoLeftOff = 90;      // If left servo can't be adjusted manually, set the stop value here
int servoRightOff = 90;     // If right servo can't be adjusted manually, set the stop value here

int minDistance = 400;      // proximity is triggered above this
int lightDiff = 125;        // sensitivity in difference between light sensors


// SETUP
//---------------------------------------------------------------------------------

void setup()                  
{
  serbSetup();                       //sets the state of all neccesary pins and adds servos to your sketch
  randomSeed(analogRead(0));         //sets the random number seed with something mildly random
  delay(1000);
}

// LOOP
//--------------------------------------------------------------------------------- 

void loop()                     
{
  proxVal = analogRead(proxSensor);
  delay(1);
  SensorLeft = 1023 - analogRead(leftLightSensor);        // This reads the value of the sensor, then saves it to the corresponding integer.
  delay(1);
  SensorRight = 1023 - analogRead(rightLightSensor);      // This reads the value of the sensor, then saves it to the corresponding integer.
  delay(1);
  SensorDifference = abs(SensorLeft - SensorRight);       // This calculates the difference between the two sensors and then saves it to an integer.
  
  if (proxVal > minDistance) {
    goRight();
  } else {
    if (SensorLeft > SensorRight && SensorDifference > lightDiff) goRight();
    if (SensorLeft < SensorRight && SensorDifference > lightDiff) goLeft();
    if (SensorDifference < lightDiff) goForward();
  }
}

// FUNCTIONS
//--------------------------------------------------------------------------------- 

void serbSetup(){
  pinMode(LEFTSERVOPIN, OUTPUT);     //sets the left servo signal pin to output
  pinMode(RIGHTSERVOPIN, OUTPUT);    //sets the right servo signal pin to output
  leftServo.attach(LEFTSERVOPIN);    //attaches left servo
  rightServo.attach(RIGHTSERVOPIN);  //attaches right servo
  pinMode(rightLightSensor, INPUT);  //sets the right light sensor signal pin to input
  pinMode(leftLightSensor, INPUT);   //sets the left light sensor signal pin to input
  goStop();                          //stops servos just in case still running
}

void goForward(){
 leftServo.write(90 + speed);
 rightServo.write(90 + speed);
}

void goBackward(){
 leftServo.write(90 - speed);
 rightServo.write(90 - speed);
}

void goRight(){
 leftServo.write(90 + speed);
 rightServo.write(90 - speed);
}

void goLeft(){
 leftServo.write(90 - speed);
 rightServo.write(90 + speed);
}

void goStop(){
 leftServo.write(90);
 rightServo.write(90);
}
