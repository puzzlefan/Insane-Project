#pragma once
class switching
{
private:
	bool	beneath = true;
	bool	moving = false;
	bool	movingUp = false;

	int fwd, bwd;
	int movingTime = 1000;//time for one way in micro seconds [10^-6 s]
						  //int contactPin;//Can be activated as you have somethning to check the position of the C in a certain place this would be the signal pin 
public:
	switching(int forwardP, int backwardP);//Initlaises the class
	void up();//moves the square to its top position
	void down();//moves the square to its lower position
};