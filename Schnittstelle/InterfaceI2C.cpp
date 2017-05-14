#include "..\Rotationssensor\InterfaceI2C.h"
#include "..\Rotationssensor\InterfaceI2C.h"
#include "..\Rotationssensor\InterfaceI2C.h"
#include "..\Rotationssensor\InterfaceI2C.h"
#include <wiringPi.h>
#include <mcp23017.h>
#include "InterfaceI2C.h"
#include <wiringPiI2C.h>


void Schnittstelle::InterfaceSetUp()
{
	// Erstellen der verschiedenen Extentionboards
	mcp23017Setup(100, 0x20);
	mcp23017Setup(200, 0x21);
	mcp23017Setup(300, 0x22);
	mcp23017Setup(400, 0x24);

	pinMode(Parken, INPUT);
	pinMode(fahrtModiNormalesFahren, INPUT);
	pinMode(fahrtModiDrehen, INPUT);
	pinMode(manuelleSteuerung, INPUT);
	pinMode(anAus, INPUT);

	pinMode(pinNotaus, INPUT);

	if ((ConnectionToken = wiringPiI2CSetup(AdresseRotationsArduino))<0) //Seems to open the needet i2c Channel for wiring pi
	{
		printf("error opening i2c channel\n\r");
	}
}

void Schnittstelle::WerteSchreiben(int pin, int Wert)
{
	digitalWrite(pin, Wert);
}

int Schnittstelle::WerteLesen(int pin)
{
	int Ergebnis = 0;

	Ergebnis = digitalRead(pin);

	return Ergebnis;
}

void Schnittstelle::I2C8Write(int token, int Register, int Wert)
{
	wiringPiI2CWriteReg8(token, Register, Wert);
}

void Schnittstelle::I2C16Write(int token, int Register, int Wert)
{
	wiringPiI2CWriteReg16(token, Register, Wert);
}

int Schnittstelle::I2C8Read(int token, int Register)
{
	return wiringPiI2CReadReg8(token, Register);
}

int Schnittstelle::I2C16Read(int token, int Register)
{
	return wiringPiI2CReadReg16(token, Register);
}
