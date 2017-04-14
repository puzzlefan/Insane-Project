#include <iostream>  //Grund-Funktionen
#include <math.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <mcp23017.h>
#include <softPwm.h>
#include <joystick.hh> //Klassen zur Verarbeitung von Sensordaten
//#include <Rotationssensor.h>
#include <libSonar.h>
#include <InterfaceI2C.h> // Schnittstelle
#include <Lenkung.h> //Generelle Steuerung
#include <manuelControl.h>
#include <switching.h>//zum feststellen der C-Module
#include <engine.h> // Klasse um Daten an Motoren weiter zu geben
#include <lcm1602.h>//Klasse für Displays

// Erstellen einzelen Objekte aus den Klassen
  
//Schnittstellen
Schnittstelle pin; 

//Joystick
Joystick joystick("/dev/input/js0");
JoystickEvent Event;

//Ultraschallsensoren
Sonar rvUltraschallsensor1;
Sonar rvUltraschallsensor2;
Sonar rvUltraschallsensor3;
Sonar lvUltraschallsensor1;
Sonar lvUltraschallsensor2;
Sonar lvUltraschallsensor3;

Sonar rhUltraschallsensor1;
Sonar rhUltraschallsensor2;
Sonar rhUltraschallsensor3;
Sonar lhUltraschallsensor1;
Sonar lhUltraschallsensor2;
Sonar lhUltraschallsensor3;

//Motoren
engine MotorA;
engine MotorB;
engine MotorC;
engine MotorD;
engine MotorCDriveA;
engine MotorCDriveB;
engine MotorCDriveC;
engine MotorCDriveD;

//Lenkung
Lenkung LenkungCDrive;

//Displays
LCM lcm;

//Initiallisieren aller wichtigen Variablen
int xAchse = 0;
int yAchse = 0;
int zAchse = 0;
bool cModule = false;


void SetUp()
{
	wiringPiSetup();

	//SetUp-Funktionen der Klassen aufrufen

	//Schnittstelle
	pin.InterfaceSetUp();

	//Ultraschallsensoren
	rvUltraschallsensor1.init(pin.get_rvUltraschallsensorTrigger1(), pin.get_rvUltraschallsensorEcho1());
	rvUltraschallsensor2.init(pin.get_rvUltraschallsensorTrigger2(), pin.get_rvUltraschallsensorEcho2());
	rvUltraschallsensor3.init(pin.get_rvUltraschallsensorTrigger3(), pin.get_rvUltraschallsensorEcho3());
	lvUltraschallsensor1.init(pin.get_lvUltraschallsensorTrigger1(), pin.get_lvUltraschallsensorEcho1());
	lvUltraschallsensor2.init(pin.get_lvUltraschallsensorTrigger2(), pin.get_lvUltraschallsensorEcho2());
	lvUltraschallsensor3.init(pin.get_lvUltraschallsensorTrigger3(), pin.get_lvUltraschallsensorEcho3());

	rhUltraschallsensor1.init(pin.get_rhUltraschallsensorTrigger1(), pin.get_rhUltraschallsensorEcho1());
	rhUltraschallsensor2.init(pin.get_rhUltraschallsensorTrigger2(), pin.get_rhUltraschallsensorEcho2());
	rhUltraschallsensor3.init(pin.get_rhUltraschallsensorTrigger3(), pin.get_rhUltraschallsensorEcho3());
	lhUltraschallsensor1.init(pin.get_lhUltraschallsensorTrigger1(), pin.get_lhUltraschallsensorEcho1());
	lhUltraschallsensor2.init(pin.get_lhUltraschallsensorTrigger2(), pin.get_lhUltraschallsensorEcho2());
	lhUltraschallsensor3.init(pin.get_lhUltraschallsensorTrigger3(), pin.get_lhUltraschallsensorEcho3());

	//Motoren
	MotorA.initialisEngine(pin.get_RadAf(), pin.get_RadAb());
	MotorB.initialisEngine(pin.get_RadBf(), pin.get_RadBb());
	MotorC.initialisEngine(pin.get_RadCf(), pin.get_RadCb());
	MotorD.initialisEngine(pin.get_RadDf(), pin.get_RadDb());
	MotorCDriveA.initialisEngine(pin.get_cRadAf(), pin.get_cRadAb());
	MotorCDriveB.initialisEngine(pin.get_cRadBf(), pin.get_cRadBb());
	MotorCDriveC.initialisEngine(pin.get_cRadCf(), pin.get_cRadCb());
	MotorCDriveD.initialisEngine(pin.get_cRadDf(), pin.get_cRadDb());

	//"Output" auf Display
	lcm.write(1, 0, "SetUp fertig!");
	lcm.write(2, 1, "Gute Fahrt!");

	delay(3000);
	
	lcm.clear();
}


void JoystickWerte()
{
	if (joystick.sample(&Event) && Event.isAxis())//Auslesen des Joysticks fürs normale Fahren,Driften und Drehen
	{
		if (Event.number == 0)
		{
			xAchse = Event.value / 327;
		}

		if (Event.number == 1)
		{
			yAchse = Event.value / 327;
		}

		if (Event.number == 2)
		{
			zAchse = Event.value / 327;
		}
	}

	if(joystick.sample(&Event)&&Event.isButton())//oder Timons Variable //Warten auf das Signal zu hochfahren über die C-Module
	{
		if(Event.number == 3)
		{
			cModule = true;
		}
	}
	else
	{
		cModule = false;
	}
}


int fall()
{
	if (pin.WerteLesen(pin.get_Parken()) == 1)
	{
		return 0;
	}
	else
	{
		if (pin.WerteLesen(pin.get_fahrtModiNormalesFahren()) == 1) 
		{
			return 1;
		}

		if (pin.WerteLesen(pin.get_fahrtModiDrehen()) == 1) 
		{
			return 3;
		}
		
		if (cModule = true) 
		{
			return 4;
		}

		if (pin.WerteLesen(pin.get_manuelleSteuerung()) == 1)
		{
			return 5;
		}

		return 2;
	}
}


int main()
{
	SetUp();

	if (joystick.isFound() == false)
	{
		lcm.write(1, 0, "Kein Joystick!");
		lcm.write(2, 1, "Keine Fahrt");
		
		delay(5000);
		
		lcm.clear();
		
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
				
				lcm.clear();

				lcm.write(0, 0, "Fahrtmodus:");
				lcm.write(5, 1, "Parken");
				
				break;
		
			case 1:
				LenkungCDrive.normaleLenkung(xAchse, yAchse);
				
				lcm.clear();

				lcm.write(0, 0, "Fahrtmodus:");
				lcm.write(4, 1, "normales Fahren");
				
				break;

			case 2:
				LenkungCDrive.driften(xAchse, yAchse);
				
				lcm.clear();
				
				lcm.write(0, 0, "Fahrtmodus:");
				lcm.write(4, 1, "Driften");
				
				break;

			case 3:
				LenkungCDrive.drehen(zAchse);
				
				lcm.clear();

				lcm.write(0, 0, "Fahrtmodus:");
				lcm.write(5, 1, "Drehen");
				
				break;
			
			case 4:
				//C-Klasse

				lcm.clear();

				lcm.write(0, 0, "Fahrtmodus:");
				lcm.write(3, 1, "Hochfahren");

				break;
			
			case 5:
				//manuelle Steuerung

				lcm.clear();

				lcm.write(0, 0, "Fahrtmodus:");
				lcm.write(4, 1, "manuell");

				break;
		}

		//Zuweisung der Leistungen den Motoren 
		MotorA.set_power(LenkungCDrive.get_leistungRadA());
		MotorB.set_power(LenkungCDrive.get_leistungRadB());
		MotorC.set_power(LenkungCDrive.get_leistungRadC());
		MotorD.set_power(LenkungCDrive.get_leistungRadD());

		std::cout << xAchse << "  ,  " << -yAchse << std::endl;
		std::cout << LenkungCDrive.get_vektor1() << "   ,   " << LenkungCDrive.get_vektor2() << std::endl;

		delay(75);
	}

	return 0;
}