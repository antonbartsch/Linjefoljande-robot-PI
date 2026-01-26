#include <Arduino.h>

const int leftSensorIn;
const int rightSensorIn;
const int leftMotorOut;
const int rightMotorOut;


// put function declarations here:
int myFunction(int, int);

int readSensors(int, int)

void setup() {
  // put your setup code here, to run once:
  int result = myFunction(2, 3);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
}

// put function definitions here:
int myFunction(int x, int y) {
  return x + y;
}

/** Läser två sensorer.
  * Returnerar: 1=höger, -1=vänster, 0=rakt fram 
  */
int readSensors(int leftSensor, int rightSensor){
  int leftSensorValue = digitalRead(leftSensor);
  int rightSensorValue = digitalRead(rightSensor);
  if((leftSensorValue == HIGH) && (rightSensorValue == HIGH)){
    Serial.println("Fel! båda sensorerna ger positiv");
    return 0;
  }
  else if(rightSensorValue == 1){
    return 1;
  }
  else if(leftSensorValue == 1){
    return -1;
  }
  else{
    return 0;
  }
}