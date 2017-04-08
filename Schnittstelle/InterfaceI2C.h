#pragma once
#ifndef InterfaceI2C_H
#define InterfaceI2C_H

#include <wiringPi.h>
#include <mcp23017.h>

class Schnittstelle 
{
private:
	
	// Variablen für die einzelnen Sensoren...
	int rvUltraschallsensorEcho1 = 100 + 8;
	int rvUltraschallsensorEcho2 = 100 + 9;
	int rvUltraschallsensorEcho3 = 100 + 10;
	int lvUltraschallsensorEcho1 = 100 + 11;
	int lvUltraschallsensorEcho2 = 100 + 12;
	int lvUltraschallsensorEcho3 = 100 + 13;

	int rvUltraschallsensorTrigger1 = 100 + 7;
	int rvUltraschallsensorTrigger2 = 100 + 6;
	int rvUltraschallsensorTrigger3 = 100 + 5;
	int lvUltraschallsensorTrigger1 = 100 + 4;
	int lvUltraschallsensorTrigger2 = 100 + 3;
	int lvUltraschallsensorTrigger3 = 100 + 2;

	int rhUltraschallsensorEcho1 = 300 + 8;
	int rhUltraschallsensorEcho2 = 300 + 9;
	int rhUltraschallsensorEcho3 = 300 + 10;
	int lhUltraschallsensorEcho1 = 300 + 11;
	int lhUltraschallsensorEcho2 = 300 + 12;
	int lhUltraschallsensorEcho3 = 300 + 13;

	int rhUltraschallsensorTrigger1 = 300 + 7;
	int rhUltraschallsensorTrigger2 = 300 + 6;
	int rhUltraschallsensorTrigger3 = 300 + 5;
	int lhUltraschallsensorTrigger1 = 300 + 4;
	int lhUltraschallsensorTrigger2 = 300 + 3;
	int lhUltraschallsensorTrigger3 = 300 + 2;

	//Variablen für die Schalter
	int Parken = 200 + 8;
	int fahrtModiNormalesFahren = 200 + 9;
	int fahrtModiDrehen = 200 + 10;

public:
	void InterfaceSetUp();
	void WerteSchreiben(int pin, int Wert);
	int WerteLesen(int pin);
		
	int get_rvUltraschallsensorEcho1() { return rvUltraschallsensorEcho1; }
	int get_rvUltraschallsensorEcho2() { return rvUltraschallsensorEcho2; }
	int get_rvUltraschallsensorEcho3() { return rvUltraschallsensorEcho3; }
	int get_lvUltraschallsensorEcho1() { return lvUltraschallsensorEcho1; }
	int get_lvUltraschallsensorEcho2() { return lvUltraschallsensorEcho2; }
	int get_lvUltraschallsensorEcho3() { return lvUltraschallsensorEcho3; }
	
	int get_rvUltraschallsensorTrigger1() { return rvUltraschallsensorTrigger1; }
	int get_rvUltraschallsensorTrigger2() { return rvUltraschallsensorTrigger2; }
	int get_rvUltraschallsensorTrigger3() { return rvUltraschallsensorTrigger3; }
	int get_lvUltraschallsensorTrigger1() { return lvUltraschallsensorTrigger1; }
	int get_lvUltraschallsensorTrigger2() { return lvUltraschallsensorTrigger2; }
	int get_lvUltraschallsensorTrigger3() { return lvUltraschallsensorTrigger3; }

	int get_rhUltraschallsensorEcho1() { return rhUltraschallsensorEcho1; }
	int get_rhUltraschallsensorEcho2() { return rhUltraschallsensorEcho2; }
	int get_rhUltraschallsensorEcho3() { return rhUltraschallsensorEcho3; }
	int get_lhUltraschallsensorEcho1() { return lhUltraschallsensorEcho1; }
	int get_lhUltraschallsensorEcho2() { return lhUltraschallsensorEcho2; }
	int get_lhUltraschallsensorEcho3() { return lhUltraschallsensorEcho3; }

	int get_rhUltraschallsensorTrigger1() { return rhUltraschallsensorTrigger1; }
	int get_rhUltraschallsensorTrigger2() { return rhUltraschallsensorTrigger2; }
	int get_rhUltraschallsensorTrigger3() { return rhUltraschallsensorTrigger3; }
	int get_lhUltraschallsensorTrigger1() { return lhUltraschallsensorTrigger1; }
	int get_lhUltraschallsensorTrigger2() { return lhUltraschallsensorTrigger2; }
	int get_lhUltraschallsensorTrigger3() { return lhUltraschallsensorTrigger3; }

	int get_Parken() { return Parken; }
	int get_fahrtModiNormalesFahren() { return fahrtModiNormalesFahren; }
	int get_fahrtModiDrehen() { return fahrtModiDrehen; }
};

#endif
