#pragma once 
#include <Arduino.h>
//Thomas wrote all this code Justin did nothing

extern int moveSpeed;
extern int turnSpeed;
extern int returnSpeed;
extern int stopSpeed;
extern int maxSpeed;

extern int oneCellDistance;
extern int oneTurnDistance;

extern elapsedMillis wait_ms;
extern elapsedMicros wait_us;

double needToDecelerate(int, double, double);
void moveOneCell();
void turnRight();
void pressToStart();
