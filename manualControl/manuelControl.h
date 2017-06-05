#include "../engine/engine.h"
#include "../Ultrasonic/libSonar.h"
#include "../Displays/lcm1602.h"
#include "../rotaryencoder/RotationssensorArduino.h"

class manualOverwrite
{
private:
	//ouput specific variable
	engine *  engines[4];
	engine * Cengines[4];
	Sonar * fUS[2][3];
//	Sonar * bUS[2][3];
	Rotationssensor * Roti[4];
	LCM * lcm;
	const int timeout = 3000;//timout for Ultrasonic sensors
	//Integers to navigate
	int DLR = 0;//dpad left right axis
	int DTB = 0;//dpad top bottom axis
	int YAc = 0;//X achse

	//Navigation vars
	int depth = 0;//indicates the depth in the in the menu for every confiramtion of a menu point you get one level deeper and vice versa
	const int minDepth = 0;//marked the minimal depth
	static const int maxDepth = 2;//marks the macimal depth

	int pos = 0;//indicates the position in the actual menu of the given depth
	const int minPos = 0;//marks the minimal position
	const int maxPos[5][maxDepth + 1] = { { 4,1,0 },{ 4,3,0 },{ 4,3,0 },{ 4,1,5 },{ 4,1,3 } };//gives the max values for a position at a certain underpoint depth = 0 length top array, depth 1 = [chosenPosition][0], depth 2 = [chosenPosition][0]

	int chosenPoth[maxDepth + 1] = { 0,0,0 };//holds the values which have been chosen before
	int lastPosNavi[3] = { 0,0,0 };//keeps track of the last recogniest position of each navigator first position left to rigth axis D-pad, second position top to bottom axis D-pad, third value of the thrust controller
	int lastDepth = -1;
	int lastPos = -1;

	//text to display
	std::string Zeile1[1] = { "Manuelle Steuerung" };
	std::string Zeile2[5] = { "Raeder Paar", "Einzelnes Rad", "Einzelner C motor","Ultraschallsensor Check","Rotatationssensor Check" };
	std::string Zeile3[5] = { "Raeder Paar", "Einzelnes Rad", "Einzelner C motor","Ultraschallsensor Check","Rotatationssensor Check" };
	std::string Zeile4[14] = { "Vorne","Hinten","Vorne Links","Vorne Rechts","Hinten Links","Hinten Rechts","Vorne Links","Vorne Rechts","Hinten Links","Hinten Rechts","Ultraschall vorne","Ultraschall hinten","Rotation Cs","Rotation Rad" };
	std::string Zeile5[14] = { "Raederpaar Vorne","Raederpaar Hinten","Einzelrad Vorne Links","Einzelrad Vorne Rechts","Einzelrad Hinten Links","Einzelrad Hinten Rechts","Einzel C Motor Vorne Links","Einzel C Motor Vorne Rechts","Einzel C Motor Hinten Links","Einzel C Motor Hinten Rechts","Ultraschall vorne","Ultraschall hinten","Rotation Cs","Rotation Rad" };
	std::string Zeile6[30] = { "Leistung: ", "Leistung: ","Leistung: ", "Leistung: ","Leistung: ", "Leistung: ","Leistung: ", "Leistung: ","Leistung: ", "Leistung: ", "vlu:  m",	"vlm:  m","vlo:  m","vru:  m","vrm:  m","vro:  m","hlu:  m","hlim:  m","hlo:  m","hru:  m","hrm:  m","hro:  m","C vl:  ","C vr:  ","hl:  ","C hr:  ","Rad vl:  ","Rad vr:  ","Rad hl:  ","Rad hr:  " };

	std::string * Texte[6] = { &Zeile1[0],&Zeile2[0],&Zeile3[0],&Zeile4[0],&Zeile5[0],&Zeile6[0] };

	std::string output[2];

	//functions
	int evenLine();//Determines which String to print if we have an even line
	int odLine();//same for the od lines, becaues of a changed data structure
	void print(std::string toPrint, std::string toPrintTwo);//outputs the Strings to te Displays
public:
	manualOverwrite(LCM ** lcm,
			Sonar ** flb, Sonar ** flm, Sonar ** flt, Sonar ** frb, Sonar ** frm, Sonar ** frt,
			/*Sonar ** blb, Sonar ** blm, Sonar ** blt, Sonar ** brb, Sonar ** brm, Sonar ** brt,*/
			engine ** rvl, engine ** rvr, engine ** rbl, engine ** rbr,
			engine ** cvl, engine ** cvr, engine ** cbl, engine ** cbr ,
			Rotationssensor ** rotLV, Rotationssensor ** rotRV, Rotationssensor ** rotLH, Rotationssensor ** rotRH);//sets the class up, tells which adress rto use for the Display
	void renewNavVar(int DLR, int DST, int YAc);//takes the new values for the navigation
	void navigate();//works with the data gatherd by renewNavVar and defines the position where you are
	void express();//takes the position ant prints the appropriare text and is responsable to deliver the gatherd values to the egines or to gather the data from a sensor

	std::string LineOne(){return output[0];}
	std::string LineTwo(){return output[1];}
};
