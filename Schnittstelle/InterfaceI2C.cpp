#include <wiringPi.h>
#include <mcp23017.h>
#include <InterfaceI2C.h>


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