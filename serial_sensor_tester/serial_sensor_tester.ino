/*
  Serial Sensor Tester
 */

#define rightLightSensor  2
#define leftLightSensor  1
#define proxSensor 3

int SensorLeft;
int SensorRight;
int SensorDifference;
int proxVal;
String message;

void setup() {
  Serial.begin(9600);
}

void loop() {
  proxVal = analogRead(proxSensor);
  delay(1);
  SensorLeft = 1023 - analogRead(leftLightSensor);        // This reads the value of the sensor, then saves it to the corresponding integer.
  delay(1);
  SensorRight = 1023 - analogRead(rightLightSensor);      // This reads the value of the sensor, then saves it to the corresponding integer.
  delay(1);
  SensorDifference = abs(SensorLeft - SensorRight);       // This calculates the difference between the two sensors and then saves it to an integer.
  message = "SensorLeft: ";
  message += SensorLeft;
  message += ",  SensorRight: ";
  message += SensorRight;
  message += ",  SensorDiff: ";
  message += SensorDifference;
  message += ",  proxVal: ";
  message += proxVal;
  Serial.println(message);
  delay(250);
}

