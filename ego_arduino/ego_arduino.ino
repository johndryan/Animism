int MotorOneDirection = 13;
int MotorOneSpeed = 11;
int MotorTwoDirection = 12;
int MotorTwoSpeed = 3;
int sensorVal = 300;
int sensorPin = 5;
int maxDistance = 200;
int minDistance = 500;

char action = 's';

void setup() {
  Serial.begin(9600);
  
  pinMode (MotorOneDirection, OUTPUT);
  pinMode (MotorOneSpeed, OUTPUT);
  pinMode (MotorTwoDirection, OUTPUT);
  pinMode (MotorTwoSpeed, OUTPUT);
}

void loop(){
  if (action == 'f') {
    forward();
  }
  if (action == 'b') {
    backward();
  }
  if (action == 'l') {
    left();
  }
  if (action == 'r') { 
    right();
  }
  if (action == 's') {
    stopMe();
  }
}

void serialEvent() {
  while (Serial.available()) {
    action = (char)Serial.read();
  }
}

void forward() {
    digitalWrite(MotorOneDirection, HIGH);
    analogWrite(MotorOneSpeed, 255);
    digitalWrite(MotorTwoDirection, HIGH);
    analogWrite(MotorTwoSpeed, 255);
}

void backward() {
    digitalWrite(MotorOneDirection, LOW);
    analogWrite(MotorOneSpeed, 255);
    digitalWrite(MotorTwoDirection, LOW);
    analogWrite(MotorTwoSpeed, 255);
}

void left() {
    digitalWrite(MotorOneDirection, LOW);
    analogWrite(MotorOneSpeed, 255);
    digitalWrite(MotorTwoDirection, HIGH);
    analogWrite(MotorTwoSpeed, 255);
}

void right() {
    digitalWrite(MotorOneDirection, HIGH);
    analogWrite(MotorOneSpeed, 255);
    digitalWrite(MotorTwoDirection, LOW);
    analogWrite(MotorTwoSpeed, 255);
}

void stopMe() {
    digitalWrite(MotorOneDirection, LOW);
    analogWrite(MotorOneSpeed, 0);
    digitalWrite(MotorTwoDirection, LOW);
    analogWrite(MotorTwoSpeed, 0);
}
