#include "RotationssensorArduino.h"
#include "../Schnittstelle/InterfaceI2C.h"
#include "time.h"
#define _USE_MATH_DEFINES
#include "math.h"

Rotationssensor::Rotationssensor(int RegSteps, int RegRevs, Schnittstelle ** Intercom)
{
	Interface = Intercom;
	StepReg = RegSteps;
	RevsReg = RegRevs;
	MaxSteps = (**Interface).I2C16Read((**Interface).get_connectionToken(), (**Interface).get_RegMaxSteps());
	DegreePerStep = 360 / MaxSteps;
}

void Rotationssensor::read()
{
	Steps = (**Interface).I2C16Read((**Interface).get_connectionToken(), StepReg);
	Revs = (**Interface).I2C16Read((**Interface).get_connectionToken(), RevsReg);
	acTime = time(0);
	if (Steps != last[0][0]) {
		for (int i = 9; i > 0; i--) {
			last[i][0] = last[i - 1][0];
			last[i][1] = last[i - 1][1];
//			last[i][2] = last[i - 1][2];
		}
		last[0][0] = Steps;
		last[0][1] = Revs;
//		last[0][2] = acTime;
	}
}

double Rotationssensor::get_distance()
{
	double reture = d * M_PI;
	reture *= Steps / MaxSteps;
	return reture;
}

double Rotationssensor::get_maxPosDis()
{
	return d * M_PI;;
}

int Rotationssensor::get_oldSteps(int pos)
{
	if (pos > 9) {
		pos = 9;
	}
	if (pos < 0) {
		pos = 0;
	}
	return last[pos][0];
}

int Rotationssensor::get_oldRevs(int pos)
{
	if (pos > 9) {
		pos = 9;
	}
	if (pos < 0) {
		pos = 0;
	}
	return last[pos][1];
}

int Rotationssensor::get_RSteps() {
	read();
	return get_Steps();
}
int Rotationssensor::get_RRevs() {
	read();
	return get_Revs();
}

double Rotationssensor::get_distanceFromThenToNow(int oldSteps, int oldRoation) {
	double reture = 0;
	double calc = get_RRevs() - oldRoation - 1;
	if (calc >= 0)
	{
		reture += (get_RRevs() - oldRoation - 1) * (d * M_PI);
		reture += (MaxSteps - get_RSteps()) * ((d * M_PI) / MaxSteps);
		reture += (MaxSteps - oldSteps) * ((d * M_PI) / MaxSteps);
	}
	else
	{
		calc = oldRoation  - get_RRevs() - 1;
		if (calc >= 0)
		{
			reture += (get_RRevs() - oldRoation - 1) * (d * M_PI);
			reture += (- get_RSteps()) * ((d * M_PI) / MaxSteps);
			reture += (- oldSteps) * ((d * M_PI) / MaxSteps);
		}
		else {
			reture += (get_RSteps() - oldSteps) * ((d * M_PI) / MaxSteps);
		}
	}
	return reture;
}

void Rotationssensor::resetSteps() {
	(*Interface)->I2C8Write((*Interface)->get_connectionToken(),255,0);//trigers reset command
}
