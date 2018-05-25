#include "inc/PinSetup.h"
#include "inc/Motors.h"
#include "inc/Sensor.h"
#include "inc/pwm.h"
#include "inc/Encoders.h"
#include "inc/Movement.h"
//#include <time.h>

//use this at the start of main
IntervalTimer sysTickTimer;

int count = 1;

void setup() {
//  srand(time(NULL));
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
  if(count){
    pressToStart();
    count--;
    delay(500);

  }
    moveOneCell();
    turnRight();

//  moveOneCell();
//  delay(500);

//  turnRight();
//  targetSpeedX = 0;
//  printEncoders();
////  printPWM();
  delay(50000000);
//  encoderValueLeft = 0;
//  encoderValueRight = 0;
//  targetSpeedX = 10;

}
void sysTick() {
  readSensors();
  getEncoderStatus(); 
  updateCurrentSpeed();
  PID(); //PID  
//  testForward();

}



