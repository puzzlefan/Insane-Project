#ifndef DEF_SONAR
#define DEF_SONAR
#define _USE_MATH_DEFINES
#include "math.h"
//distances in Meter
class Sonar
{
public:
	Sonar();//Constructr does nothing
	void init(int trigger, int echo);//init for straigth forward Sensors
	void init(int trigger, int echo, int height, int angle);//init for angledS Sensors
	double distance(int timeout);// mesurment function
	double calcDistance(int timeout);//calculated distance for angled sensors 
	double calcHeigth(int timeout);//calculated heigth for angled sensors
	double getMountigHigth() { return height; }
	double getmountingAngle() { return angle; }

private:
	//Functions
	void recordPulseLength();
	//Init values
	int trigger;//-pin
	int echo;//reciver pin
	int height = -1;//the higth in which the speaker and mic are fixed at
	int angle = -1;//the angle, from the mesurement direction to a straigth line to the ground
	//Calculation values
	volatile long startTimeUsec;
	volatile long endTimeUsec;
	double distanceMeters;
	long travelTimeUsec;
	long now;
	const double DegreeToRad = (2 * M_PI) / 360;
};

#endif
