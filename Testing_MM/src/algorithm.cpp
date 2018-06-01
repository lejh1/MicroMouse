#include "../inc/Pinsetup.h"
#include "../inc/Sensor.h"
#include "../inc/Motors.h"
#include "../inc/pwm.h"
#include "../inc/Encoders.h"
#include "../inc/Movement.h"
#include "../inc/algorithm.h"

#include <Arduino.h>
void randomAlg(){
    if(!frontWall && leftWall && rightWall){  // can go only foward
        moveOneCell();        
    }else if(!frontWall && !leftWall && rightWall){ //can go forward or left 
        if (random(millis()) % 2) { 
			turnLeft();
		}
		else {
			moveOneCell();
		}
    }else if(!frontWall && leftWall && !rightWall){ //can go forward or right
        if (random(millis()) % 2) {   
			moveOneCell();
		}
		else {
			turnRight();
		}
    }else if(frontWall && !leftWall && !rightWall){ //can go left or right
        if (random(millis()) % 2) {   // Turn left or right randomly
            turnLeft();
        }
        else {
            turnRight();
        }
        moveOneCell();
    }else if(frontWall && leftWall && !rightWall){ //can go only right
        turnRight();
        moveOneCell();
    }else if(frontWall && !leftWall && rightWall){ //can go only left
        turnLeft();
        moveOneCell();
    }else if(frontWall && leftWall && rightWall){ //needs to turn around
        turnRight();
        turnRight();
        moveOneCell();
    }else if(!frontWall && !leftWall && !rightWall){ //any direction 
        if (random(millis()) % 3 == 2) {
                turnRight();
            }
            else if (random(millis()) % 3 == 1) {
                turnLeft();
            }
        moveOneCell();
    }

}