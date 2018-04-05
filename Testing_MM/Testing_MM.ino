#include "inc/PinSetup.h"
#include "inc/Motors.h"
#include "inc/Sensor.h"
//#include "inc/pwm.h"
#include "inc/Encoders.h"

IntervalTimer sysTickTimer;

void setup() {
  pinMode(TeensyLED, OUTPUT);
  digitalWrite(TeensyLED, HIGH);
  
  //========SETUP========//
  MotorSetup();
  E_Setup();
  R_Setup();
  attachInterrupts();
  //====================//
  
  sysTickTimer.begin(sysTick, 5000);
  Serial.begin(9600);
  delay(2000);
}

void loop() {
  Serial.print("Left: ");
  Serial.println(encoderValueLeft);
  Serial.print("Right: ");
  Serial.println(encoderValueRight);
  delay(10);
//  Forward();
//
//  Braking();
//
//  Reverse();
//
//  Braking();


}
void sysTick() {
  //readSensors();
  //update endoder
  //update speed
  //PID
}



