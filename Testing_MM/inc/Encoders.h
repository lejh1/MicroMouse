#pragma once 

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;
// extern int leftEncoder;
// extern int rightEncoder;
// extern int leftEncoderChange;
// extern int rightEncoderChange;

void attachInterrupts();

void countLeftEncoderA();
void countLeftEncoderB();
void countRightEncoderA();
void countRightEncoderB();

// void getEncoderStatus();