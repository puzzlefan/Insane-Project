// manuelControl.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
//#include <initializer_list>
#include <string>
#include "manuelControl.h"
#include "../engine/engine.h"
#include "../Ultrasonic/libSonar.h"
#include "../Displays/lcm1602.h"
#include "../rotaryencoder/RotationssensorArduino.h"


using namespace std;
//constructor
manualOverwrite::manualOverwrite(LCM ** lcm,Sonar ** flb, Sonar ** flm, Sonar ** flt, Sonar ** frb, Sonar ** frm, Sonar ** frt, Sonar ** blb, Sonar ** blm, Sonar ** blt, Sonar ** brb, Sonar ** brm, Sonar ** brt, engine ** rvl, engine ** rvr, engine ** rbl, engine ** rbr, engine ** cvl, engine ** cvr, engine ** cbl, engine ** cbr,Rotationssensor ** rotLV, Rotationssensor ** rotRV, Rotationssensor ** rotLH, Rotationssensor ** rotRH)
{
	this->lcm=*lcm;
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
	//brings the engines in position
	engines[0] = *rvl;
	engines[1] = *rvr;
	engines[2] = *rbl;
	engines[3] = *rbr;
	//brings the C-Engines in position
	Cengines[0] = *cvl;
	Cengines[1] = *cvr;
        Cengines[2] = *cbl;
        Cengines[3] = *cbr;
	//brings the rotationssensors in Position
	Roti[0] = *rotLV;
	Roti[1] = *rotRV;
	Roti[2] = *rotLH;
	Roti[3] = *rotRH;
}
//private Functions
void manualOverwrite::print(std::string toPrint, std::string toPrintTwo) {
	lcm->clear();
	lcm->write(0,0,toPrint);
	lcm->write(0,1,toPrintTwo);
//	std::cout<<toPrint<<" Zeile 2: "<<toPrintTwo<<std::endl;Debug output
}
int manualOverwrite::evenLine() {
	int reture = 0;
	if (depth == minDepth) { reture = 0; }
	if (depth == 1)
	{
		reture = chosenPoth[depth - 1];
	}
	if (depth==maxDepth)
	{
		int position = chosenPoth[0];
		for (int i = 0; i < position; i++)
		{
			reture += (maxPos[i][1] + 1);
		}
		reture += chosenPoth[depth - 1];
	}
	return reture;
}
int manualOverwrite::odLine() {
	int reture = 0;
	if (depth == minDepth) { reture = pos; }
	if (depth == 1)
	{
		int position = chosenPoth[depth-1];
		for (int i = 0; i < position; i++)
		{
			reture += (maxPos[i][1] + 1);
		}
		reture += pos;
	}
	if (depth==maxDepth)
	{
		int position = chosenPoth[depth - 2];
		for (int i = 0; i < position; i++)
		{
			reture += (maxPos[i][2] + 1)*(maxPos[i][1] + 1);
		}
		position = chosenPoth[depth - 1];
		reture += (maxPos[chosenPoth[depth - 2]][2] + 1)*(position);
		reture += pos;
	}
	return reture;
}
//public functions
void manualOverwrite::renewNavVar(int DLR, int DTB, int XAc) {
	this->DLR = DLR;
	this->DTB = DTB;
	this->XAc = XAc;
}
void manualOverwrite::navigate(){
	if (lastPosNavi[0] != DLR) {
		if (DLR < 0)
		{
			chosenPoth[depth] = 0;
			depth--;
			if (depth < 0) { depth = minDepth; }
			pos = chosenPoth[depth];
			chosenPoth[depth] = pos;
		}
		if (DLR > 0)
		{
			chosenPoth[depth] = pos;
			pos = 0;
			depth++;
			if (depth > maxDepth) { depth = maxDepth; }
			chosenPoth[depth] = pos;
		}
		lastPosNavi[0] = DLR;
	}
	else
	{
		if (lastPosNavi[1] != DTB) {
			if (DTB < 0)
			{
				pos--;
				if (pos < 0) { pos = maxPos[chosenPoth[0]][depth]; }
				chosenPoth[depth] = pos;
			}
			if (DTB > 0)
			{
				pos++;
				chosenPoth[depth] = pos;
				if (pos > maxPos[chosenPoth[0]][depth]) { pos = 0; }
			}
			lastPosNavi[1] = DTB;
		}
		else
		{
			if (lastPosNavi[2] != XAc&&depth == maxDepth)
			{
				lastPosNavi[2] = XAc;
			}
		}
	}
}
void manualOverwrite::express() {
		int od = odLine();
		int var = 0;//holds the outpuvalue if needed
		if(depth==maxDepth){
			switch (od)
			{
			case 0:
				//engines front to XAc
				engines[0]->set_power(XAc);
				engines[1]->set_power(XAc);
				var = XAc;
				break;
			case 1:
				//engines back to XAc
				engines[2]->set_power(XAc);
				engines[3]->set_power(XAc);
				var = XAc;
				break;
			case 2:
				//engine front left to XAc
				engines[0]->set_power(XAc);
				var = XAc;
				break;
			case 3:
				//engine front rigth to XAc
				engines[1]->set_power(XAc);
				var = XAc;
				break;
			case 4:
				//engine back left to XAc
				engines[2]->set_power(XAc);
				var = XAc;
				break;
			case 5:
				//engine back rigth to XAc
				engines[3]->set_power(XAc);
				var = XAc;
				break;
			case 6:
				//C engine front left to XAc
                                Cengines[0]->set_power(XAc);
                                var = XAc;
				break;
			case 7:
				//C engine front rigth to XAc
                                Cengines[1]->set_power(XAc);
                                var = XAc;
				break;
			case 8:
				//C engine back left to XAc
				Cengines[2]->set_power(XAc);
                                var = XAc;
				break;
			case 9:
				//C engine back rigth to XAc
				Cengines[3]->set_power(XAc);
                                var = XAc;
				break;
			case 10:
				//var= Ultra vlu
				var = fUS[0][0]->distance(timeout);
				break;
			case 11:
				//var= Ultra vlm
				var = fUS[0][1]->distance(timeout);
				break;
			case 12:
				//var= Ultra vlo
				var = fUS[0][2]->distance(timeout);
				break;
			case 13:
				//var= Ultra vru
				var = fUS[1][0]->distance(timeout);
				break;
			case 14:
				//var= Ultra vrm
				var = fUS[1][1]->distance(timeout);
				break;
			case 15:
				//var= Ultra vro
				var = fUS[1][2]->distance(timeout);
				break;
			case 16:
				//var= Ultra hlu
				var = bUS[0][0]->distance(timeout);
				break;
			case 17:
				//var= Ultra hlm
				var = bUS[0][1]->distance(timeout);
				break;
			case 18:
				//var= Ultra hlo
				var = bUS[0][2]->distance(timeout);
				break;
			case 19:
				//var= Ultra hru
				var = bUS[1][0]->distance(timeout);
				break;
			case 20:
				//var= Ultra hrm
				var = bUS[1][1]->distance(timeout);
				break;
			case 21:
				//var= Ultra hro
				var = bUS[1][2]->distance(timeout);
				break;
			case 22:
				//var= C vl�
				var=0;
				break;
			case 23:
				//var= C vr�
                                var=0;
				break;
			case 24:
				//var= C hl�
                                var=0;
				break;
			case 25:
				//var= C hr�
                                var=0;
				break;
			case 26:
				//var= RAD vl�
				var = Roti[0]->get_RSteps();
				break;
			case 27:
				//var= Rad vr�
				var = Roti[1]->get_RSteps();
				break;
			case 28:
				//var= Rad hl�
				var = Roti[2]->get_RSteps();
				break;
			case 29:
				//var= Rad hr�
				var = Roti[3]->get_RSteps();
				break;
			default:
				break;
			}
		}
		else{
			//resets all powers if we are not deep enough
			for(int i = 0;i<4;i++){
				engines[i]->set_power(0);
			}
		}
		if (lastDepth != depth || lastPos != pos)//Only prints when values have changed
		{
			print(Texte[depth * 2][evenLine()],Texte[1 + depth * 2][od]+": "+std::to_string(var));
			lastDepth = depth;
			lastPos = pos;
		}
}
/* damit mit main zusammen kompeliert wird habe ich es auskommentiert LG Beke
int main()
{
	manualOverwrite test(0);
	int DLR = 0;
	int DTB = 0;
	int XAc = 0;
	Joystick joystick("/dev/input/js0");
	JoystickEvent events;
	if (!joystick.isFound())
	{
		printf("open failed.\n");
		exit(1);
	}
	while (true) {
		if (joystick.sample(&events)) {
			if (events.isAxis())
			{
				switch (events.number)
				{
				case 4:
					DLR = events.value;
					break;
				case 5:
					DTB = events.value;
					break;
				default:
					break;
				}
			}
		}
		test.renewNavVar(DLR, DTB, XAc);
		test.navigate();
		test.express();
	}
	cin.get();
	return 0;
}*/

