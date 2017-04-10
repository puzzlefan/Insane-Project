// switching.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "switching.h"
#include <unistd.h>
#include <wiringPi.h>



switching::switching(int forwardP, int backwardP)
{
	//copys the local variables to their global counter part
	fwd = forwardP;
	bwd = backwardP;
	//contactPin = contactP; also just in use as you would have a wax to check the position
	//initialises the engine pins
	pinMode(fwd, OUTPUT);
	pinMode(bwd, OUTPUT);
	//pinMode(contactPin, INPUP);//same
	//make sure the engine is turned off
	digitalWrite(fwd, LOW);
	digitalWrite(bwd, LOW);
}
void switching::up() {
	digitalWrite(fwd,HIGH);
	usleep(movingTime);
	digitalWrite(fwd, LOW);
}
void switching::down() {
	digitalWrite(bwd, HIGH);
	usleep(movingTime);
	digitalWrite(bwd, LOW);
}


