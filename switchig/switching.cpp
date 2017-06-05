// switching.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "switching.h"
//#include <unistd.h>
#include <time.h>
#include <wiringPi.h>
#include "../engine/engine.h"
#include <chrono>

switching::switching(engine ** motor)
{
	//copys the local variables to their global counter part
	modor = *motor;
}

void switching::SetUp(double UPTime, double DownTime){
	this->UPTime=UPTime;
	this->DownTime=DownTime;
}

bool switching::up() {
	if (start) {
		modor->set_power(100);
		start = false;
		waiting = true;
	}
	if(waiting){
		if (waitingFirst) {
			beginn = std::chrono::system_clock::now();
			waitingFirst = false;
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_time = end - beginn;
		if (elapsed_time.count()>= UPTime) {
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
		if (waitingFirst) {
			beginn = std::chrono::system_clock::now();
			waitingFirst = false;
		}
		end = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_time = end - beginn;
		if (elapsed_time.count()>= DownTime) {
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
