#include <iostream>  //Grund-Funktionen
#include <math.h>
#include <wiringPi.h>
#include <mcp23017.h>
#include <softPwm.h>
#include <joystick.hh> //Klassen zur Verarbeitung von Sensordaten
#include <Rotationssensor.h>
#include <libSonar.h>
#include <InterfaceI2C.h> // Schnittstelle
#include <Lenkkung.h> //Generelle Steuerung
#include <engine.h> // Klasse um Daten an Motoren weiter zu geben


void SetUp()
{
	wiringPiSetup();

	// Erstellen einzelen Objekte aus den Klassen

	//Schnittstellen
	InterfaceI2C::pin();

	//Joystick
	joystick::Joystick();

	//Ultraschallsensoren
	libSonar::rvUlreaschallsensor1();
	libSonar::rvUltraschallsensor2();
	libSonar::rvUltraschallsensor3();
	libSonar::lvUltraschallsensor1();
	libSonar::lvUltraschallsensor2();
	libSonar::lvUltraschallsensor3();

	libSonar::rhUltraschallsensor1();
	libSonar::rhUltraschallsensor2();
	libSonar::rhUltraschallsensor3();
	libSonar::lhUltraschallsensor1();
	libSonar::lhUltraschallsensor2();
	libSonar::lhUltraschallsensor3();

	//Motoren
	engine::MotorA();
	engine::MotorB();
	engine::MotorC();
	engine::MotorD();
	engine::MotorCDirveA();
	engine::MotorCDriveB();
	engine::MotorCDriveC();
	engine::MotorCDriveD();

	//Lenkung
	Lenkung::LenkungCDrive();

	//SetUp-Funktionen der Klassen aufrufen

	//Schnittstelle
	pin.InterfaceSetUp();

	//Ultraschallsensoren
	rvUltraschallsensoren1.init(pin.get_rvUltraschallsensorenTrigger1(), pin.get_rvUltraschallsensorenEcho1());
	rvUltraschallsensoren2.init(pin.get_rvUltraschallsensorenTrigger2(), pin.get_rvUltraschallsensorenEcho2());
	rvUltraschallsensoren3.init(pin.get_rvUltraschallsensorenTrigger3(), pin.get_rvUltraschallsensorenEcho3());
	lvUltraschallsensoren1.init(pin.get_lvUltraschallsensorenTrigger1(), pin.get_lvUltraschallsensorenEcho1());
	lvUltraschallsensoren2.init(pin.get_lvUltraschallsensorenTrigger2(), pin.get_lvUltraschallsensorenEcho2());
	lvUltraschallsensoren3.init(pin.get_lvUltraschallsensorenTrigger3(), pin.get_lvUltraschallsensorenEcho3());

	rhUltraschallsensoren1.init(pin.get_rhUltraschallsensorenTrigger1(), pin.get_rhUltraschallsensorenEcho1());
	rhUltraschallsensoren2.init(pin.get_rhUltraschallsensorenTrigger2(), pin.get_rhUltraschallsensorenEcho2());
	rhUltraschallsensoren3.init(pin.get_rhUltraschallsensorenTrigger3(), pin.get_rhUltraschallsensorenEcho3());
	lhUltraschallsensoren1.init(pin.get_lhUltraschallsensorenTrigger1(), pin.get_lhUltraschallsensorenEcho1());
	lhUltraschallsensoren2.init(pin.get_lhUltraschallsensorenTrigger2(), pin.get_lhUltraschallsensorenEcho2());
	lhUltraschallsensoren3.init(pin.get_lhUltraschallsensorenTrigger3(), pin.get_lhUltraschallsensorenEcho3());

	//Motoren
	MotorA.initialisEngine(pin.get_RadAf(), pin.get_RadAb());
	MotorB.initialisEngine(pin.get_RadBf(), pin.get_RadBb());
	MotorC.initialisEngine(pin.get_RadCf(), pin.get_RadCb());
	MotorD.initialisEngine(pin.get_RadDf(), pin.get_RadDb());
	MotorCDriveA.initialisEngine(pin.get_cRadAf(), pin.get_cRadAb());
	MotorCDriveB.initialisEngine(pin.get_cRadBf(), pin.get_cRadBb());
	MotorCDriveC.initialisEngine(pin.get_cRadCf(), pin.get_cRadCb());
	MotorCDriveD.initialisEngine(pin.get_cRadDf(), pin.get_cRadDb());
}

int main()
{
	void SetUp();

	while (true)
	{

	}

	return 0;
}