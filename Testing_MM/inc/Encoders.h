#pragma once

extern volatile int encoderValueLeft;
extern volatile int encoderValueRight;
extern int leftEncoder;
extern int rightEncoder;

extern int leftEncoderChange;
extern int rightEncoderChange;

extern int encoderCount;
extern int encoderCountW;

extern int leftEncoderOld;
extern int rightEncoderOld;
extern int rightEncoderCount;
extern int leftEncoderCount;

extern double oldEncoderCount; //IDK what this is

extern int encoderChange;
extern int distanceLeft;
extern int distanceLeftW;

void attachInterrupts();

void countLeftEncoderA();
void countLeftEncoderB();
void countRightEncoderA();
void countRightEncoderB();

void getEncoderStatus();
void printEncoders();