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

	//Einstellen der verschiedenen Pins auf In- und Output
	pinMode(rvUltraschallsensorEcho1, INPUT);
	pinMode(rvUltraschallsensorEcho2, INPUT);
	pinMode(rvUltraschallsensorEcho3, INPUT);
	pinMode(lvUltraschallsensorEcho1, INPUT);
	pinMode(lvUltraschallsensorEcho2, INPUT);
	pinMode(lvUltraschallsensorEcho3, INPUT);

	pinMode(rvUltraschallsensorTrigger1, OUTPUT);
	pinMode(rvUltraschallsensorTrigger2, OUTPUT);
	pinMode(rvUltraschallsensorTrigger3, OUTPUT);
	pinMode(lvUltraschallsensorTrigger1, OUTPUT);
	pinMode(lvUltraschallsensorTrigger2, OUTPUT);
	pinMode(lvUltraschallsensorTrigger3, OUTPUT);

	pinMode(rhUltraschallsensorEcho1, INPUT);
	pinMode(rhUltraschallsensorEcho2, INPUT);
	pinMode(rhUltraschallsensorEcho3, INPUT);
	pinMode(lhUltraschallsensorEcho1, INPUT);
	pinMode(lhUltraschallsensorEcho2, INPUT);
	pinMode(lhUltraschallsensorEcho3, INPUT);

	pinMode(rhUltraschallsensorTrigger1, OUTPUT);
	pinMode(rhUltraschallsensorTrigger2, OUTPUT);
	pinMode(rhUltraschallsensorTrigger3, OUTPUT);
	pinMode(lhUltraschallsensorTrigger1, OUTPUT);
	pinMode(lhUltraschallsensorTrigger2, OUTPUT);
	pinMode(lhUltraschallsensorTrigger3, OUTPUT);

	pinMode(Parken, INPUT);
	pinMode(fahrtModiNormalesFahren, INPUT);
	pinMode(fahrtModiDrehen, INPUT);
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