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
int ledState = 0;
int ledOnOff = 0;
long previousMillis = 0;
int lightLevelTrigger = 350;

// SETTINGS
//--------------------------------------------------------------------------------- 

int speed = 20;             // sets the speed of the robot (both servos) between 0 and 90

int minDistance = 400;      // proximity is triggered above this
int lightDiff = 75;         // sensitivity in difference between light sensors

int interval = 300;       // interval at which LEDs should blink (milliseconds)

// SETUP
//---------------------------------------------------------------------------------

void setup()                  
{
  randomSeed(analogRead(1));         //sets the random number seed with something mildly random
  serbSetup();                       //sets the state of all neccesary pins and adds servos to your sketch
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
    // There's something in front
    allLightsOn();
    goBackward();
    delay(200);
    goRight();
    delay(300);
  } else {
    if (SensorLeft > SensorRight && SensorDifference > lightDiff) goRight();
    if (SensorLeft < SensorRight && SensorDifference > lightDiff) goLeft();
    if (SensorDifference < lightDiff) goForward();
  }
  
  doLights();
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
  // Choose a speed and light blink interval for this creature
  speed = 1 + random(18);
  interval = 950-(speed*50);
  String message = "Speed: ";
  message += speed;
  message += ",  interval: ";
  message += interval;
}

// MOVEMENT

void goForward(){
 leftServo.write(90 + speed);
 rightServo.write(90 - speed);
}

void goBackward(){
 leftServo.write(90 - speed);
 rightServo.write(90 + speed);
}
  
void goRight(){
 leftServo.write(90 + speed);
 rightServo.write(90 + speed);
}

void goLeft(){
 leftServo.write(90 - speed);
 rightServo.write(90 - speed);
}

void goStop(){
 leftServo.write(90);
 rightServo.write(90);
}

// LIGHTS

void doLights(){
  unsigned long currentMillis = millis();
  if (SensorLeft < lightLevelTrigger || SensorRight < lightLevelTrigger) {
    // On and Off
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;
      switch (ledOnOff) {
        case 0:
          digitalWrite(2, HIGH);
          digitalWrite(3, HIGH);
          digitalWrite(4, HIGH);
          digitalWrite(5, HIGH);
          break;
        case 1:
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          break;
      }
      ledOnOff++;
      if(ledOnOff > 1) ledOnOff = 0;
    }
  } else {
    // Do flash
    if(currentMillis - previousMillis > interval) {
      previousMillis = currentMillis;           // save the last time you blinked the LED
      switch (ledState) {
        case 0:
          digitalWrite(2, HIGH);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          break;
        case 1:
          digitalWrite(2, LOW);
          digitalWrite(3, HIGH);
          digitalWrite(4, LOW);
          digitalWrite(5, LOW);
          break;
        case 2:
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(5, LOW);
          break;
        case 3:
          digitalWrite(2, LOW);
          digitalWrite(3, LOW);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          break;
      }
      ledState++;
      if(ledState > 3) ledState = 0;
    }
  }
}

void allLightsOn(){
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
}
