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

void Lenkung::berechnungL�nge(int xAchse, int yAchse)
{
	berechnungWinkel(xAchse, yAchse);
	
	l�ngeLeistung = sqrt(xAchse*xAchse + yAchse*yAchse);
	Vektor1 = sin(beta)*l�ngeLeistung;
	Vektor2 = sqrt(l�ngeLeisung*l�ngeLeistung + Vektor1*Vektor1);
}

void Lenkung::normaleLenkung(int xAchse, int yAchse)
{
	berechnungL�nge(xAchse, yAchse);

	leistungRadA = Vektor1;
	leistungRadD = Vektor1;

	leistungRadB = Vektor2;
	leistungRadC = Vektor2;
}

void Lenkung::driften(int xAchse, int yAchse)
{
	berechnungL�nge(xAchse, yAchse);

	if (yAchse == 0) //seitw�rts fahren; ansonsten keine Werte da yAchse = 0
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
	leistungRadB = d�mpfung*zAchse;
	leistungRadC = d�mpfung*zAchse;

	leistungRadA = -1 * d�mpfung*zAchse;
	leistungRadD = -1 * d�mpfung*zAchse;
}

void Lenkung::bremsen(int xAchse, int yAchse)
{
	//Stellen Sie sich Code vor...
}