#ifndef InterfaceI2C_H
#define InterfaceI2C_H

#include <wiringPi.h>
#include <mcp23017.h>

class Schnittstelle
{
private:

	int AdresseRotationsArduino = 0x03;
	int ConnectionToken;

	int RegMaxStep = 0;
	int RegStepsLV = 2;//Register Schritte links vorne
	int RegRevsLV = 3;//Register Umdrehungne links vorne
	int RegStepsRV = 4;//...
	int RegRevsRV = 5;
	int RegStepsLH = 6;
	int RegRevsLH = 7;
	int RegStepsRH = 8;
	int RegRevsRH = 9;

	// Variablen für die einzelnen Sensoren; geben die PinNr. an
	int rvUltraschallsensorEcho1 = 300 + 8;
	int rvUltraschallsensorEcho2 = 300 + 9;
	int rvUltraschallsensorEcho3 = 300 + 10;
	int lvUltraschallsensorEcho1 = 300 + 11;
	int lvUltraschallsensorEcho2 = 300 + 12;
	int lvUltraschallsensorEcho3 = 300 + 13;

	int rvUltraschallsensorTrigger1 = 300 + 7;
	int rvUltraschallsensorTrigger2 = 300 + 6;
	int rvUltraschallsensorTrigger3 = 300 + 5;
	int lvUltraschallsensorTrigger1 = 300 + 4;
	int lvUltraschallsensorTrigger2 = 300 + 3;
	int lvUltraschallsensorTrigger3 = 300 + 2;

	//Variablen für die Schalter; geben die PinNr. an
	int Parken = 200 + 8;
	int fahrtModiNormalesFahren = 200 + 9;
	int fahrtModiDrehen = 200 + 10;
	int manuelleSteuerung = 200 + 11;
	int anAus = 200 + 12;

	//Variablen für die Motoren; geben die PinNr. an
	int RadAf = 0;
	int RadAb = 29;

	int RadBf = 3;
	int RadBb = 2;

	int RadCf = 21;
	int RadCb = 22;

	int RadDf = 24;
	int RadDb = 23;

	//Variablen für die Motoren am C-Modul; geben die PinNr.an
	int cRadAf = 25;
	int cRadAb = 1;

	int cRadBf = 6;
	int cRadBb = 26;

	int cRadCf = 27;
	int cRadCb = 28;

	int cRadDf = 4;
	int cRadDb = 5;

	//Notaus
	int pinNotaus = 7;

public:
	void InterfaceSetUp();
	void WerteSchreiben(int pin, int Wert);
	int WerteLesen(int pin);

	void I2C8Write(int token, int Register, int Wert);
	void I2C16Write(int token, int Register, int Wert);
	int I2C8Read(int token, int Register);
	int I2C16Read(int token, int Register);

	int get_AdrRotationsArduino() { return AdresseRotationsArduino; }
	int get_connectionToken() { return ConnectionToken; }

	int get_RegMaxSteps() { return RegMaxStep; }
	int get_RegStepsLV() { return RegStepsLV; }
	int get_RegRevsLV() { return RegRevsLV; }
	int get_RegStepsRV() { return RegStepsRV; }
	int get_RegRevsRV() { return RegRevsRV; }
	int get_RegStepsLH() { return RegStepsLH; }
	int get_RegRevsLH() { return RegRevsLH; }
	int get_RegStepsRH() { return RegStepsRH; }
	int get_RegRevsRH() { return RegRevsRH; }

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

	int get_Parken() { return Parken; }
	int get_fahrtModiNormalesFahren() { return fahrtModiNormalesFahren; }
	int get_fahrtModiDrehen() { return fahrtModiDrehen; }
	int get_manuelleSteuerung() { return manuelleSteuerung; }
	int get_anAus() { return anAus; }

	int get_RadAf() { return RadAf; }
	int get_RadAb() { return RadAb; }
	int get_RadBf() { return RadBf; }
	int get_RadBb() { return RadBb; }
	int get_RadCf() { return RadCf; }
	int get_RadCb() { return RadCb; }
	int get_RadDf() { return RadDf; }
	int get_RadDb() { return RadDb; }

	int get_cRadAf() { return cRadAf; }
	int get_cRadAb() { return cRadAb; }
	int get_cRadBf() { return cRadBf; }
	int get_cRadBb() { return cRadBb; }
	int get_cRadCf() { return cRadCf; }
	int get_cRadCb() { return cRadCb; }
	int get_cRadDf() { return cRadDf; }
	int get_cRadDb() { return cRadDb; }

	int get_pinNotaus() { return pinNotaus; }
};

#endif
