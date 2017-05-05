// switching.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "switching.h"
#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include "../engine/engine.h"


switching::switching(engine ** motor)
{
	//copys the local variables to their global counter part
	modor = *motor;
}
bool switching::up() {
	if (start) {
		modor->set_power(100);
		start = false;
		waiting = true;
	}
	if(waiting){
		if (-1 == clock_gettime(CLOCK_MONOTONIC,&Time)) {
			//Error Handling here
		}
		if (waitingFirst) {
			comparisonEvent = (unsigned double) Time.tv_nsec + ((unsigned double) Time.tv_sec) * 1000000000;
			waitingFirst = false;
		}
		if (comparisonEvent + movingTime <= (unsigned double) Time.tv_nsec + ((unsigned double) Time.tv_sec) * 1000000000) {
			waiting = false;
			ending = true;
		}
	}
	if (ending) {
		modor->set_power(0);
		//resetting of the bools
		start = true;
		waiting = false;
		ending = false;
		waitingFirst = true;
		return true;
	}
	else{
		return false;
	}
}
bool switching::down() {
	if (start) {
		modor->set_power(-100);
		start = false;
		waiting = true;
	}
	if(waiting){
		if (-1 == clock_gettime(CLOCK_MONOTONIC,&Time)) {
			//Error Handling here
		}
		if (waitingFirst) {
			comparisonEvent = (unsigned double) Time.tv_nsec + ((unsigned double) Time.tv_sec) * 1000000000;
			waitingFirst = false;
		}
		if (comparisonEvent + movingTime <= (unsigned double) Time.tv_nsec + ((unsigned double) Time.tv_sec) * 1000000000) {
			waiting = false;
			ending = true;
		}
	}
	if (ending) {
		modor->set_power(0);
		//resetting of the bools
		start = true;
		waiting = false;
		ending = false;
		waitingFirst = true;
		return true;
	}
	else{
		return false;
	}
}
