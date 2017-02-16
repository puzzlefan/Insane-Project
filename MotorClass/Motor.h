#pragma once
#include <wiringPi.h>
#include <softPwm.h>

class motor
{
private:
	int zgeschwindigkeit =0; //Zielgeschwindigkeit
	int ageschwindigkeit=0; //aktuelle Geschwindigkeit
	int zuwachs=0;//soll den Wert angeben, um denen die aktuelle Geschwindigkeiit erhöht werden soll
	int speed_steps=100;
	int pin_forward,pin_backward;
public:
	motor(int one, int two, int speed);
	void set_speed(int speed);
	/*{
		geschwindigkeit = speed; //Neigung des Joysticks nach vorne/hinten
		return = 0;
	}*/

	void geschwindigkeitsanpassung ();
	/*{
		int differenz(0);//Differenz zwischen Ziel und aktueller Geschwindigkeit

		differenz = zgeschwindigkeit - ageschwindigkeit;
		zuwachs = 0.1*differenz;
		ageschwindigkeit = ageschwindigkeit + zuwachs;
	}*/

	void renew_driver_Speed(int speed);
	int get_a_speed(){return ageschwindigkeit;}
};
