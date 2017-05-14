// C-Up.cpp : Defines the entry point for the console application.
//

#include "C.h"

C::C(Sonar ** flb, Sonar ** flm, Sonar ** flt, Sonar ** frb, Sonar ** frm, Sonar ** frt, Sonar ** blb, Sonar ** blm, Sonar ** blt, Sonar ** brb, Sonar ** brm, Sonar ** brt, Rotationssensor ** wlf, Rotationssensor ** wrf, Rotationssensor ** wlb, Rotationssensor ** wrb, switching ** svl, switching ** svr, switching ** sbl, switching ** sbr, engine ** rvl, engine ** rvr, engine ** rbl, engine ** rbr)//gets the values needed to use the Claas, (Z.B. lenkung; Motoren, Switching, Ultrasch�lle, Rotationssensoren ...
{
	//brings the left ultra sonic sensors in position
	fUS[0][0] = *flb;
	fUS[0][1] = *flm;
	fUS[0][2] = *flt;
	//brings the rigth ultra sonic sensors in position
	fUS[1][0] = *frb;
	fUS[1][1] = *frm;
	fUS[1][2] = *frt;
	//brings the left ultra sonic back sensors in position
	bUS[0][0] = *blb;
	bUS[0][1] = *blm;
	bUS[0][2] = *blt;
	//brings the rigth ultra sonic back sensors in position
	bUS[1][0] = *brb;
	bUS[1][1] = *brm;
	bUS[1][2] = *brt;
	//brings the Switches in position
	Switch[0] = *svl;
	Switch[1] = *svr;
	Switch[2] = *sbl;
	Switch[3] = *sbr;
	//brings the engines in position
	Engines[0] = *rvl;
	Engines[1] = *rvr;
	Engines[2] = *rbl;
	Engines[3] = *rbr;
	//brings the rotation sensors in position
	Wheels[0] = *wlf;
	Wheels[1] = *wrf;
	Wheels[2] = *wlb;
	Wheels[3] = *wrb;
	//					-Anbringungshoehe-needetDistance tan(Maximal Winkel fuer Steigung)
	//Maxschraeghoehe	=	----------------------------------------------------------------
	//					tam(NeigungswinkelSensor) - tan(Maxiaml Winkel fuer Steigung)
	for (int i = 0; i < 2; i++)
	{
		maxSchraegHoehe[i] = ((-(fUS[i][2]->getMountigHigth())) - (needetDistance * tan(DegreeToRad * maxAngle))) / (DegreeToRad * (tan(fUS[i][2]->getmountingAngle()))* tan(maxAngle));
	}
}

void C::UP() {

	//CHECK BOOLS
	if (FirstRound )
	{
		for (int i = 0; i < 4; i++)
		{
			Wheels[i]->resetSteps(i * 2 + 2);
			Wheels[i]->read();
			RotaryEntryStatesforBack[i][0] = Wheels[i]->get_Steps();
			RotaryEntryStatesforBack[i][1] = Wheels[i]->get_Revs();
		}
		FirstRound  = false;	
	}
	if (!OnTheLine)
	{
		OnTheLine = true;
	}
	if (!KeepGoing&&timeoutPlease)// if the process can be paused and somebody wants to pause it just returns and waits for the next round, but the rutine is stil in loop
	{
		timeoutPlease = false;
		return;
	}
	if (!NoWayBack&&cryer)
	{
		reset();
		return;
	}

	//positioning
	if (!primePos) {//positioning for the ride
		int lastRotl = Wheels[0]->get_RSteps();//Get the actual states of rotation
		int lastRotr = Wheels[1]->get_RSteps();

		//read all ultrasonic sensors
		for (int i = 0; i < 2; i++)//read all Ultrasonic Sensors in this direction and store them in the Array
		{
			for (int j = 0; j < 3; j++)
			{
				USm[i][j] = (*fUS[i][j]).calcDistance(timeout);
			}
		}

		if ((!(needetDistance - accuracy <= USm[0][0] &&  USm[0][0] <= needetDistance + accuracy) && !(needetDistance - accuracy <= USm[1][0] && USm[1][0] <= needetDistance + accuracy))||((oneStepForward||oneStepBackward) && !(oneStepLeftFWD||oneStepLeftBWD||oneStepRightFWD||oneStepRightBWD)))//Checks , if no Sensor is matching the wanted distance
		{
			if ((needetDistance - accuracy <= USm[0][0] && needetDistance - accuracy <= USm[1][0])||oneStepForward)//if the distance is greater then the wanted distance it shoul move everything one rotationstep further
			{

				if (!oneStepForward) {
					for (int i = 0; i < 4; i++)//sets the direction to all engines
					{
						(*Engines[i]).set_power(maneuverPower);
					}
					oneStepForward = true;
					oneStepForwardlastRR = lastRotr;
					oneStepForwardlastRL = lastRotl;
				}
				//when you have time you should stop the left and rigth side individual
				if(Wheels[0]->get_RSteps() >= oneStepForwardlastRL + 1 && Wheels[1]->get_RSteps() >= oneStepForwardlastRR + 1 && oneStepForward) {//waits for the movement of one step
					for (int i = 0; i < 4; i++)//stops all engines
					{
						(*Engines[i]).set_power(0);
					}
					oneStepForward = false;
				}
			}
			if ((needetDistance + accuracy >= USm[0][0] && needetDistance + accuracy >= USm[1][0])||oneStepBackward)//if the distance is to small everything moves back
			{
				if (!oneStepBackward) {
					for (int i = 0; i < 4; i++)//same for other direction
					{
						(*Engines[i]).set_power(-maneuverPower);
					}
					oneStepBackward = true;
					oneStepBackwardlastRR = lastRotr;
					oneStepBackwardlastRL = lastRotl;
				}
				//when you have time you should stop the left and rigth side individual
				if(Wheels[0]->get_RSteps() <= oneStepBackwardlastRL - 1 && Wheels[1]->get_RSteps() <= oneStepBackwardlastRR - 1) {
					for (int i = 0; i < 4; i++)
					{
						(*Engines[i]).set_power(0);
					}
					oneStepBackward = false;
				}
			}
		}
		else//if at least one Sensor matches the wanted distance
		{
			if ((!(needetDistance - accuracy <= USm[0][0] && USm[0][0] <= needetDistance + accuracy))||oneStepLeftFWD||oneStepLeftBWD)//Checks if the left Sensor is matching
			{
				if (needetDistance - accuracy < USm[0][0]||(oneStepLeftFWD&&!oneStepLeftBWD))//if it is not matching the distance got shrinked by one step on this side
				{
					if (!oneStepLeftFWD) {
						for (int i = 0; i < 2; i++)//gets al engines for this direction going
						{
							(*Engines[i * 2]).set_power(maneuverPower);
						}
						oneStepLeftFWD = true;
						oneStepLeftFWDlastRL = lastRotl;
					}
					if(Wheels[0]->get_RSteps() >= oneStepLeftFWDlastRL + 1 && oneStepLeftFWD) {//waits for the step
						for (int i = 0; i < 2; i++)//gets all the engines going in the direction stoping
						{
							(*Engines[i * 2]).set_power(0);
						}
						oneStepLeftFWD = false;
					}
				}
				else {//if(needetDistance - accuracy > USm[0][0]) {//or the distane gets greater if needet
					if (!oneStepLeftBWD) {
						for (int i = 0; i < 2; i++)//same...
						{
							(*Engines[i * 2]).set_power(-maneuverPower);
						}
						oneStepLeftBWD = true;
						oneStepLeftBWDlastRL = lastRotl;
					}
					if (Wheels[0]->get_RSteps() <= oneStepLeftBWDlastRL - 1 && oneStepLeftBWD) {
						for (int i = 0; i < 2; i++)
						{
							(*Engines[i * 2]).set_power(0);
						}
						oneStepLeftBWD = false;
					}
				}
			}
			else {//if the left sensor is not matching
				if (!(needetDistance - accuracy <= USm[1][0] && USm[1][0] <= needetDistance + accuracy)||oneStepRightFWD||oneStepRightBWD)//it checks the other side
				{
					if (needetDistance - accuracy < USm[1][0]||(oneStepRightFWD&&!oneStepRightBWD))//same just for the other side
					{
						if (!oneStepRightFWD) {
							for (int i = 0; i < 2; i++)//same ...
							{
								(*Engines[i * 2 + 1]).set_power(maneuverPower);
							}
							oneStepRightFWD = true;
							oneStepRightFWDlastRR = lastRotr;
						}
						if(oneStepRightFWD && Wheels[1]->get_RSteps() >= oneStepRightFWDlastRR + 1) {
							for (int i = 0; i < 2; i++)
							{
								(*Engines[1 + i * 2]).set_power(0);
							}
							oneStepRightFWD = false;
						}
					}
					else {//if(needetDistance - accuracy > USm[1][0]) {//same just for the other side
						if (!oneStepRightBWD) {
							for (int i = 0; i < 2; i++)//same...
							{
								(*Engines[i * 2 + 1]).set_power(-maneuverPower);
							}
							oneStepRightBWD = true;
							oneStepRightBWDlastRR = lastRotr;
						}
						if(oneStepRightBWD && Wheels[1]->get_RSteps() <= oneStepRightBWDlastRR - 1) {
							for (int i = 0; i < 2; i++)
							{
								(*Engines[1 + i * 2]).set_power(0);
							}
							oneStepRightBWD = false;
						}
					}
				}
				else//if we are here all other Sensors are on a distance witch is in the accuracy
				{
					//	middle Sensor if we are goed to go or not
					if (USm[0][1] <= USm[0][0]+accuracy+ lengthDifMidLow || USm[1][1] <= USm[1][0] + accuracy + lengthDifMidLow)
					{
						//when we are here we have a wall that is, if our estimation was correct, not passebele and the C-Programm gets terminated
						reset();
						return;
					}
					//  same for top Sensor (needs to measure earlier to)
					if ((maxSchraegHoehe[0]+accuracy > fUS[0][2]->calcHeigth(timeout) && fUS[0][2]->calcHeigth(timeout) > possibleHigth + accuracy )|| (maxSchraegHoehe[0] + accuracy > fUS[1][2]->calcHeigth(timeout) && fUS[1][2]->calcHeigth(timeout) > possibleHigth + accuracy))
					{
						//if we are here the heighest Sensors thinks the wall or curb is to heigh
						reset();
						return;
					}
					//	When we allready passed this one once we wont do it again until a new curb arrives
					//	point of no return
					NoWayBack = true;
					//	pauses the abbility to pause for a moment
					KeepGoing = true;
					primePos = true;
				}
			}

		}
	}

	//upwards movement
	if (primePos) {
		if(FirstPrimeRound)
		{
			for (int i = 0; i < 4; i++)
			{
				Wheels[i]->resetSteps(i * 2 + 2);
				Wheels[i]->read();
				RotaryEntryStatesforBack[i][0] = Wheels[i]->get_Steps();
				RotaryEntryStatesforBack[i][1] = Wheels[i]->get_Revs();
			}
			FirstPrimeRound = false;
		}
		if(!frontUp){//runs upper until front up gets positive
			frontUpMoving = true;
			if(upper(false)){//makes the moves naccesarry to step on the curb
				//allows pausing
				KeepGoing = false;
				frontUp = true;
				frontUpMoving = false;
			}
		}
		if (!frontUpMoving&&frontUp) {
			//move forward until we can switch the back

			//calculation
			//distance needet for the back wheels = neededDistance+distance betwen the axes
			//if condition needs to be true while the disance between the axes has not been past
			//distance between the axis-change of position through rotation
			//left
			if (distanceAxes>= Wheels[2]->get_distanceFromThenToNow(RotaryEntryStatesforBack[2][0], RotaryEntryStatesforBack[2][1]))
			{
				for (int i = 0; i < 2; i++)
				{
					Engines[i*2]->set_power(upwardsPower);
				}
			}
			else {
				for (int i = 0; i < 2; i++)
				{
					Engines[i*2]->set_power(0);
				}
			}
			//rigth
			if (distanceAxes >= Wheels[3]->get_distanceFromThenToNow(RotaryEntryStatesforBack[3][0], RotaryEntryStatesforBack[3][1]))
			{
				for (int i = 0; i < 2; i++)
				{
					Engines[1 + i * 2]->set_power(upwardsPower);
				}
			}
			else {
				for (int i = 0; i < 2; i++)
				{
					Engines[1 + i * 2]->set_power(0);
				}
			}

			//disables pause until we are complete
			KeepGoing = true;

			if ((!backUp && backUpMoving)||(!backUp && Engines[0]->get_power() == 0 && Engines[2]->get_power() == 0)) {
				backUpMoving = true;
				if (upper(true)) {//moves forward until the back is also on the curb
					KeepGoing = false; // allow pause if you can hit the Switch erly enoug, which is logically impossible but how cares
					backUp = true;
					backUpMoving = false;
				}
			}
			if (!backUpMoving&&backUp) {
				void reset();//free the programm
			}
		}
	}
}

bool C::upper(bool back) {
	if (RoundOne) {
		//safe the initial state of all rotations
		for (int i = 0; i < 4; i++)
		{
			Wheels[i]->read();
			RotaryEntryStates[i][0] = Wheels[i]->get_Steps();
			RotaryEntryStates[i][1] = Wheels[i]->get_Revs();
		}
		RoundOne = false;
		switchDown = true;
	}
	if (switchDown) {
		//switch front
		if(Switch[0 + (back*2)]->down() && Switch[1 + (back * 2)]->down()){
			switchDown = false;
			switchedDown = true;
		}
	}

	//move forward until we can switch again
	if(switchedDown){
		for (int i = 0; i < 4; i++)
		{
			Engines[i]->set_power(upwardsPower);
		}
		switchedDown = false;
		waitToStop = true;
	}
	if (waitToStop && (((RotaryEntryStates[(back * 2)][0] <= Wheels[0]->get_RSteps()) && (RotaryEntryStates[(back * 2)][1] + 1 <= Wheels[0]->get_RRevs())) && ((RotaryEntryStates[1 + (back * 2)][0] <= Wheels[1]->get_RSteps()) && (RotaryEntryStates[1 + (back * 2)][1] + 1 <= Wheels[1]->get_RRevs()))))
	{
		for (int i = 0; i < 4; i++)
		{
			Engines[i]->set_power(0);
		}
		waitToStop = false;
		switchUp = true;
	}
	if (switchUp) {
		if(Switch[0 + (back * 2)]->up()&&Switch[1 + (back * 2)]->up()){
			switchUp = false;
			switchedUp = true;
		}
	}
	if (switchedUp) {
		//reset of all function specific bools
		RoundOne = true;//indicates if we are in the first roundtrip or one of the followuing
		switchDown = false;//indicates if the C should move down
		switchedDown = false;//indicates if it has moved down
		waitToStop = false;// indicates that we are moving and the stop checker is enabled
		switchUp = false;//tells the c to switch up
		switchedUp = false;//tels if the Cs are switched up and determines the return

		return true;
	}
	else{
		return false;
	}
}

void C::reset() {
	//Sets all bools to starting conditions
	NoWayBack = false;
	cryer = false;
	KeepGoing = false;
	timeoutPlease = false;
	primePos = false;
	OnTheLine = false;

	//while avoidence reset joust to be shure nothing can be mist
	FirstRound  = true;
	FirstPrimeRound = true;
	//moving everything forward
	oneStepForward = false;//indicates if the loop is going allready
	//moving everything backwards
	oneStepBackward = false;//indicates if the loop is going allready
	//moving leftside bwd
 	oneStepLeftBWD = false;//indicates if the loop is going allready
	//moving leftside fwd
	oneStepLeftFWD = false;//indicates if the loop is going allready
	//moving rightside bwd
	oneStepRightBWD = false;//indicates if the loop is going allready
	//moving rightside fwd
	oneStepRightFWD = false;//indicates if the loop is going allready
	//bool for ceeping track if we are going up with the front
	frontUp = false;
	frontUpMoving = false;
	//bool for ceeping track if we are going up with the front
	backUp = false;
	backUpMoving = false;
}

//
//Testing paragraph
//
/*Sonar a;
switching * b = new switching(2,3);//The way to initialise
engine c;
C TEST( **a, &a, &a, &a, &a, &a, &b, &b, &b, &b, &c, &c, &c, &c);
int main()
{
    return 0;
}
*/
