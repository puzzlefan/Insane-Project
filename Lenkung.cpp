#include <engine.h>
#include <interfaceI2C.h>
#include <Lenkung.h>
#include <math.h>

void Lenkung::berechnungWinkel (int xAchse, int yAchse)
{
	alpha = asin(yAchse / sqrt(xAchse*xAchse + yAchse*yAchse);

	beta = M_PI / 4 - alpha;
	beta = fabs(beta);//Betrag nehmen
}

void Lenkung::berechnungLänge(int xAchse, int yAchse)
{
	berechnungWinkel(xAchse, yAchse);
	
	längeLeistung = sqrt(xAchse*xAchse + yAchse*yAchse);
	Vektor1 = sin(beta)*längeLeistung;
	Vektor2 = sqrt(längeLeisung*längeLeistung + Vektor1*Vektor1);
}

void Lenkung::normaleLenkung(int xAchse, int yAchse)
{
	berechnungLänge(xAchse, yAchse);

	leistungRadA = Vektor1;
	leistungRadD = Vektor1;

	leistungRadB = Vektor2;
	leistungRadC = Vektor2;
}

void Lenkung::driften(int xAchse, int yAchse)
{
	berechnungLänge(xAchse, yAchse);

	if (yAchse == 0) //seitwärts fahren; ansonsten keine Werte da yAchse = 0
	{
		leistungRadA = xAchse;
		leistungRadC = xAchse;

		leistungRadB = -1*xAchse;
		leistungRadD = -1*xAchse;
	}

	else //"normales" driften
	{
		leistungRadA = Vektor1;
		leistungRadC = Vektor1;

		leistungRadB = Vektor2;
		leistungRadD = Vektor2;
	}
}

void Lenkung::drehen(int zAchse)
{
	leistungRadB = dämpfung*zAchse;
	leistungRadC = dämpfung*zAchse;

	leistungRadA = -1 * dämpfung*zAchse;
	leistungRadD = -1 * dämpfung*zAchse;
}

void Lenkung::bremsen(int xAchse, int yAchse)
{
	//Stellen Sie sich Code vor...
}