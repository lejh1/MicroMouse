#pragma once 
extern int ambientLeft;
extern int ambientFrontLeft;
extern int ambientRight;
extern int ambientFrontRight;

// Receiver value raw
extern int rawLeft;
extern int rawFrontLeft;
extern int rawRight;
extern int rawFrontRight;

//True value of receiver readings
extern int TrueValueLeft;
extern int TrueValueFrontLeft;
extern int TrueValueRight;
extern int TrueValueFrontRight;

//Need to change 
extern int targetLeft;
extern int targetRight;
extern int targetFront;
extern int targetFront2;

extern int sensorError;

extern bool frontWall;
extern bool leftWall;
extern bool rightWall;

void E_Setup();

void R_Setup();

void readSensors();

void PrintVals();
void getSensorError();
void detectWalls();