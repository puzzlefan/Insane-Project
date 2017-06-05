/*
#ifndef Rotationssensor_H
#define Rotattionssensor_H

#include<wiringPi.h>
#include<iostream>
#include<math.h>

using namespace std;
class Rotationssensor {
private:
	//physical positions
	int lBOne = 0;//Ligth barrier one
	int lBTwo = 0;//Ligth barrier two

	//calculation values
	int toothCount = 20;//quantity of toothwheel tooth
	int maxSteps = toothCount * 4;//steps per round

	//calculated Values
	int Steps = 0;//allready taken steps of the round
	int rotation = 0;//actual Angle in degree starts at every rotation at zero
	int revolutions = 0;//counts the revolution, revolutions backwards get substracted

						//bools for counting
	bool lBOneNewStat = false;//turns true if the first sensors actual state was activ
	bool lBTwoNewStat = false;//turns true if the second sensors actual state was activ
	bool lBOneStat = false;//turns true if the first sensors last state was activ
	bool lBTwoStat = false;//turns true if the second sensors last state was activ
	bool dir = false;//indicates the direction
	bool directions[4][2] = { { false,true },{ false,false },{ true,false },{ true,true } };//state first Sensor, state second Sensor
	bool * actStat[2] = { &lBOneStat,&lBTwoStat };
	int pos = 0;//last combined state
	int maxPos = 3;
	int posi(int newPos);
	void determineDir();
public:
	RotaryEncoder(int P1, int P2);//sets the encoder up
	void Check();//checks if any counting is necesary
	int getSteps() { return Steps; }//returns the actual count of steps
	int getDegree() { return (360 / maxSteps * Steps); }
	int getRevs() { return revolutions; }
	int getV();
	int getMaxSteps() { return maxSteps; }
	void set_Revs(int revs) { revolutions = revs; }
};

#endif
*/
