#include "../inc/Pinsetup.h"
#include <Arduino.h>
#include "../inc/Sensor.h"
#include "../inc/Motors.h"
#include "../inc/pwm.h"
#include "../inc/Encoders.h"

elapsedMillis wait_ms;
elapsedMicros wait_us;
int moveSpeed = 10;
int turnSpeed = 10;
int returnSpeed = 10;
int stopSpeed = 30;
int maxSpeed = 67; 

// int oneTurnDistance = 340;
// int oneTurnDistance = 185;
int oneTurnDistance = 501;
int leftTurnDistance = 492;
int oneCellDistance = 476;


double needToDecelerate(int dist, double curSpd, double endSpd) { //speed are in encoder counts/ms, dist is in encoder counts 
	if (curSpd<0) curSpd = -curSpd;
	if (endSpd<0) endSpd = -endSpd;
	if (dist<0) dist = 1;
	if (dist == 0) dist = 1;  //prevent divide by 0

	return (abs(curSpd*curSpd - endSpd*endSpd)/dist/4/2);
	//calculate deceleration rate needed with input distance, input current speed and input targetspeed to determind if the deceleration is needed
	//use equation 2*a*S = Vt^2 - V0^2  ==>  a = (Vt^2-V0^2)/2/S
	//because the speed is the sum of left and right wheels(which means it's doubled), that's why there is a "/4" in equation since the square of 2 is 4
}

void moveOneCell() {
	useSensors =false;

	// useSensors = false;
	targetSpeedW = 0;
	targetSpeedX = moveSpeed;
	distanceLeft = oneCellDistance;
	elapsedMillis wait;
	do {
		/*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
		here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
		if(needToDecelerate(distanceLeft, curSpeedX, 0) < decX)
			targetSpeedX = moveSpeed;
		else
			targetSpeedX = 0;
		if (wait > 5) {
			// Serial.println(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed));
			// Serial.println(encoderCountX-oldEncoderCount);
			// Serial.println("In Loop");
			wait = 0;
		}
		//there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
		delay(1);
	}
	while( ((encoderCount-oldEncoderCount) < oneCellDistance && 
		TrueValueLeft < targetFront2 && TrueValueRight < targetFront2)	// If no wall in front, use encoders
		|| (TrueValueLeft < targetFront && TrueValueLeft > targetFront2)
		|| (TrueValueRight < targetFront && TrueValueRight > targetFront2) // If has front wall, use sensors
		 );
	//LFvalues1 and RFvalues1 are the front wall sensor threshold when the center of mouse between the boundary of the cells.
	//LFvalues2 and RFvalues2 are the front wall sensor threshold when the center of the mouse staying half cell farther than LFvalues1 and 2
	//and LF/RFvalues2 are usually the threshold to determine if there is a front wall or not. You should probably move this 10mm closer to front wall when collecting
	//these thresholds just in case the readings are too weak.
	// Serial.println(frontWall);

	if (frontWall) {
		while (TrueValueLeft < 200) {
			targetSpeedX = 5;
			delay(1);
		}
		targetSpeedX = 0;
	}	
	useSensors =false;
	delay(500);
	oldEncoderCount = encoderCount; //update here for next movement to minimized the counts loss between cells.
	resetPID();
	// useSensors = true;
}
void turnRight() {
	targetSpeedX = 0;
	useSensors = false;
	elapsedMillis wait;
	distanceLeftW = -oneTurnDistance;
	while (distanceLeftW < 0) {
		targetSpeedW = -turnSpeed;
		delay(5);
		// Serial.println(targetSpeedW);
	}
	turnFeedback = 0;
	targetSpeedW = 0;
	delay(1000);
	// useSensors = true;
	resetPID();
}

void turnLeft() {
	targetSpeedX = 0;
	useSensors = false;
	elapsedMillis wait;
	distanceLeftW = leftTurnDistance;
	while (distanceLeftW > 0) {
		targetSpeedW = turnSpeed;
		delay(5);
		// Serial.println(targetSpeedW);
	}
	turnFeedback = 0;
	targetSpeedW = 0;
	delay(1000);
	// useSensors = true;
	resetPID();
}
// void Forward() {
// 	targetSpeedW = 0;
// 	targetSpeedX = moveSpeed;
// 	distanceLeftX = 300;
// 	do {
// 		if (Receiver_L_Reading > targetFront || Receiver_R_Reading > targetFront) {
// 			if(needToDecelerate(300, curSpeedX, 0) < decX) {
// 				targetSpeedX = moveSpeed;
// 			}
// 			else {
// 				targetSpeedX = 0;
// 			}
// 		} 
// 		else {
// 			if(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed) < decX)
// 				targetSpeedX = maxSpeed;
// 			else
// 				targetSpeedX = moveSpeed;
// 		}
// 	}
// 	while ( (encoderCountX-oldEncoderCount) < 900);
// 	oldEncoderCount = encoderCountX;
// }

void pressToStart(){
	while(1){
		if(TrueValueLeft > 500){
			break;
		}
		delay(5);
		// Serial.println("waiting");
	}
}