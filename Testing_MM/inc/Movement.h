#pragma once 
#include <Arduino.h>

extern int moveSpeed;
extern int turnSpeed;
extern int returnSpeed;
extern int stopSpeed;
extern int maxSpeed;

extern int oneCellDistance;
extern int oneTurnDistance;
extern int leftTurnDistance;
extern elapsedMillis wait_ms;
extern elapsedMicros wait_us;

double needToDecelerate(int, double, double);
void moveOneCell();
void turnRight();
void turnLeft();
void pressToStart();
