#include "../inc/Pinsetup.h"
#include <Arduino.h>
#include "../inc/Sensor.h"
#include "../inc/Motors.h"
#include "../inc/pwm.h"
#include "../inc/Encoders.h"
int leftEncoder;
int rightEncoder;

int leftEncoderChange;
int rightEncoderChange;

int encoderCount;
int encoderCountW;

int leftEncoderOld;
int rightEncoderOld;
double oldEncoderCount;

int encoderChange;
int rightEncoderCount;
int leftEncoderCount;

int distanceLeft;
int distanceLeftW;

volatile int encoderValueLeft = 0;
volatile int encoderValueRight = 0;

void attachInterrupts() {
  	attachInterrupt(EncoderL_A, countLeftEncoderA, CHANGE);
  	attachInterrupt(EncoderL_B, countLeftEncoderB, CHANGE);
  	attachInterrupt(EncoderR_A, countRightEncoderA, CHANGE);
	attachInterrupt(EncoderR_B, countRightEncoderB, CHANGE);

}
void countLeftEncoderA() {
	if (digitalRead(EncoderL_A)) {
		if (digitalRead(EncoderL_B)) { // If channel A leads B
			encoderValueLeft--;
		}
		else {
			encoderValueLeft++;
		}
	}
	else {
		if (digitalRead(EncoderL_B)) {
			encoderValueLeft++;
		}
		else {
			encoderValueLeft--;
		}
	}
}

void countLeftEncoderB() {
	if (digitalRead(EncoderL_B)) {
	   	if (digitalRead(EncoderL_A)) { 
	   		encoderValueLeft++;
	   	}
		else {
			encoderValueLeft--;
		}
	}
	else {
		if (digitalRead(EncoderL_A)) {
			encoderValueLeft--;
		}
		else {
			encoderValueLeft++;
		}
	}
}

void countRightEncoderA() {
	if (digitalRead(EncoderR_A)) {
		if (digitalRead(EncoderR_B)) { // If channel A leads B
			encoderValueRight--;
		}
		else {
			encoderValueRight++;
		}
	}
	else {

		if (digitalRead(EncoderR_B)) {
			encoderValueRight++;
		}
		else {
			encoderValueRight--;
		}
	}
}
void countRightEncoderB() {
	if (digitalRead(EncoderR_B)) {

		if (digitalRead(EncoderR_A)) {
			encoderValueRight++;
		}
		else {
			encoderValueRight--;
		}
	}
	else {

		if (digitalRead(EncoderR_A)) {
\
			encoderValueRight--;
		}
		else {

			encoderValueRight++;
		}
	}
}

void getEncoderStatus(void)
{
	leftEncoder = encoderValueLeft;
	rightEncoder = encoderValueRight;

	leftEncoderChange = leftEncoder - leftEncoderOld;
	rightEncoderChange = rightEncoder - rightEncoderOld;
	encoderChange = (leftEncoderChange + rightEncoderChange)/2;	 

	leftEncoderOld = leftEncoder;
	rightEncoderOld = rightEncoder;
					
	leftEncoderCount += leftEncoderChange;
	rightEncoderCount += rightEncoderChange;
	encoderCount =  (leftEncoderCount+rightEncoderCount)/2;	
	encoderCountW = rightEncoderCount - leftEncoderCount;
	
	distanceLeft -= encoderChange;// update distanceLeft	
	distanceLeftW -= rightEncoderChange - leftEncoderChange; // distanceLeftW: CW is positive
	Serial.println(distanceLeft);

}
void printEncoders() {
	Serial.print(encoderValueLeft);
	Serial.print(":");
	Serial.println(encoderValueRight);
}