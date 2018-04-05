#include "../inc/Pinsetup.h"
#include <Arduino.h>
#include "../inc/Sensor.h"
#include "../inc/Motors.h"
#include "../inc/pwm.h"
#include "../inc/Encoders.h"
// int moveSpeed = 10;
// int turnSpeed = 15;
// int returnSpeed = 10;
// int stopSpeed = 30;
// int maxSpeed = 67; 

// void moveOneCell() {
// 	targetSpeedW = 0;
// 	targetSpeedX = moveSpeed;
// 	distanceLeftX = oneCellDistance;
// 	elapsedMillis wait;
// 	do {
// 		/*you can call int needToDecelerate(int32_t dist, int16_t curSpd, int16_t endSpd)
// 		here with current speed and distanceLeft to decide if you should start to decelerate or not.*/
// 		if(needToDecelerate(distanceLeftX, curSpeedX, 0) < decX)
// 			targetSpeedX = moveSpeed;
// 		else
// 			targetSpeedX = 0;
// 		if (wait > 5) {
// 			// Serial.println(needToDecelerate(distanceLeftX, curSpeedX, moveSpeed));
// 			// Serial.println(encoderCountX-oldEncoderCount);
// 			// Serial.println("In Loop");
// 			wait = 0;
// 		}
// 		//there is something else you can add here. Such as detecting falling edge of post to correct longitudinal position of mouse when running in a straight path
// 		delay(1);
// 	}
// 	while( ((encoderCountX-oldEncoderCount) < oneCellDistance && 
// 		Receiver_L_Reading < targetFront2 && Receiver_R_Reading < targetFront2)	// If no wall in front, use encoders
// 		|| (Receiver_L_Reading < targetFront && Receiver_L_Reading > targetFront2)
// 		|| (Receiver_R_Reading < targetFront && Receiver_R_Reading > targetFront2) // If has front wall, use sensors
// 		 );
// 	//LFvalues1 and RFvalues1 are the front wall sensor threshold when the center of mouse between the boundary of the cells.
// 	//LFvalues2 and RFvalues2 are the front wall sensor threshold when the center of the mouse staying half cell farther than LFvalues1 and 2
// 	//and LF/RFvalues2 are usually the threshold to determine if there is a front wall or not. You should probably move this 10mm closer to front wall when collecting
// 	//these thresholds just in case the readings are too weak.
// 	// Serial.println(frontWall);

// 	if (frontWall) {
// 		while (Receiver_L_Reading < 350) {
// 			targetSpeedX = 5;
// 			delay(1);
// 		}
// 		targetSpeedX = 0;
// 	}

// 	delay(500);
// 	oldEncoderCount = encoderCountX; //update here for next movement to minimized the counts loss between cells.
// }


