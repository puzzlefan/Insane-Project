#define _USE_MATH_DEFINES
#include "math.h"
#include "../Ultrasonic/libSonar.h"
#include "../engine/engine.h"
#include "../switchig/switching.h"
#include "../rotaryencoder/RotationssensorArduino.h"

class C
{
private:
	//
	//Used Classes
	//
	//Array of Sonar Sensors  0 = bottom -> 2 = top
	Sonar * fUS[2][3];//0= Left, 1=Rigth ;0=bottom 2=top
	Sonar * bUS[2][3];//"
	//Array of Rotationsensors at the wheels
	Rotationssensor * Wheels[4]; //0= LV, 1 = RV, 2= HL ...
	//Array of Switchers
	switching * Switch[4];
	//Array of engines
	engine * Engines[4];
	//
	//Used variables
	//
	//for steering
	bool NoWayBack = false;//indicates, if the process can terminated
	bool cryer = false;//indicates if someone  wants to give up
	bool KeepGoing = true;//indicates, if the process can pe paused
	bool timeoutPlease = false;//idicates that someone wants to make a break
	//for continues operation
	bool OnTheLine = false;//indicates if the switch needs to keep this active
	//indicates if we have allready bin in position
	bool primePos = false;
	//
	//constants
	//
	//!!!
	const double diameterWheel = 0.225;
	const double extentWheel = diameterWheel * M_PI;
	const double maxRadiusC = 0.2458;
	const double extentC = 0.68273;
	const double needetDistance = extentC+extentWheel;//measuret in meters //needs to be calculated
	const double distanceAxes = 1.00103;
	const double possibleHigth = maxRadiusC-(diameterWheel/2);

	const double maxAngle = 30;//max Angle in degrees where something is considerd as a slope
	//!!!
	const double heigthLowest = 0.1;
	const double heigthMiddel = 0.2;
	const double heigthHighest = 1;

	const double accuracy = 0.017;//mesuarments out the Arduino forum
	const double DegreeToRad = (2 * M_PI) / 360;
	const double maneuverPower = 100;
	const double upwardsPower = 100;
	const int timeout = 30000;//value out of the example from the originel Libsonar library 
	//caculatet consts
	const double	lengthDifMidLow = sin((2 * M_PI) - (DegreeToRad * maxAngle)) * (heigthMiddel - heigthLowest);// distance difference that is needet to define something as a slope
	double maxSchraegHoehe[2];
	//
	//measurements
	//
	double USm[2][3];//stores the measuret distances
	int RotaryEntryStates[4][2];//safes the position of the rotary encoders, so that we can return if the breakup goes that far
	int RotaryEntryStatesforBack[4][2];//safes the position of the rotary encoders, so that we can return if the breakup goes that far

	//functions
	void reset();//resets the class to initial position
	void upper(bool back);//switches and moves until one pair of wheels has changed it higth in a full circle
public:
	C(Sonar ** flb, Sonar ** flm, Sonar ** flt, Sonar ** frb, Sonar ** frm, Sonar ** frt, Sonar ** blb, Sonar ** blm, Sonar ** blt, Sonar ** brb, Sonar ** brm, Sonar ** brt, Rotationssensor ** wlf, Rotationssensor ** wrf, Rotationssensor ** wlb, Rotationssensor ** wrb, switching ** svl, switching ** svr, switching ** sbl, switching ** sbr, engine ** rvl, engine ** rvr, engine ** rbl, engine ** rbr);//gets the values needed to use the Claas, (Z.B. lenkung; Motoren, Switching, Ultrasch�lle, Rotatiosensoren...
	void UP();//starts the C up sequence
	void DOWN();//starts the C don sequence

	void set_pause() { timeoutPlease = true; }
	void set_end() { cryer = true; }
	bool getOnlineStat() { return OnTheLine; }
};



