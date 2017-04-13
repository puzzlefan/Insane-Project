#include <iostream>
#include <InterfaceI2C.h>
#include <Lenkung.h>
#include <math.h>


void Lenkung::berechnungLange(int xAchse, int yAchse)
{	
	double dxAchse = (double)xAchse;//wandelt Integerwerte in Double um, damit bei der Rechnung unterschiedliche Werte raus kommen
	double dyAchse = (double)yAchse;

	Vektor1 = 1 / sqrt(2)*dxAchse + 1 / sqrt(2)*dyAchse;
	Vektor2 = -1 / sqrt(2)*dxAchse + 1 / sqrt(2)*dyAchse;
}

void Lenkung::normaleLenkung(int xAchse, int yAchse)
{
	berechnungLange(xAchse, yAchse);

	leistungRadA += lamda*(Vektor1-leistungRadA);
	leistungRadD += lamda*(Vektor1-leistungRadD);

	leistungRadB += lamda*(Vektor2-leistungRadB);
	leistungRadC += lamda*(Vektor2-leistungRadC);
}

void Lenkung::driften(int xAchse, int yAchse)
{
	if (yAchse == 0) //seitwärts fahren; ansonsten keine Werte da yAchse = 0
	{
		leistungRadA += lamda*(xAchse-leistungRadA);
		leistungRadC += lamda*(xAchse-leistungRadC);

		leistungRadB += -1*lamda*(xAchse-leistungRadB);
		leistungRadD += -1*lamda*(xAchse-leistungRadD);
	}

	else //"normales" driften
	{	
		berechnungLange(xAchse, yAchse);

		leistungRadA += lamda*(Vektor1-leistungRadA);
		leistungRadC += lamda*(Vektor1-leistungRadC);

		leistungRadB += lamda*(Vektor2-leistungRadB);
		leistungRadD += lamda*(Vektor2-leistungRadD);
	}
}

void Lenkung::drehen(int zAchse)
{
	leistungRadB += lamda*(dampfung*zAchse-leistungRadB);
	leistungRadC += lamda*(dampfung*zAchse-leistungRadC);

	leistungRadA += -1*lamda*(dampfung*zAchse-leistungRadA);
	leistungRadD += -1*lamda*(dampfung*zAchse-leistungRadD);
}

void Lenkung::parken()
{
	leistungRadA += lamda*(0 - leistungRadA);
	leistungRadB += lamda*(0 - leistungRadB);
	leistungRadC += lamda*(0 - leistungRadC);
	leistungRadD += lamda*(0 - leistungRadD);
}
