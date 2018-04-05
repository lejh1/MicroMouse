/*=======Motor Logic=======*/
#include <Arduino.h>
#include "../inc/PinSetup.h"
#include "../inc/Motors.h"

void MotorSetup(){
  pinMode(LMForward, OUTPUT);
  pinMode(LMReverse, OUTPUT);
  pinMode(RMForward, OUTPUT);
  pinMode(RMReverse, OUTPUT);
}

void Forward(){
  digitalWrite(LMForward, HIGH);
  digitalWrite(LMReverse, LOW);
  digitalWrite(RMForward, HIGH);
  digitalWrite(RMReverse, LOW);
  delay(3000); 
} 

void Reverse(){
  digitalWrite(LMForward, LOW);
  digitalWrite(LMReverse, HIGH);
  digitalWrite(RMForward, LOW);
  digitalWrite(RMReverse, HIGH);
  delay(3000); 
} 


void Braking(){
  digitalWrite(LMForward, LOW);
  digitalWrite(LMReverse, LOW);
  digitalWrite(RMForward, LOW);
  digitalWrite(RMReverse, LOW);
  delay(1000);
}

void setLeftPWM(int speed){
  if(speed >255){
    speed = 255;
  }
  if(speed < -255){
    speed = 255;
  }
  if(speed >= 0){
    analogWrite(LMForward, speed);
    analogWrite(LMReverse, 0);
  } else{
    analogWrite(LMReverse, -speed);
    analogWrite(LMForward, 0);
  }
}

void setRightPWM(int speed){
  if(speed >255){
    speed = 255;
  }
  if(speed < -255){
    speed = 255;
  }
  if(speed >= 0){
    analogWrite(RMForward, speed);
    analogWrite(RMReverse, 0);
  } else{
    analogWrite(RMReverse, -speed);
    analogWrite(RMForward, 0);
  }
}