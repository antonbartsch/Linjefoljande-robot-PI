#include <Arduino.h>
#include <LowPower.h>

const int leftSensorIn =2;
const int rightSensorIn =3;
const int leftMotorOut = 10;
const int rightMotorOut =11;
const float integralConstant =0;
const float errorConstant = 1;
const int integLimit = 10;

int intgError = 0;


// put function declarations here:
int myFunction(int, int);
int readSensors(int, int);
void integrateError(int);
void driveMotors(float);
float pI(int, int);
float clamp(float, float, float);
void printToSerial(int,float);
void deepSleep(int);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(leftSensorIn, INPUT);
  pinMode(rightSensorIn, INPUT);
  pinMode(leftMotorOut, OUTPUT);
  pinMode(rightMotorOut, OUTPUT);
  deepSleep(15);
}

void loop() {
  // put your main code here, to run repeatedly:

int error = readSensors(leftSensorIn, rightSensorIn);
integrateError(error);
float motorInput = pI(error, intgError);
motorInput = clamp(motorInput, -1.0, 1.0);
driveMotors(motorInput);
printToSerial(error, motorInput);
}

// put function definitions here:

/** Läser två sensorer.
  * Returnerar: 1=höger, -1=vänster, 0=rakt fram 
  */
int readSensors(int leftSensor, int rightSensor){
  int leftSensorValue = digitalRead(leftSensor);
  int rightSensorValue = digitalRead(rightSensor);
  if((leftSensorValue == 1) && (rightSensorValue == 1)){
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

/** Summerar felen och skapar en 'integral'
  * sparar värdet i int intgError
  */
void integrateError(int error){
  intgError += error;
  if (intgError>integLimit){intgError = integLimit;}
  if (intgError<-integLimit){intgError = -integLimit;}
}

/** Kör motorerna utifrån felvärde mellan -1 och 1
*/
void driveMotors(float error){
  if(error<0){
    int motorValue = 255+(error*255);
    analogWrite(leftMotorOut, motorValue);
    analogWrite(rightMotorOut, 255);
  }
  else if(error>0){
    int motorValue = 255-(error*255);
    analogWrite(leftMotorOut, 255);
    analogWrite(rightMotorOut, motorValue);
  }
  else{
    analogWrite(leftMotorOut, 255);
    analogWrite(rightMotorOut, 255);
  }
}

/**Adderar en multiplikation av felet med en multiplikation av integralen
 * Returnerar: inputvärde för motordrivar funktionen
  */
 float pI(int error, int integratedError){
  return (errorConstant*error) - (integralConstant*integratedError);
 }

/*Avrundar värden innom angivna gränser
*/
float clamp(float value, float lowerLimit, float upperLimit){
if(value <= lowerLimit){
  return lowerLimit;
}
else if(value>upperLimit){
  return upperLimit;
}
else return value;
}

void printToSerial(int error, float motorValue){
  Serial.println("error: ");
  Serial.println(error);
  Serial.println("inegral:");
  Serial.println(intgError);
  Serial.println("motorValue:");
  Serial.println(motorValue);

}

void deepSleep(int cykles){ //En cykle 8s
  for (int i = 0; i <cykles; i++){
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
