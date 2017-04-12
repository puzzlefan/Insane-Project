// manuelControl.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
//#include <initializer_list>
#include "joystick.hh"
#include <string>
#include "manuelControl.h"



using namespace std;
//constructor
manualOverwrite::manualOverwrite(int displayAdresse)
{
	DisAdr = displayAdresse;
}
//private Functions
void manualOverwrite::print(std::string toPrint) {
	cout << toPrint << endl << flush;
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
	if (lastDepth != depth || lastPos != pos)//Only prints when values have changed
	{
		int od = odLine();
		int var = 0;//holds the outpuvalue if needed
		switch (od)
		{
		case 0:
			//engines front to XAc
			break;
		case 1:
			//engines back to XAc
			break;
		case 2:
			//engine front left to XAc
			break;
		case 3:
			//engine front rigth to XAc
			break;
		case 4:
			//engine back left to XAc
			break;
		case 5:
			//engine back rigth to XAc
			break;
		case 6:
			//C engine front left to XAc
			break;
		case 7:
			//C engine front rigth to XAc
			break;
		case 8:
			//C engine back left to XAc
			break;
		case 9:
			//C engine back rigth to XAc
			break;
		case 10:
			//var= Ultra vlu
			break;
		case 11:
			//var= Ultra vlm
			break;
		case 12:
			//var= Ultra vlo
			break;
		case 13:
			//var= Ultra vru
			break;
		case 14:
			//var= Ultra vrm
			break;
		case 15:
			//var= Ultra vro
			break;
		case 16:
			//var= Ultra hlu
			break;
		case 17:
			//var= Ultra hlm
			break;
		case 18:
			//var= Ultra hlo
			break;
		case 19:
			//var= Ultra hru
			break;
		case 20:
			//var= Ultra hrm
			break;
		case 21:
			//var= Ultra hro
			break;
		case 22:
			//var= C vl°
			break;
		case 23:
			//var= C vr°
			break;
		case 24:
			//var= C hl°
			break;
		case 25:
			//var= C hr°
			break;
		case 26:
			//var= RAD vl°
			break;
		case 27:
			//var= Rad vr°
			break;
		case 28:
			//var= Rad hl°
			break;
		case 29:
			//var= Rad hr°
			break;
		default:
			break;
		}
		print(Texte[depth * 2][evenLine()]);
		print(Texte[1 + depth * 2][od]);
		lastDepth = depth;
		lastPos = pos;
	}
}

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
}

