#include "engine.h"
#include <softPwm.h>

void engine::initialisEngine(int fPin, int bPin) {
	int x = wiringPiSetup();
	fwd = fPin;
	bwd = bPin;
	pinMode(fwd, OUTPUT);
	pinMode(bwd, OUTPUT);
	softPwmCreate(fwd, 0, PWMrperiodTime);
	softPwmCreate(bwd, 0, PWMrperiodTime);

}

void engine::set_power(float pro) {
	if (pro >= 100)
	{
		power = 100;
	}
	else
	{
		if (pro <= -100)
		{
			power = -100;
		}
		else
		{
			power = pro;
		}
	}
}

void engine::renew_driver_Speed() {
	if (power == 0) {
		moving = false;
		softPwmWrite(fwd, 0);
		softPwmWrite(bwd, 0);
	}
	else
	{
		moving = true;
		if (power < 0)
		{
			forward = false;
			softPwmWrite(fwd, 0);
			softPwmWrite(bwd, -1 * power);
		}
		else
		{
			forward = true;
			softPwmWrite(fwd, power);
			softPwmWrite(bwd, 0);
		}
	}
}