#include <iostream>  //Grund-Funktionen
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>
#include <softPwm.h>
#include "rotaryencoder/RotationssensorArduino.h"
#include "Joystick/joystick.hh" //Klassen zur Verarbeitung von Sensordaten
#include "Ultrasonic/libSonar.h"
#include "Schnittstelle/InterfaceI2C.h" // Schnittstelle
#include "Lenkung/Lenkung.h" //Generelle Steuerung
#include "manualControl/manuelControl.h"
#include "switchig/switching.h"//zum feststellen der C-Module
#include "engine/engine.h" // Klasse um Daten an Motoren weiter zu geben
#include "Displays/lcm1602.h"//Klasse fuer Displays
#include "C/C.h"


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
manualOverwrite mSteuerung(& lcm,& lvUltraschallsensor1,& lvUltraschallsensor2,& lvUltraschallsensor3,& rvUltraschallsensor1,& rvUltraschallsensor2,& rvUltraschallsensor3,& lhUltraschallsensor1,& lhUltraschallsensor2,& lhUltraschallsensor3,& rhUltraschallsensor1,& rhUltraschallsensor2,& rhUltraschallsensor3,& MotorA,& MotorB,& MotorC,& MotorD,& MotorCA,& MotorCB,& MotorCC,& MotorCD,& RotLV,& RotRV,& RotLH,& RotRH);
//Cs
C * Cs = new C(& lvUltraschallsensor1,& lvUltraschallsensor2,& lvUltraschallsensor3,& rvUltraschallsensor1,& rvUltraschallsensor2,& rvUltraschallsensor3,& lhUltraschallsensor1,& lhUltraschallsensor2,& lhUltraschallsensor3,& rhUltraschallsensor1,& rhUltraschallsensor2,& rhUltraschallsensor3,& RotLV,& RotRV,& RotLH,& RotRH, & CDriveA, & CDriveB,& CDriveC,& CDriveD,& MotorA,& MotorB, & MotorC, & MotorD);

//Initiallisieren aller wichtigen Variablen
int xAchse = 0;
int yAchse = 0;
int zAchse = 0;
int DLR = 0;
int DTB = 0;
bool cModule = false;
bool NOTAUS = false;


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

	//"Output" auf Display
	lcm->write(1, 0, "SetUp fertig!");
	lcm->write(2, 1, "Gute Fahrt!");

	delay(3000);
	
	lcm->clear();
}


void JoystickWerte()
{
	if (joystick.sample(&Event)
	{
		if(Event.isAxis())//Auslesen des Joysticks fürs normale Fahren,Driften und Drehen
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

		if(Event.isButton())//oder Timons Variable //Warten auf das Signal zu hochfahren über die C-Module
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

int KontrolleEingabe() //soll unlogische Eingaben verhindern; viele Probleme werden durch die fall zuweisung verhindert/Aufbau der Schalter
{
	if (pin->WerteLesen(pin->get_Parken()) == 0 && pin->WerteLesen(pin->get_manuelleSteuerung()) == 1)//Nicht parken + manuelle Steuerung an
	{
		return 1;
	}

	if (pin->WerteLesen(pin->get_Parken()) == 0 && pin->WerteLesen(pin->get_anAus()) == 0)//Ausschalten ohne das man voher parkt
	{
		return 1;
	}

	if (pin->WerteLesen(pin->get_Parken()) == 1 && cModule == true)//Parken und Hochfahren wollen
	{
		return 1;
	}

	if (pin->WerteLesen(pin->get_manuelleSteuerung()) == 1 && cModule == true)//manuelle Steuerung + Hochfahren wollen
	{
		return 1;
	}

	return 0;
}

int fall()
{
	if (pin->WerteLesen(pin->get_pinNotaus()) == 0)
	{
		NOTAUS = true;
		return 6;
	}

	if ((cModule == true && pin->WerteLesen(pin->get_Parken()) == 0 && pin->WerteLesen(pin->get_manuelleSteuerung()) == 0) || Cs->getOnlineStat())
	{
		return 4;
	}

	if (KontrolleEingabe() == 1)
	{
		return 7;
	}

	if (pin->WerteLesen(pin->get_Parken()) == 1)
	{

		if (pin->WerteLesen(pin->get_manuelleSteuerung()) == 1)
		{
			return 5;
		}

		return 0;
	}
	else
	{
		if (pin->WerteLesen(pin->get_fahrtModiNormalesFahren()) == 1) 
		{
			return 1;
		}

		if (pin->WerteLesen(pin->get_fahrtModiDrehen()) == 1) 
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

	while(true)
	{
		// Aktualisierung der Joystick Daten
		JoystickWerte();

		//Zuweisung welcher Typ von Fortbewegung gerade "zuständig" ist
		switch(fall())
		{
			case 0:
				LenkungCDrive.parken();
				
				lcm->clear();

				lcm->write(0, 0, "Fahrtmodus:");
				lcm->write(5, 1, "Parken");
				
				break;
		
			case 1:
				LenkungCDrive.normaleLenkung(xAchse, yAchse);
				
				lcm->clear();

				lcm->write(0, 0, "Fahrtmodus:");
				lcm->write(4, 1, "normales Fahren");
				
				break;

			case 2:
				LenkungCDrive.driften(xAchse, yAchse);
				
				lcm->clear();
				
				lcm->write(0, 0, "Fahrtmodus:");
				lcm->write(4, 1, "Driften");
				
				break;

			case 3:
				LenkungCDrive.drehen(zAchse);
				
				lcm->clear();

				lcm->write(0, 0, "Fahrtmodus:");
				lcm->write(5, 1, "Drehen");
				
				break;
			
			case 4:
				Cs->UP();

				lcm->clear();

				lcm->write(0, 0, "Fahrtmodus:");
				lcm->write(3, 1, "Hochfahren");

				break;
			
			case 5:
				mSteuerung.renewNavVar(DLR, DTB, xAchse);
				mSteuerung.navigate();
				mSteuerung.express();

				lcm->clear();

				break;

			case 7:
				LenkungCDrive.parken();

				lcm->clear();

				lcm->write(0, 0, "Auswahl");
				lcm->write(1, 1, "kontrollieren");

				break;

			default:
				break;
		}

		//Zuweisung der Leistungen den Motoren
		switch (fall())
		{
			case 0:
			case 1:
			case 2:
			case 3:
				MotorA->set_power(LenkungCDrive.get_leistungRadA());
				MotorB->set_power(LenkungCDrive.get_leistungRadB());
				MotorC->set_power(LenkungCDrive.get_leistungRadC());
				MotorD->set_power(LenkungCDrive.get_leistungRadD());
				
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

		std::cout << xAchse << "  ,  " << -yAchse << std::endl;
		std::cout << LenkungCDrive.get_vektor1() << "   ,   " << LenkungCDrive.get_vektor2() << std::endl;

		//Abbruchfunktion
		if (NOTAUS == true || pin->WerteLesen(pin->get_anAus()) == 1)
		{
			break;
		}

		//delay(75);
	}

	if (pin->WerteLesen(pin->get_anAus()) == 1)//Endkommentar
	{
		lcm->clear();
		lcm->write(0, 0, "Auf Wiedersehen");

		delay(1000);

		lcm->write(1, 1, "Herunterfahren");

		delay(3000);

		lcm->clear();
	}

	system("sudo shutdown -h now"); //zum heruterfahren des Pis

	return 0;
}