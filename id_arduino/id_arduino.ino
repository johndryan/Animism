/*
 *  Based on Arduino Controlled Servo Robot (SERB) code: http://www.oomlout.com/serb 
 */ 
 
//---------------------------------------------------------------------------------
// START OF ARDUINO CONTROLLED SERVO ROBOT (SERB) PREAMBLE
#include <Servo.h>

#define LEFTSERVOPIN  10
#define RIGHTSERVOPIN  9
#define rightLightSensor  2
#define leftLightSensor  1
#define proxSensor 3

Servo leftServo; 
Servo rightServo; 

int speed = 50; //sets the speed of the robot (both servos) a percentage between 0 and 100
int servoLeftOff = 90;
int servoRightOff = 90;

int SensorLeft;
int SensorRight;
int SensorDifference;

int minDistance = 400;
int lightDiff = 125;
int proxVal = 500;

// END OF ARDUINO CONTROLLED SERVO ROBOT (SERB) PREAMBLE
//---------------------------------------------------------------------------------


/*
 * sets pins to appropriate states and attaches servos. Then pauses
 * for 1 second before the program starts
*/ 
void setup()                  
{
  serbSetup();                       //sets the state of all neccesary pins and adds servos to your sketch
  randomSeed(analogRead(0));         //sets the random number seed with something mildly random
  delay(1000);
}

/*
 * turns the robot either left or right (randomly) for a period between 
 * 0.1 and 1 second. Before going forward for a random time period 
 * between 1 and 4 seconds. Before pausing for two seconds then starting
 * again.
*/
void loop()                     
{
  proxVal = analogRead(proxSensor);
  delay(1);
  SensorLeft = 1023 - analogRead(leftLightSensor); // This reads the value of the sensor, then saves it to the corresponding integer.
  delay(1);
  SensorRight = 1023 - analogRead(rightLightSensor); // This reads the value of the sensor, then saves it to the corresponding integer.
  delay(1);
  SensorDifference = abs(SensorLeft - SensorRight); // This calculates the difference between the two sensors and then saves it to an integer.
  
  if (proxVal > minDistance) {
    goStop();
  } else {
    if (SensorLeft > SensorRight && SensorDifference > lightDiff) goRight();
    if (SensorLeft < SensorRight && SensorDifference > lightDiff) goLeft();
    if (SensorDifference < lightDiff) goForward();
  }
  
//   turnRandom(100,1000);            //Turns randomly left or right for a random time period between .1 second and one second
//   goForwardRandom(1000,2000);      //Goes forward for a random time period between 1 and 2 seconds
//   goStop();                        //Stops the robot
//   delay(2000);                     //pauses for 2 seconds (whilst stopped)
}

/*
 * turns the robot randomly left or right for a random time period between
 * minTime (milliseconds) and maxTime (milliseconds)
 */
void turnRandom(int minTime, int maxTime){
  int choice = random(2);                     //Random number to decide between left (1) and right (0)
  int turnTime = random(minTime,maxTime);     //Random number for the pause time
  if(choice == 1){ goLeft();}                 //If random number = 1 then turn left
  else {goRight();}                           //If random number = 0 then turn right
  delay(turnTime);                            //delay for random time                         
}

/*
 * goes forward for a random time period between minTime (milliseconds)
 * and maxTime (milliseconds)
 */
void goForwardRandom(int minTime, int maxTime){
  int forwardTime = random(minTime,maxTime);      //determine a random time to go forward
  goForward();                                    //sets the SERB forward
  delay(forwardTime);                             //delays for random time period
}

//------------------------------------------------------------------------------------------------------------
//START OF ARDUINO CONTROLLED SERVO ROBOT (SERB) ROUTINES

/*
 * sets up your arduino to address your SERB using the included routines
*/
void serbSetup(){
  setSpeed(speed);
  pinMode(LEFTSERVOPIN, OUTPUT);     //sets the left servo signal pin to output
  pinMode(RIGHTSERVOPIN, OUTPUT);    //sets the right servo signal pin to output
  leftServo.attach(LEFTSERVOPIN);    //attaches left servo
  rightServo.attach(RIGHTSERVOPIN);  //attaches right servo
  pinMode(rightLightSensor, INPUT);
  pinMode(leftLightSensor, INPUT);
  goStop();
}


/*
 * sets the speed of the robot between 0-(stopped) and 100-(full speed)
 * NOTE: speed will not change the current speed you must change speed 
 * then call one of the go methods before changes occur.
*/ 
void setSpeed(int newSpeed){
  if(newSpeed >= 100) {newSpeed = 100;}     //if speed is greater than 100 make it 100
  if(newSpeed <= 0) {newSpeed = 0;}         //if speed is less than 0 make it 0 
  speed = newSpeed * 0.9;                   //scales the speed to be between 0 and 90
}

void goRight(){
 leftServo.write(90 + speed);
 rightServo.write(90 - speed);
}

void goLeft(){
 leftServo.write(90 - speed);
 rightServo.write(90 + speed);
}

void goForward(){
 leftServo.write(90 + speed);
 rightServo.write(90 + speed);
}

void goBackward(){
 leftServo.write(90 - speed);
 rightServo.write(90 - speed);
}

void goStop(){
 leftServo.write(90);
 rightServo.write(90);
} 
//END OF ARDUINO CONTROLLED SERVO ROBOT (SERB) ROUTINES
//------------------------------------------------------------------------------------------------------------
