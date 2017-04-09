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

	leistungRadA += lamda*(Vektor1-leistungRadA);
	leistungRadD += lamda*(Vektor1-leistungRadD);

	leistungRadB += lamda*(Vektor2-leistungRadB);
	leistungRadC += lamda*(Vektor2-leistungRadC);
}

void Lenkung::driften(int xAchse, int yAchse)
{
	berechnungLänge(xAchse, yAchse);

	if (yAchse == 0) //seitwärts fahren; ansonsten keine Werte da yAchse = 0
	{
		leistungRadA += lamda*(xAchse-leistungRadA);
		leistungRadC += lamda*(xAchse-leistungRadC);

		leistungRadB += -1*lamda*(xAchse-leistungRadB);
		leistungRadD += -1*lamda*(xAchse-leistungRadD);
	}

	else //"normales" driften
	{
		leistungRadA += lamda*(Vektor1-leistungRadA);
		leistungRadC += lamda*(Vektor1-leistungRadC);

		leistungRadB += lamda*(Vektor2-leistungRadB);
		leistungRadD += lamda*(Vektor2-leidtungRadD);
	}
}

void Lenkung::drehen(int zAchse)
{
	leistungRadB += lamda*(dämpfung*zAchse-leistungRadB);
	leistungRadC += lamda*(dämpfung*zAchse-leistungRadC);

	leistungRadA += -1*lamda*(dämpfung*zAchse-leistungRadA);
	leistungRadD += -1*lamda*(dämpfung*zAchse-leistungRadD);
}

void parken()
{
	leistungRadA += lamda*(0 - leistungRadA);
	leistungRadB += lamda*(0 - leistungRadB);
	leistungRadC += lamda*(0 - leistungRadC);
	leistungRadD += lamda*(0 - leistungRadD);
}
