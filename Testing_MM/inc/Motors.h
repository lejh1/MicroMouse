#pragma once 
extern int baseLeftSpeed;
extern int baseRightSpeed;

void MotorSetup();

void Forward();

void Reverse();

void Braking();

void setLeftPWM(int);
void setRightPWM(int);