#include "Rotationssensor.h"
#include <wiringPi.h>
#include <iostream>
#include <pthread.h>

int Wfail = wiringPiSetup();
rotationssensor test;


void RotationLV1(){
        test.rotationscount(1);
}
void  RotationLV2(){
       test.rotationscount(2);
}


void interrupts(){
        wiringPiISR(24, INT_EDGE_BOTH, &RotationLV1);
        wiringPiISR(25, INT_EDGE_BOTH, &RotationLV2);

}

int main() {
	interrupts();
	while(true){
//	std::cout<<test.get_velocity()<<std::endl;
	}
	return 0;
}
