// switching.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include "switching.h"
#include <unistd.h>
#include <wiringPi.h>
#include "../engine/engine.h"


switching::switching(engine ** motor)
{
	//copys the local variables to their global counter part
	modor = *motor;
}
void switching::up() {
	modor->set_power(100);
	usleep(movingTime);
	modor->set_power(0);
}
void switching::down() {
	modor->set_power(-100);
	usleep(movingTime);
	modor->set_power(0);
}
