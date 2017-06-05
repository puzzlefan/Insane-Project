#ifndef RotationssensorArduino_H
#define	RotationssensorArduino_H
#include "../Schnittstelle/InterfaceI2C.h"
class Rotationssensor
{
private:
	//values for the constructor
	int StepReg, RevsReg, MaxSteps, DegreePerStep;
	Schnittstelle ** Interface;

	int Steps;
	int Revs;
	int acTime;
	int last[10][2] = { { 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 },{ 0,0 } };

	double d = 0.225;//mesuret in meter
public:
	Rotationssensor(int RegSteps, int RegRevs, Schnittstelle ** Interface);
	void read();
	int get_Steps() { return Steps; }
	int get_RSteps();//returns the steps and reads the actual position
	int get_Revs() { return Revs; }
	//You STILL have to think at the adge case that the next revolution is a zero!
	int get_RRevs();//returns the revolutions and reads the actual position 
	int get_angle() { return DegreePerStep*Steps; }
	double get_diameter() { return d; }
	double get_distance();
	//You STILL have to think at the adge case that the next revolution is a zero!
	//done to late maybe rethink neccessary
	double get_distanceFromThenToNow(int oldSteps, int oldRoation);
	double get_maxPosDis();//returns the maximal possible distance

	int get_oldSteps(int pos);
	int get_oldRevs(int pos);

	void resetSteps();
};

#endif
