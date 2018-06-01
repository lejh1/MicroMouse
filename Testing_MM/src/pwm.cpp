#include "../inc/Pinsetup.h"
#include <Arduino.h>
#include "../inc/Sensor.h"
#include "../inc/Motors.h"
#include "../inc/pwm.h"
#include "../inc/Encoders.h"
// double curSpeedX = 0;
// double curSpeedW = 0;
// double targetSpeedX = 15;
// double targetSpeedW = 0;
// double encoderFeedbackX = 0;
// double encoderFeedbackW = 0;
// double pidInputX = 0;
// double pidInputW = 0;
// double posErrorX = 0;
// double posErrorW = 0;
// double oldPosErrorX = 0;
// double oldPosErrorW = 0;
// double sensor_scale = 6;

// int posPwmX = 0;
// int posPwmW = 0;
// double kpX = 2, kdX = 4;
// double kpW = 1, kdW = 12;//used in straight
// double kpW1 = 1;//used for T1 and T3 in curve turn
// double kdW1 = 26;
// double kpW2 = 1;//used for T2 in curve turn
// double kdW2 = 36;
// double accX = 600;//6m/s/s  
// double decX = 600; 
// double accW = 1; //cm/s^2
// double decW = 1;
// bool useSensors = false;
// bool onlyUseEncoderFeedback = true;



double accX = 0.3;  // Probably no need to change.
double accW = 0.4;
double decX = 0.43; // Do not change. Perfect value
double decW = 0.4;

double sensorFeedback = 0;
double turnFeedback = 0;
double sensor_scale = 6;
double turn_scale = 1;
bool useSensors = true;

double curSpeedX = 0;
double curSpeedW = 0;
double targetSpeedX = 0;
double targetSpeedW = 0;

double encoderFeedbackX = 0;
double encoderFeedbackW = 0;

int outMin = -255;	// Anti-windup
int outMax = 255;

double ITermX;
double ITermW;

double lastSpeedX = 0;
double lastSpeedW = 0;

double kpX = 3;//.5; // Slightly confident this number is good
double kpW = 10;
double kiX = .1;//.2; // Very confident in this number
// double kiW = .1;
double kiW = 0;

double kdX = .15; // Very confident in this number
double kdW = .15;
// double kdW = ;


// void PID() // encoder PD controller
// {	
// 	int rotationalFeedback;
// 	int sensorFeedback = 0;
	
//     /* simple PD loop to generate base speed for both motors */	
// 	encoderFeedbackX = rightEncoderChange + leftEncoderChange; //forward
// 	encoderFeedbackW = rightEncoderChange - leftEncoderChange;	
	
//     if(useSensors){
// 	    // sensorFeedback = sensorError/a_scale;//have sensor error properly scale to fit the system
//     }
// 	if(onlyUseEncoderFeedback)
// 		rotationalFeedback = encoderFeedbackW;
// 	else
// 		rotationalFeedback = encoderFeedbackW + sensorFeedback;
// 	    //if you use IR sensor as well, the line above will be rotationalFeedback = encoderFeedbackW + gyroFeedback + sensorFeedback;
// 	    //make sure to check the sign of sensor error.

// 	posErrorX += curSpeedX - encoderFeedbackX;
// 	posErrorW += curSpeedW - rotationalFeedback;
	
// 	posPwmX = kpX * posErrorX + kdX * (posErrorX - oldPosErrorX);
// 	posPwmW = kpW * posErrorW + kdW * (posErrorW - oldPosErrorW);
	
// 	oldPosErrorX = posErrorX;
// 	oldPosErrorW = posErrorW;
	
// 	baseLeftSpeed = posPwmX - posPwmW;
// 	baseRightSpeed = posPwmX + posPwmW;

// 	setLeftPWM(baseLeftSpeed);
// 	setRightPWM(baseRightSpeed);	
// }
void PID() {
	int rotationalFeedback;

	encoderFeedbackX = rightEncoderChange + leftEncoderChange;
	encoderFeedbackW = rightEncoderChange - leftEncoderChange;   // Positive if mouse rotates CW

	// Serial.print(leftEncoderChange);
	// Serial.print(",");
	// Serial.print(rightEncoderChange);
	// Serial.println();

	if (useSensors) {
		sensorFeedback = sensorError/sensor_scale;
	}
	else {
		sensorFeedback = 0;
	}
	turnFeedback = turnFeedback / turn_scale;
	rotationalFeedback = encoderFeedbackW - sensorFeedback - turnFeedback;
	// Serial.println(rotationalFeedback);

	double errorX = curSpeedX - encoderFeedbackX;
   ITermX += (kiX * errorX);
   if (ITermX > outMax) ITermX = outMax;
   else if (ITermX < outMin) ITermX = outMin;
   double dInputX = (curSpeedX - lastSpeedX);

   double errorW = curSpeedW - rotationalFeedback;
   ITermW += (kiW * errorW);
   if (ITermW > outMax) ITermW = outMax;
   else if (ITermW < outMin) ITermW = outMin;
   double dInputW = (curSpeedW - lastSpeedW);

   lastSpeedX = curSpeedX;
   lastSpeedW = curSpeedW;

	double OutputX, OutputW;

	OutputX = kpX * errorX + ITermX - kdX * dInputX;
	if(OutputX > outMax) OutputX = outMax;
   else if(OutputX < outMin) OutputX = outMin;

   OutputW = kpW * errorW + ITermW - kdW * dInputW;
	if(OutputW > outMax) OutputW = outMax;
   else if(OutputW < outMin) OutputW = outMin;

   // Serial.print(OutputW); // Commanded speed
   // Serial.print(',');
   // Serial.println(encoderFeedbackW); // True speed

	baseLeftSpeed= OutputX - OutputW;
	baseRightSpeed = OutputX + OutputW;

	setLeftPWM(baseLeftSpeed);
	setRightPWM(baseRightSpeed);
}

void updateCurrentSpeed() {
	if(curSpeedX < targetSpeedX) {
		curSpeedX += accX;
    	if(curSpeedX > targetSpeedX)
      	curSpeedX = targetSpeedX;
	} 
	else if(curSpeedX > targetSpeedX) {
		curSpeedX -= decX;
		if(curSpeedX < targetSpeedX)
			curSpeedX = targetSpeedX;
	}
	if(curSpeedW < targetSpeedW) {
		curSpeedW += accW;
		if(curSpeedW > targetSpeedW)
			curSpeedW = targetSpeedW;
	}
	else if(curSpeedW > targetSpeedW) {
		curSpeedW -= decW;
		if(curSpeedW < targetSpeedW)
			curSpeedW = targetSpeedW;
	}
	// if (targetSpeedX == 0) {
	// 	curSpeedX = 0;
	// }
	// if (targetSpeedW == 0) {
	// 	curSpeedW = 0;
	// }
}

// void testForward() {
// 	encoderFeedbackX = rightEncoderChange + leftEncoderChange; //forward
// 	encoderFeedbackW = rightEncoderChange - leftEncoderChange;	

// 	posErrorX += curSpeedX - encoderFeedbackX;
// 	posErrorW += curSpeedW - encoderFeedbackW;

	
// 	posPwmX = kpX * posErrorX + kdX * (posErrorX - oldPosErrorX);
// 	posPwmW = kpW * posErrorW + kdW * (posErrorW - oldPosErrorW);
	
// 	oldPosErrorX = posErrorX;
// 	oldPosErrorW = posErrorW;
	
// 	baseLeftSpeed = posPwmX - posPwmW;
// 	baseRightSpeed = posPwmX + posPwmW;

// 	setLeftPWM(baseLeftSpeed);
// 	setRightPWM(baseRightSpeed);
// }

void printPWM(){
	Serial.println("L Speed:");
	Serial.println(baseLeftSpeed);
	Serial.println("R Speed:");
	Serial.println(baseRightSpeed);
}
void resetPID() {
	ITermX = 0;
	ITermW = 0;
	lastSpeedX = 0;
	lastSpeedW = 0;
	curSpeedX = 0;
	curSpeedW = 0;
	encoderCount = 0;
	encoderCountW = 0;
}