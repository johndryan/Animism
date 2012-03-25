int MotorPinDirection = 13;
int MotorPinSpeed = 11;
int sensorVal = 300;
int sensorPin = 5;
int maxDistance = 200;
int minDistance = 500;

void setup() {
  //Serial.begin(9600);
  pinMode (MotorPinDirection, OUTPUT);
  pinMode (MotorPinSpeed, OUTPUT);
}

void loop(){
  sensorVal = analogRead(sensorPin);
  delay(1);
  if (sensorVal < maxDistance) {
    // FORWARD
    digitalWrite(MotorPinDirection, LOW);
    analogWrite(MotorPinSpeed, 200);
  } else if (sensorVal > minDistance) {
    // REVERSE
    digitalWrite(MotorPinDirection, HIGH);
    analogWrite(MotorPinSpeed, 200);
  } else {
    //Serial.println("STOP");
    digitalWrite(MotorPinDirection, LOW);
    analogWrite(MotorPinSpeed, 0);
  }
  //Serial.println(sensorVal);
}

