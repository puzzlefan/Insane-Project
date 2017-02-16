#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>
#include "Motor.h"

motor marder(25,24,0);
int sped = 50;
int main()
{
	if(wiringPiSetup()==-1){return 1;}
	//pinMode (pin, OUTPUT);
	//digitalWrite(pin,HIGH);
	marder.set_speed(sped);
	for(int i=0;i<=75;i++){
		marder.geschwindigkeitsanpassung();
		std::cout<<marder.get_a_speed()<<std::endl<<std::flush;
		delay(100);
	}
	marder.set_speed(-sped);
        for(int i=0;i<=75;i++){
                marder.geschwindigkeitsanpassung();
                std::cout<<marder.get_a_speed()<<std::endl<<std::flush;
                delay(100);
        }
	//digitalWrite(pin,LOW);
	return 0;
}

