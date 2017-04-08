#ifndef Rotationssensor_H
#define Rotattionssensor_H

#include<wiringPi.h>
#include<iostream>
#include<math.h>

using namespace std;
class rotationssensor {
private:
	//definition of the reallife addicted variables
	int pinOne = 24;//wiringPi Number
	int pinTwo = 25;//wiringPi Number
	int totalstepcount = 10;
	float diameter = 0.225;//meter
	float maxSpeed = 20;//meter/sekunde

	//variables which are calculated from the above specificated variables
	int angleperstep = 360 / totalstepcount;
	float wayperstep = (radius*radius*atan(1) * 4) / totalstepcount;
	float radius = diameter / 2;
	float minT = ((diameter*atan(1)*4)/(maxSpeed*totalstepcount))*1000;//milli Sekunde

	//variavles which are changing at runtime
//	float totaldistance = 0; see actual angle as long as not needed in the class
	float v = 0;
	float StartMSec = minT;
	float EndMSec;
	float passedTime;
	int stepcount = 0;
//	int actualangle = 0;  the interrupt needs to be short so unessesary calculations are onlly made on demand
	int turns = 0;

	bool moving = false;//indicates if the devise is moving
	bool forward = true;//indicates the direction

	char directionOld;//holds the last activated State to compare if the following on was triggerd
	char directionNew;//the other needed one for the before discribed action

	float mTime;//is used to ceep track of the passed time for 20 steps to calculate the "normal" velocity

public:
	void rotationscount(int i);
	int get_actualangle() { return stepcount * angleperstep; }//claculates the actual angle and returns it
	int get_turns() { return turns; }
	int get_stepcount() { return stepcount; }
	float get_velocity(){ return v;}
	float get_wayperstep(){return wayperstep;}
	float get_totaldistnce(){return totalstepcount * wayperstep + stepcount * wayperstep;}
	float get_mTime(){return mTime}
};

#endif
