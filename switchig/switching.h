#ifndef switching_H
#define switching_H
#include "../engine/engine.h"
class switching
{
private:
	engine * modor;

	bool	beneath = true;
	bool	moving = false;
	bool	movingUp = false;

	//int fwd, bwd;
	int movingTime = 1000;//time for one way in micro seconds [10^-6 s]
						  //int contactPin;//Can be activated as you have somethning to check the position of the C in a certain place this would be the signal pin
public:
	switching(engine ** motor);//Initlaises the class
	void up();//moves the square to its top position
	void down();//moves the square to its lower position
};
#endif
