#include<wiringPi.h>
#include<iostream>
#include "Rotationssensor.h"
#include <pthread.h>

void rotationssensor::rotationscount(int i){
	EndMSec = millis();//stops time mesurment
	passedTime = EndMSec - StartMSec;//calculates passed time
	if(passedTime>=minT){//checks if the code is allowed to get exrcutet
		StartMSec = millis();//reststarts the timer

		if(stepcount==totalstepcount){//if a rotation is complitet a new one is started, to do so the steps variable is revoked to 0
			stepcount = 0;
			turns++;
		}
		if(i == 1){//Checks how has activated the count
			if(digitalRead(pinOne)){
				directionNew = 0;
			}
			else{
				directionNew = 2;
			}
		}
		else{
			if(digitalRead(pinTwo)){
       				directionNew = 1;
                        }
                        else{
				directionNew = 3;
                        }
		}

		stepcount++;//adds a step habpens here because the stuff before needs to happen fast

		if(directionOld==directionNew){//checks if we are moving and in which direction
			moving = false;
			v = 0;
		}
		else{
			moving = true;
			v = ((wayperstep*1000)/ passedTime);//calculates velocity
			if(directionOld<=directionNew || (directionOld==3 && directionNew == 0)){
				forward = true;
			}
			else{
				forward = false;
				v *= -1;
			}
		}
	}
}
