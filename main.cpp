/*
	TODO
	-
	Anmerkungen
	- Fall kurzgeschlossen
	- NOTAUS wieder aktivieren
	- Achse für manuel control gewechselt richtung vieleicht falsch
	- Manul Control gibt jetzt string zurück und schreibt nicht selbst
	Bugfixes
	- String Initiallisierung aus Schaleife rausgenommen da sonst stetige Neudefinition
*/
#include <iostream>  //Grund-Funktionen
#include <math.h>
#include <string.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>
#include <softPwm.h>
#include <chrono>
#include "rotaryencoder/RotationssensorArduino.h" 
#include "Joystick/joystick.hh" //Klassen zur Verarbeitung von Sensordaten
#include "Ultrasonic/libSonar.h"
#include "Schnittstelle/InterfaceI2C.h" // Schnittstelle
#include "Lenkung/Lenkung.h" //Generelle Steuerung
#include "manualControl/manuelControl.h"
#include "switching/switching.h"//zum feststellen der C-Module
#include "C/C.h"//KLasse zur Verwendung der C-Module
#include "engine/engine.h" // Klasse um Daten an Motoren weiter zu geben
#include "Displays/lcm1602.h"//Klasse fuer Displays

// Erstellen einzelen Objekte aus den Klassen

//Schnittstellen
Schnittstelle * pin = new Schnittstelle;

//Joystick
Joystick joystick("/dev/input/js0");
JoystickEvent Event;

//Ultraschallsensoren
Sonar * rvUltraschallsensor1 = new Sonar;
Sonar * rvUltraschallsensor2 = new Sonar;
Sonar * rvUltraschallsensor3 = new Sonar;
Sonar * lvUltraschallsensor1 = new Sonar;
Sonar * lvUltraschallsensor2 = new Sonar;
Sonar * lvUltraschallsensor3 = new Sonar;
/*
Sonar * rhUltraschallsensor1 = new Sonar;
Sonar * rhUltraschallsensor2 = new Sonar;
Sonar * rhUltraschallsensor3 = new Sonar;
Sonar * lhUltraschallsensor1 = new Sonar;
Sonar * lhUltraschallsensor2 = new Sonar;
Sonar * lhUltraschallsensor3 = new Sonar;*/

//Motoren
engine * MotorA = new engine;
engine * MotorB = new engine;
engine * MotorC = new engine;
engine * MotorD = new engine;

//switching Motoren
engine * MotorCA = new engine;
engine * MotorCB = new engine;
engine * MotorCC = new engine;
engine * MotorCD = new engine;

//switching
switching * CDriveA = new switching(& MotorCA);
switching * CDriveB = new switching(& MotorCB);
switching * CDriveC = new switching(& MotorCC);
switching * CDriveD = new switching(& MotorCD);

//Rotationssensoren
Rotationssensor * RotLV = new Rotationssensor(pin->get_RegStepsLV(),pin->get_RegRevsLV(),& pin);
Rotationssensor * RotRV = new Rotationssensor(pin->get_RegStepsRV(),pin->get_RegRevsRV(),& pin);
Rotationssensor * RotLH = new Rotationssensor(pin->get_RegStepsLH(),pin->get_RegRevsLH(),& pin);
Rotationssensor * RotRH = new Rotationssensor(pin->get_RegStepsRH(),pin->get_RegRevsRH(),& pin);

//Lenkung
Lenkung LenkungCDrive;

//Displays
LCM * lcm = new LCM;

//manuelle Lenkung
manualOverwrite mSteuerung(& lcm,& lvUltraschallsensor1,& lvUltraschallsensor2,& lvUltraschallsensor3,& rvUltraschallsensor1,& rvUltraschallsensor2,& rvUltraschallsensor3,/*Nicht existente Sensoren & lhUltraschallsensor1,& lhUltraschallsensor2,& lhUltraschallsensor3,& rhUltraschallsensor1,& rhUltraschallsensor2,& rhUltraschallsensor3,*/& MotorA,& MotorB,& MotorC,& MotorD,& MotorCA,& MotorCB,& MotorCC,& MotorCD,& RotLV,& RotRV,& RotLH,& RotRH);

//Cs
C * Cs = new C(& lvUltraschallsensor1,& lvUltraschallsensor2,& lvUltraschallsensor3,& rvUltraschallsensor1,& rvUltraschallsensor2,& rvUltraschallsensor3,/* Nicht Existente Ultraschallsensoren & lhUltraschallsensor1,& lhUltraschallsensor2,& lhUltraschallsensor3,& rhUltraschallsensor1,& rhUltraschallsensor2,& rhUltraschallsensor3,*/& RotLV,& RotRV,& RotLH,& RotRH, & CDriveA, & CDriveB,& CDriveC,& CDriveD,& MotorA,& MotorB, & MotorC, & MotorD);

//Hey Beeks

//Initiallisieren aller wichtigen Variablen
double Zeiten[4][2] ={{1,1},{1,1},{1,1},{1,1}};
int xAchse = 0;
int yAchse = 0;
int zAchse = 0;
int DLR = 0;
int DTB = 0;
bool cModule = false;
bool NOTAUS = false;
//Checkvalues
bool NOT_AUS = false;
bool POWERONOFF = false;
bool PARKING = false;
bool MANUAL = false;
bool NORMAL = false;
bool DREHEN = false;
bool C_MODUL = false;

//Roundtrip time mesurment variables

std::chrono::time_point<std::chrono::system_clock> AnfangSchleife, EndeSchleife;
unsigned int Roundtrips = 0;
double lastRoundtripTime = 0;
double averageLastRoundtripTime = 0;


using namespace std;

void SetUp()
{
	wiringPiSetup();

	//SetUp-Funktionen der Klassen aufrufen

	//Schnittstelle
	pin->InterfaceSetUp();

	//Ultraschallsensoren
	rvUltraschallsensor1->init(pin->get_rvUltraschallsensorTrigger1(), pin->get_rvUltraschallsensorEcho1(),1);//last int height
	rvUltraschallsensor2->init(pin->get_rvUltraschallsensorTrigger2(), pin->get_rvUltraschallsensorEcho2(),1);
	rvUltraschallsensor3->init(pin->get_rvUltraschallsensorTrigger3(), pin->get_rvUltraschallsensorEcho3(),1,45);//last int mounting angle
	lvUltraschallsensor1->init(pin->get_lvUltraschallsensorTrigger1(), pin->get_lvUltraschallsensorEcho1(),1);
	lvUltraschallsensor2->init(pin->get_lvUltraschallsensorTrigger2(), pin->get_lvUltraschallsensorEcho2(),1);
	lvUltraschallsensor3->init(pin->get_lvUltraschallsensorTrigger3(), pin->get_lvUltraschallsensorEcho3(),1,45);
	/*
	rhUltraschallsensor1->init(pin->get_rhUltraschallsensorTrigger1(), pin->get_rhUltraschallsensorEcho1(),1);
	rhUltraschallsensor2->init(pin->get_rhUltraschallsensorTrigger2(), pin->get_rhUltraschallsensorEcho2(),1);
	rhUltraschallsensor3->init(pin->get_rhUltraschallsensorTrigger3(), pin->get_rhUltraschallsensorEcho3(),1,45);
	lhUltraschallsensor1->init(pin->get_lhUltraschallsensorTrigger1(), pin->get_lhUltraschallsensorEcho1(),1);
	lhUltraschallsensor2->init(pin->get_lhUltraschallsensorTrigger2(), pin->get_lhUltraschallsensorEcho2(),1);
	lhUltraschallsensor3->init(pin->get_lhUltraschallsensorTrigger3(), pin->get_lhUltraschallsensorEcho3(),1,45);*/

	//Motoren
	MotorA->initialisEngine(pin->get_RadAf(), pin->get_RadAb());
	MotorB->initialisEngine(pin->get_RadBf(), pin->get_RadBb());
	MotorC->initialisEngine(pin->get_RadCf(), pin->get_RadCb());
	MotorD->initialisEngine(pin->get_RadDf(), pin->get_RadDb());
	//C-Motoren
	MotorCA->initialisEngine(pin->get_cRadAf(), pin->get_cRadAb());
	MotorCB->initialisEngine(pin->get_cRadBf(), pin->get_cRadBb());
	MotorCC->initialisEngine(pin->get_cRadCf(), pin->get_cRadCb());
	MotorCD->initialisEngine(pin->get_cRadDf(), pin->get_cRadDb());

	//switching
	CDriveA->SetUp(Zeiten[0][0],Zeiten[0][1]);
	CDriveB->SetUp(Zeiten[1][0],Zeiten[1][1]);
	CDriveD->SetUp(Zeiten[2][0],Zeiten[2][1]);
	CDriveC->SetUp(Zeiten[3][0],Zeiten[3][1]);

	//"Output" auf Display
	lcm->clear();

	lcm->write(1, 0, "SetUp fertig!");
	lcm->write(2, 1, "Gute Fahrt!");

	delay(3000);

	lcm->clear();
}


void JoystickWerte()
{
	if (joystick.sample(&Event))
	{
		if(Event.isAxis())//Auslesen des Joysticks f�rs normale Fahren,Driften und Drehen
		{
			switch (Event.number)
			{
				case 0:
					xAchse = Event.value / 327;
					break;

				case 1:
					yAchse = Event.value / 327;
					break;

				case 2:
					zAchse = Event.value / 327;
					break;

				case 4:
					DLR = Event.value;
					break;

				case 5:
					DTB = Event.value;
					break;
			}
		}

		if(Event.isButton())//Warten auf das Signal zu hochfahren �ber die C-Module
		{
			if(Event.number == 3 && Event.value == 1)
			{
				cModule = true;
			}
			else
			{
				cModule = false;
			}

			if(Event.number == 0)
			{
				Cs->set_end();
			}

			if(Event.number == 1)
			{
				Cs->set_pause();
			}
		}
	}
}

void ReadPins()
{// Wenn etwas aktiev seien soll ist der status der bool true
	NOT_AUS			= !pin->WerteLesen(pin->get_pinNotaus());//Bei Null alles aus
	POWERONOFF 		= pin->WerteLesen(pin->get_anAus());//wenn eins dann laufen 0 => aus
	PARKING			= pin->WerteLesen(pin->get_Parken());//wenn eins dann parken
	MANUAL			= pin->WerteLesen(pin->get_manuelleSteuerung());//Wenn 1 dann manuelle Steuerung
	NORMAL			= pin->WerteLesen(pin->get_fahrtModiNormalesFahren());//Wenn 1 dann normales fahren
	DREHEN			= pin->WerteLesen(pin->get_fahrtModiDrehen());//wenn 1 dann drehen
	C_MODUL			= cModule;
}

int KontrolleEingabe() //soll unlogische Eingaben verhindern; viele Probleme werden durch die fall zuweisung verhindert/Aufbau der Schalter
{
	if (!PARKING && MANUAL)//Nicht parken + manuelle Steuerung an
	{
		return 1;
	}

	if (!PARKING && !POWERONOFF)//Ausschalten ohne das man voher parkt
	{
		return 1;
	}

	if (PARKING && cModule == true)//Parken und Hochfahren wollen
	{
		return 1;
	}

	if (MANUAL && cModule == true)//manuelle Steuerung + Hochfahren wollen
	{
		return 1;
	}

	return 0;
}

int fall()
{
	
	if (NOT_AUS)//Bei NOTAUS Abbruch
	{
		NOTAUS = true;
		return 6;
	}

	if ((cModule == true && !PARKING && !MANUAL) || Cs->getOnlineStat())//fährt hoch, startet nut wenn weidersprüchliche Bedingungen nicht vorliegen
	{
		return 4;
	}

	if (KontrolleEingabe() == 1)//sucht wiedersprüche
	{
		return 7;
	}

	if (PARKING)//wenn Parken dann
	{

		if (MANUAL)
		{
			return 5;
		}

		return 0;
	}
	else
	{
		if (NORMAL)
		{
			return 1;
		}

		if (DREHEN)
		{
			return 3;
		}

		return 2;
	}
}


int main()
{
	SetUp();

	if (joystick.isFound() == false)
	{
		lcm->write(1, 0, "Kein Joystick!");
		lcm->write(2, 1, "Keine Fahrt");

		delay(5000);

		lcm->clear();

		return 0;
	}

	//Variablen fuer Ausgabe auf Display
	string out1;
	string out2;
	string out1Alt;
	string out2Alt;

	while(true)
	{
		//Roundtrip Zeiten Messen// An Teil am Ende der Schleife denken
		AnfangSchleife = std::chrono::system_clock::now();
		// Aktualisierung der Joystick Daten
		JoystickWerte();
		ReadPins();
		//Zuweisung welcher Typ von Fortbewegung gerade "zust�ndig" ist
		switch(fall())
		{
			case 0:
				LenkungCDrive.parken();

				out1 = "Fahrtmodus:";
				out2 = "Parken";

				break;

			case 1:
				LenkungCDrive.normaleLenkung(xAchse, yAchse);

				out1 = "Fahrtmodus:";
				out2 = "normales Fahren";

				break;

			case 2:
				LenkungCDrive.driften(xAchse, yAchse);

				out1 = "Fahrtmodus:";
				out2 = "Driften";

				break;

			case 3:
				LenkungCDrive.drehen(xAchse);

				out1 = "Fahrtmodus:";
				out2 = "Drehen";

				break;

			case 4:
				Cs->UP();

				out1 = "Fahrtmodus:";
				out2 = "Hochfahren";

				break;

			case 5://Muss string zurückgeben anstatt direkt zu schreiben
				mSteuerung.renewNavVar(DLR, DTB, yAchse);//gives the controlvalues to the class
				mSteuerung.navigate();//takes care that your navigation is leagel
				mSteuerung.express();//matches the matching string to the navigation

				out1 = mSteuerung.LineOne();//outputs the String to the main interface for the Display
				out2 = mSteuerung.LineTwo();

				break;
			case 7:
				LenkungCDrive.parken();

				out1 = "Auswahl";
				out2 = "kontrollieren";

				break;

			default:
				break;
		}

		//Ausgabe auf Display
		if (out1.compare(out1Alt))
		{
			lcm->clear();

			lcm->write(0, 0, out1);
			lcm->write(0, 1, out2);

			out1Alt = out1;
		}

		if (out2.compare(out2Alt))
		{
			lcm->clear();

			lcm->write(0, 0, out1);
			lcm->write(0, 1, out2);

			out2Alt = out2;
		}

		//Variable Abbruvh Leistung
		double Abbruch = 3;

		//Zuweisung der Leistungen den Motoren
		switch (fall())
		{
			case 0: //fallen alle auf case 3 da die Leistungen durch die Lenkung bestimmt werden um auch langsam zu bremsen ...
			case 1:
			case 2:
			case 3:
				//Leistung auf Motor A
				if (LenkungCDrive.get_leistungRadA()>Abbruch||LenkungCDrive.get_leistungRadA()<-Abbruch)
				{
					MotorA->set_power(LenkungCDrive.get_leistungRadA());
				}
				else
				{
					MotorA->set_power(0);
				}

				//Leistung auf Motor B
				if (LenkungCDrive.get_leistungRadB()>Abbruch||LenkungCDrive.get_leistungRadB()<-Abbruch)
				{
					MotorB->set_power(LenkungCDrive.get_leistungRadB());
				}
				else
				{
					MotorB->set_power(0);
				}

				//Leistung auf Motor C
				if (LenkungCDrive.get_leistungRadC()>Abbruch||LenkungCDrive.get_leistungRadC()<-Abbruch)
				{
					MotorC->set_power(LenkungCDrive.get_leistungRadC());
				}
				else
				{
					MotorC->set_power(0);
				}

				//Leistung auf Motor D
				if (LenkungCDrive.get_leistungRadD()> Abbruch||LenkungCDrive.get_leistungRadD()< -Abbruch)
				{
					MotorD->set_power(LenkungCDrive.get_leistungRadD());
				}
				else
				{
					MotorD->set_power(0);
				}

				break;

			case 6:
				MotorA->set_power(0);
				MotorB->set_power(0);
				MotorC->set_power(0);
				MotorD->set_power(0);

				MotorCA->set_power(0);
				MotorCB->set_power(0);
				MotorCC->set_power(0);
				MotorCD->set_power(0);

			default:
				break;
		}

		//Ausgabe auf Bildschirm
		std::cout << "Joystick X: " << xAchse << "  , Y:  " << -yAchse << std::endl;
		//std::cout << "Lenkungsvektor 1: " <<LenkungCDrive.get_vektor1() << "   , 2:  " << LenkungCDrive.get_vektor2() << std::endl;
		std::cout << "Motor A: " << MotorA->get_power() << "Motor B : " << MotorA->get_power() << "Motor C : " << MotorC->get_power() << " Motor D : " << MotorD->get_power() << std::endl;
		std::cout << "Modi: " << fall() <<"  "<< out2 << std::endl;

		//Abbruchfunktion
//		if (NOTAUS == true || !stat[POWERONOFF] && KontrolleEingabe() == 0)
//		{
//			break;
//		}
		//Roundtrip ende
		
		EndeSchleife = std::chrono::system_clock::now();
		std::chrono::duration<double> elapsed_time = EndeSchleife - AnfangSchleife;
		lastRoundtripTime = elapsed_time.count();
		Roundtrips++;
		averageLastRoundtripTime = (averageLastRoundtripTime * (Roundtrips-1) + lastRoundtripTime)/Roundtrips;
		std::cout << "Average roundtrip: "<< averageLastRoundtripTime<< " s" << endl;
		
	}

	if (!POWERONOFF)//Endkommentar //Wenn durch Aus aus Nachricht anzeigen
	{
		lcm->clear();
		lcm->write(0, 0, "Auf Wiedersehen");

		delay(1000);

		lcm->write(1, 1, "Herunterfahren");

		delay(3000);

		lcm->clear();
	}

	//system("sudo shutdown -h now"); //zum heruterfahren des Pis

	return 0;
}
