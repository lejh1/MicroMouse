#include "../inc/Pinsetup.h"
#include <Arduino.h>
#include "../inc/Sensor.h"
// Receiver value of ambient light 
int ambientLeft;
int ambientFrontLeft;
int ambientRight;
int ambientFrontRight;

// Receiver value raw
int rawLeft;
int rawFrontLeft;
int rawRight;
int rawFrontRight;

//True value of receiver readings
int TrueValueLeft;
int TrueValueFrontLeft;
int TrueValueRight;
int TrueValueFrontRight;

//Booleans for walls 
bool frontWall;
bool leftWall;
bool rightWall;

//Threshold for wall values via Jerry 
int thresholdFront = 119;
// int thresholdSideLeft = 155;		// Threshold for Wall on side
int thresholdSideLeft = 250;		// Threshold for Wall on side

// int thresholdSideRight = 100;		// Threshold for Wall on side
int thresholdSideRight = 135;		// Thresho	ld for Wall on side

int thresholdUpperFront = 200; // Threshold for when mouse close to front wall detecting side walls

//Targer Values NEED TO CHANGE AND FIND MYSELF
int targetLeft = 0;// 325
int targetRight = 0;//256
int targetFront = 85;	// 60 - Threshold for Wall in front from Cell Boundary
int targetFront2 = 220;	// 30 - Threshold for Wall in front from Half Cell further than boundary

//
int sensorError;

//Instantiate Emitters
void E_Setup(){
    pinMode(Emitter_L, OUTPUT);
    pinMode(Emitter_FL, OUTPUT);
    pinMode(Emitter_R, OUTPUT);
    pinMode(Emitter_FR, OUTPUT);
}
//Instantiate Receivers
void R_Setup(){
    pinMode(Receiver_L, INPUT);
    pinMode(Receiver_FL, INPUT);
    pinMode(Receiver_R, INPUT);
    pinMode(Receiver_FR, INPUT);
}
//Reading Sensors
void readSensors(){
    // Duty Cycle of .008 
    // =======FORWARD LEFT====== //
    ambientLeft = analogRead(Receiver_L);
    digitalWrite(Emitter_L, HIGH);
    delayMicroseconds(40);
    rawLeft = analogRead(Receiver_L);
    TrueValueLeft = rawLeft - ambientLeft;
    digitalWrite(Emitter_L, LOW);

    // =======FORWARD RIGHT====== //
    delayMicroseconds(25);
    ambientRight = analogRead(Receiver_R);
    digitalWrite(Emitter_R, HIGH);
    delayMicroseconds(40);
    rawRight = analogRead(Receiver_R);
    TrueValueRight = rawRight - ambientRight;
    digitalWrite(Emitter_R, LOW);

    // =======LEFT====== //
    delayMicroseconds(25);
    ambientFrontLeft = analogRead(Receiver_FL);
    digitalWrite(Emitter_FL, HIGH);
    delayMicroseconds(40);
    rawFrontLeft = analogRead(Receiver_FL);
    TrueValueFrontLeft = rawFrontLeft - ambientFrontLeft;
    digitalWrite(Emitter_FL, LOW);

    // =======RIGHT====== //
    delayMicroseconds(25);
    ambientFrontRight = analogRead(Receiver_FR);
    digitalWrite(Emitter_FR, HIGH);
    delayMicroseconds(40);
    rawFrontRight = analogRead(Receiver_FR);
    TrueValueFrontRight = rawFrontRight - ambientFrontRight;
    digitalWrite(Emitter_FR, LOW);
    PrintVals();

	detectWalls();
	getSensorError();

}


//Print Receiver Readings
void PrintVals(){
    Serial.print("Left Value: ");
    Serial.println(TrueValueLeft);
    Serial.print("Right Value: ");
    Serial.println(TrueValueRight);
    Serial.print("Front Left Value: ");
    Serial.println(TrueValueFrontLeft);
    Serial.print("Front Right Value: ");
    Serial.println(TrueValueFrontRight);
	Serial.print("Sensor Error: ");
    Serial.println(sensorError);
	Serial.print("Left Wall: ");
    Serial.println(leftWall);
	Serial.print("Right Wall: ");
    Serial.println(rightWall);
	Serial.print("Front Wall: ");
    Serial.println(frontWall);
}

void detectWalls() {
	if (TrueValueRight > thresholdFront || TrueValueLeft > thresholdFront) {
		frontWall = true;
	}
	else {
		frontWall = false;
	}

	if (TrueValueFrontLeft > thresholdSideLeft) {
		leftWall = true;
	}
	else {
		leftWall = false;
	}
	
	if (TrueValueFrontRight > thresholdSideRight) {
		rightWall = true;
	}
	else {
		rightWall = false;
	}
}

void getSensorError() {

	// if (TrueValueRight < thresholdUpperFront || TrueValueLeft < thresholdUpperFront) {
	// 	if (leftWall == true && rightWall == true) {
	// 		sensorError = TrueValueFrontRight - TrueValueFrontLeft;
	// 	}
	// 	else if (leftWall == true && rightWall == false) {
	// 		sensorError = targetLeft - TrueValueFrontLeft;
	// 	}
	// 	else if (rightWall == true && leftWall == false) {
	// 		sensorError = TrueValueFrontRight - targetRight;
	// 	}
	// 	else if (rightWall == false && leftWall == false) {
	// 		sensorError = 0;
	// 	}
	// }
	// else {
	// 	sensorError = TrueValueLeft - TrueValueRight;
	// 	sensorError *= 3;
	// }

	if (TrueValueRight < thresholdUpperFront || TrueValueLeft < thresholdUpperFront) {
		if (leftWall == true && rightWall == true) {
			sensorError = TrueValueFrontRight - TrueValueFrontLeft - (targetRight - targetLeft);
		}
		else if (leftWall == true && rightWall == false) {
			sensorError = targetLeft - TrueValueFrontLeft;
		}
		else if (rightWall == true && leftWall == false) {
			sensorError = TrueValueFrontRight - targetRight;
		}
		else if (rightWall == false && leftWall == false) {
			sensorError = 0;
		}
	}
	else {
		sensorError = 0;
	}

	// if (frontWall) {
	// 	sensorError = (TrueValueLeft - TrueValueRight) * 3;
	// }

	if (TrueValueRight > thresholdUpperFront || TrueValueLeft > thresholdUpperFront) {
		sensorError = (TrueValueLeft - TrueValueRight);
	}
}