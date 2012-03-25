import processing.serial.*;
import cc.arduino.*;
import SimpleOpenNI.*;

Arduino arduino;
SimpleOpenNI  context;
boolean       autoCalib=true;

boolean botDisabled = false;
int MotorOneDirection = 13;
int MotorOneSpeed = 11;
int MotorTwoDirection = 12;
int MotorTwoSpeed = 3;

int centerZone = 25;

void setup() {
  context = new SimpleOpenNI(this);
  // enable depthMap generation 
  if(context.enableDepth() == false)
  {
     println("Can't open the depthMap, maybe the camera is not connected!"); 
     exit();
     return;
  }
  // enable skeleton generation for all joints
  context.enableUser(SimpleOpenNI.SKEL_PROFILE_ALL);
  
  size(context.depthWidth(), context.depthHeight()); 
  
  arduino = new Arduino(this, Arduino.list()[0], 57600);
  arduino.pinMode(MotorOneDirection, Arduino.OUTPUT);
  arduino.pinMode(MotorOneSpeed, Arduino.OUTPUT);
  arduino.pinMode(MotorTwoDirection, Arduino.OUTPUT);
  arduino.pinMode(MotorTwoSpeed, Arduino.OUTPUT);
}

void draw() {
  // update the cam
  context.update();
  
  // draw depthImageMap
  image(context.depthImage(),0,0);
  
  // draw the skeleton if it's available
  if(context.isTrackingSkeleton(1)) drawSkeleton(1);
  
  if(!botDisabled) stopMe();
}

void keyPressed() {
    botDisabled = true;
}

// draw the skeleton with the selected joints
void drawSkeleton(int userId)
{
  // to get the 3d joint data
  
  PVector jointPos = new PVector();
  context.getJointPositionSkeleton(userId,SimpleOpenNI.SKEL_NECK,jointPos);
  if (jointPos.x < centerZone && jointPos.x > -centerZone && botDisabled == false) {
    println("CENTER: " + jointPos);
    stopMe();
  } else if (jointPos.x > centerZone) {
    println("RIGHT: " + jointPos);
    goRight();
  } else if (jointPos.x < -centerZone) {
    println("LEFT: " + jointPos);
    goLeft();
  }
  context.drawLimb(userId, SimpleOpenNI.SKEL_HEAD, SimpleOpenNI.SKEL_NECK);

  context.drawLimb(userId, SimpleOpenNI.SKEL_NECK, SimpleOpenNI.SKEL_LEFT_SHOULDER);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_SHOULDER, SimpleOpenNI.SKEL_LEFT_ELBOW);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_ELBOW, SimpleOpenNI.SKEL_LEFT_HAND);

  context.drawLimb(userId, SimpleOpenNI.SKEL_NECK, SimpleOpenNI.SKEL_RIGHT_SHOULDER);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_SHOULDER, SimpleOpenNI.SKEL_RIGHT_ELBOW);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_ELBOW, SimpleOpenNI.SKEL_RIGHT_HAND);

  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_SHOULDER, SimpleOpenNI.SKEL_TORSO);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_SHOULDER, SimpleOpenNI.SKEL_TORSO);

  context.drawLimb(userId, SimpleOpenNI.SKEL_TORSO, SimpleOpenNI.SKEL_LEFT_HIP);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_HIP, SimpleOpenNI.SKEL_LEFT_KNEE);
  context.drawLimb(userId, SimpleOpenNI.SKEL_LEFT_KNEE, SimpleOpenNI.SKEL_LEFT_FOOT);

  context.drawLimb(userId, SimpleOpenNI.SKEL_TORSO, SimpleOpenNI.SKEL_RIGHT_HIP);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_HIP, SimpleOpenNI.SKEL_RIGHT_KNEE);
  context.drawLimb(userId, SimpleOpenNI.SKEL_RIGHT_KNEE, SimpleOpenNI.SKEL_RIGHT_FOOT);
}

// -----------------------------------------------------------------
// Moving the bot

void goForward() {
    arduino.digitalWrite(MotorOneDirection, arduino.HIGH);
    arduino.analogWrite(MotorOneSpeed, 255);
    arduino.digitalWrite(MotorTwoDirection, arduino.HIGH);
    arduino.analogWrite(MotorTwoSpeed, 255);
}

void goLeft() {
    arduino.digitalWrite(MotorOneDirection, arduino.LOW);
    arduino.analogWrite(MotorOneSpeed, 255);
    arduino.digitalWrite(MotorTwoDirection, arduino.HIGH);
    arduino.analogWrite(MotorTwoSpeed, 255);
}

void goRight() {
    arduino.digitalWrite(MotorOneDirection, arduino.HIGH);
    arduino.analogWrite(MotorOneSpeed, 255);
    arduino.digitalWrite(MotorTwoDirection, arduino.LOW);
    arduino.analogWrite(MotorTwoSpeed, 255);
}

void goBackward() {
    arduino.digitalWrite(MotorOneDirection, arduino.HIGH);
    arduino.analogWrite(MotorOneSpeed, 255);
    arduino.digitalWrite(MotorTwoDirection, arduino.HIGH);
    arduino.analogWrite(MotorTwoSpeed, 255);
}

void stopMe() {
    arduino.digitalWrite(MotorOneDirection, arduino.LOW);
    arduino.analogWrite(MotorOneSpeed, 0);
    arduino.digitalWrite(MotorTwoDirection, arduino.LOW);
    arduino.analogWrite(MotorTwoSpeed, 0);
}

// -----------------------------------------------------------------
// SimpleOpenNI events

void onNewUser(int userId)
{
  println("onNewUser - userId: " + userId);
  println("  start pose detection");
  
  if(autoCalib)
    context.requestCalibrationSkeleton(userId,true);
  else    
    context.startPoseDetection("Psi",userId);
}

void onLostUser(int userId)
{
  println("onLostUser - userId: " + userId);
}

void onStartCalibration(int userId)
{
  println("onStartCalibration - userId: " + userId);
}

void onEndCalibration(int userId, boolean successfull)
{
  println("onEndCalibration - userId: " + userId + ", successfull: " + successfull);
  
  if (successfull) 
  { 
    println("  User calibrated !!!");
    context.startTrackingSkeleton(userId); 
  } 
  else 
  { 
    println("  Failed to calibrate user !!!");
    println("  Start pose detection");
    context.startPoseDetection("Psi",userId);
  }
}

void onStartPose(String pose,int userId)
{
  println("onStartPose - userId: " + userId + ", pose: " + pose);
  println(" stop pose detection");
  
  context.stopPoseDetection(userId); 
  context.requestCalibrationSkeleton(userId, true);
 
}

void onEndPose(String pose,int userId)
{
  println("onEndPose - userId: " + userId + ", pose: " + pose);
}
