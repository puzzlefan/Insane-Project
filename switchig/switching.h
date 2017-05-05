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
	int movingTime = 1000;//time for one way in nano seconds [10^-9 s]
						  //int contactPin;//Can be activated as you have somethning to check the position of the C in a certain place this would be the signal pin

	//while avoidence bools
	bool start = true;
	bool waiting = false;
	bool ending = false;
	bool waitingFirst = true;
	//further while avoidence
	//link if it doesnt seem to work:
	//https://www.google.de/search?q=clock_gettime(CLOCK_MONOTONIC%2C)&rlz=1C1CHBD_deDE720DE720&oq=clock_gettime(CLOCK_MONOTONIC%2C)&aqs=chrome..69i57j0l5.432j0j7&sourceid=chrome&ie=UTF-8
	//https://linux.die.net/man/3/clock_gettime
	unsigned double comparisonEvent = 0;
	struct acttime {
        time_t   tv_sec;        /* seconds */
        long     tv_nsec;       /* nanoseconds */
};
acttime Time;
public:
	switching(engine ** motor);//Initlaises the class
	bool up();//moves the square to its top position
	bool down();//moves the square to its lower position
};
#endif
