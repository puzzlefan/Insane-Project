#pragma once
#include <wiringPi.h>
#include <softPwm.h>

//BREMSEN M�SSEN EINGEBAUT WERDEN

class engine
{
private:
	//important booles
	bool forward = true;
	bool moving = false;
	//speed
	int fwd;
	int bwd;
	int PWMrperiodTime = 100;//the maximum time of one puls (if it is at max range it is completly on)
							 //the resolution shortest time are 100 microseconds
							 //procentual power
	float power = 0;

public:
	//initialization no constructor because of the better name
	void initialisEngine(int fPin, int bPin);
	//sets the rotationstate values manually actual values coulb be automatet later
	//returns the rotationstate values
	//other set functions
	void set_power(float pro);
	//other get functions
	float get_power() { return power; }
	//utility functions
	void renew_driver_Speed();
};

