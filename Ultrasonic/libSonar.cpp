#include <iostream>
#include <wiringPi.h>
#include "libSonar.h"//has to be changed back to orrigenel Files
#include "math.h"

Sonar::Sonar() {}

void Sonar::init(int trigger, int echo)
{
	this->trigger = trigger;
	this->echo = echo;
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
	digitalWrite(trigger, LOW);
	delay(500);
}
void Sonar::init(int trigger, int echo, int height, int angle) {
	this->trigger = trigger;
	this->echo = echo;
	this->height = height;
	this->angle = angle;
	pinMode(trigger, OUTPUT);
	pinMode(echo, INPUT);
	digitalWrite(trigger, LOW);
	delay(500);
}

double Sonar::distance(int timeout)
{
	delay(10);

	digitalWrite(trigger, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigger, LOW);

	now = micros();

	while (digitalRead(echo) == LOW && micros() - now<timeout);
	recordPulseLength();

	travelTimeUsec = endTimeUsec - startTimeUsec;
	distanceMeters = 100 * ((travelTimeUsec / 1000000.0)*340.29) / 2;

	return distanceMeters;
}

void Sonar::recordPulseLength()
{
	startTimeUsec = micros();
	while (digitalRead(echo) == HIGH);
	endTimeUsec = micros();
}

double Sonar::calcDistance(int timeout) {
	double mesurment = distance(timeout);//mesures distance
	if (angle != -1) {	
		mesurment = mesurment * sin(angle * DegreeToRad);//triangle calcuations to get the distance
	}
	return mesurment;
}

double Sonar::calcHeigth(int timeout) {
	if (angle != -1 ) {
		double mesurment = distance(timeout);//mesures distance
		mesurment = mesurment * cos(angle * DegreeToRad);//triangle calcuations to get the distance
		return mesurment;
	}
	else
	{
		return height;
	}
	
}
