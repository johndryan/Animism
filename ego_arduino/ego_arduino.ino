int MotorOneDirection = 13;
int MotorOneSpeed = 11;
int MotorTwoDirection = 12;
int MotorTwoSpeed = 3;
int sensorVal = 300;
int sensorPin = 5;
int maxDistance = 200;
int minDistance = 500;

void setup() {
  //Serial.begin(9600);
  pinMode (MotorOneDirection, OUTPUT);
  pinMode (MotorOneSpeed, OUTPUT);
  pinMode (MotorTwoDirection, OUTPUT);
  pinMode (MotorTwoSpeed, OUTPUT);
}

void loop(){
  forward();
  delay(2000);
  stop();
  delay(500);
  left();
  delay(2000);
  stop();
  delay(500);
  backward();
  delay(2000);
  stop();
  delay(500);
  right();
  delay(2000);
  stop();
  delay(500);
}

void forward() {
    digitalWrite(MotorOneDirection, HIGH);
    analogWrite(MotorOneSpeed, 255);
    digitalWrite(MotorTwoDirection, HIGH);
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

void backward() {
    digitalWrite(MotorOneDirection, HIGH);
    analogWrite(MotorOneSpeed, 255);
    digitalWrite(MotorTwoDirection, HIGH);
    analogWrite(MotorTwoSpeed, 255);
}

void stop() {
    digitalWrite(MotorOneDirection, LOW);
    analogWrite(MotorOneSpeed, 0);
    digitalWrite(MotorTwoDirection, LOW);
    analogWrite(MotorTwoSpeed, 0);
}
