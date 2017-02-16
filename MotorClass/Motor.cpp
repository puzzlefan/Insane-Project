// Motor.cpp : Defines the entry point for the console application.
//

#include "Motor.h"
#include <wiringPi.h>
#include <softPwm.h>
#include <iostream>

void motor::set_speed(int speed){
	zgeschwindigkeit = speed;
}
void motor::geschwindigkeitsanpassung(){
	int differenz = 0;//Differenz zwischen Ziel und aktueller Geschwindigkeit

	differenz = zgeschwindigkeit - ageschwindigkeit;
	zuwachs = 0.1*differenz;
//	std::cout<<zuwachs<<std::endl<<std::flush; Debug  thing...
	if(zuwachs!=0){
		ageschwindigkeit = ageschwindigkeit + zuwachs;
	}
	if(zuwachs==0){
		ageschwindigkeit = zgeschwindigkeit;
	}
	renew_driver_Speed(ageschwindigkeit);
}
void motor::renew_driver_Speed(int speed){
	if(speed == 0){
		softPwmWrite(pin_forward,0);
		softPwmWrite(pin_backward,0);
	}
        if(speed < 0){
                softPwmWrite(pin_forward,0);
                softPwmWrite(pin_backward,speed * -1);
        }
        if(speed > 0){
                softPwmWrite(pin_forward,speed);
                softPwmWrite(pin_backward,0);
        }
}

motor::motor(int one, int two, int speed){
	pin_forward = one;
	pin_backward = two;
	pinMode(pin_forward,OUTPUT);
	pinMode(pin_backward,OUTPUT);
	softPwmCreate(pin_forward,0,speed_steps);
	softPwmCreate(pin_backward,0,speed_steps);
	renew_driver_Speed(speed);
}
