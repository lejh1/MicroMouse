#include "../inc/Pinsetup.h"
#include <Arduino.h>
#include "../inc/Sensor.h"
#include "../inc/Motors.h"
#include "../inc/pwm.h"
#include "../inc/Encoders.h"
float curSpeedX = 0;
float curSpeedW = 0;
int targetSpeedX = 0;
int targetSpeedW = 0;
int encoderFeedbackX = 0;
int encoderFeedbackW = 0;
float pidInputX = 0;
float pidInputW = 0;
float posErrorX = 0;
float posErrorW = 0;
float oldPosErrorX = 0;
float oldPosErrorW = 0;
int posPwmX = 0;
int posPwmW = 0;
float kpX = 2, kdX = 4;
float kpW = 1, kdW = 12;//used in straight
float kpW1 = 1;//used for T1 and T3 in curve turn
float kdW1 = 26;
float kpW2 = 1;//used for T2 in curve turn
float kdW2 = 36;
float accX = 600;//6m/s/s  
float decX = 600; 
float accW = 1; //cm/s^2
float decW = 1;

// void calculateMotorPwm(void) // encoder PD controller
// {	
// 	int rotationalFeedback;
// 	int sensorFeedback;
	
//     /* simple PD loop to generate base speed for both motors */	
// 	encoderFeedbackX = rightEncoderChange + leftEncoderChange;
// 	encoderFeedbackW = rightEncoderChange - leftEncoderChange;	
	
// 	sensorFeedback = sensorError/a_scale;//have sensor error properly scale to fit the system
	
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
	
// 	leftBaseSpeed = posPwmX - posPwmW;
// 	rightBaseSpeed = posPwmX + posPwmW;

// 	setLeftPwm(leftBaseSpeed);
// 	setRightPwm(rightBaseSpeed);	
// }