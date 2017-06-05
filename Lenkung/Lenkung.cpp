#include <iostream>
#include "../Schnittstelle/InterfaceI2C.h"
#include "Lenkung.h"
#include <math.h>
#include <cmath>

void Lenkung::berechnungLange(int xAchse, int yAchse)
{
	double dxAchse = (double)xAchse;//wandelt Integerwerte in Double um, damit bei der Rechnung unterschiedliche Werte raus kommen
	double dyAchse = (double)yAchse;
	dyAchse *= -1;//um Koordinatensystem des Joysticks auszugleichen

	Vektor1 = 1 / sqrt(2)*dxAchse + 1 / sqrt(2)*dyAchse;
	Vektor2 = -1 / sqrt(2)*dxAchse + 1 / sqrt(2)*dyAchse;

	if (Vektor1 > 100) { Vektor1 = 100; }
	if (Vektor2 > 100) { Vektor2 = 100; }
	if (Vektor1 < -100) { Vektor1 = -100; }
	if (Vektor2 < -100) { Vektor2 = -100; }
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
	if (yAchse == 0) //seitwrts fahren; ansonsten keine Werte da yAchse = 0
	{
		leistungRadA += lamda*(xAchse-leistungRadA);
		leistungRadC += lamda*(xAchse-leistungRadC);

		leistungRadB += lamda*(-xAchse-leistungRadB);//Geht nicht auf weil wenn x positiv  leistung negativ => -- wird immer schneller größer
		leistungRadD += lamda*(-xAchse-leistungRadD);
		
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

void Lenkung::drehen(int xAchse)//drehen jetzt mit X-Achse
{
	leistungRadB += lamda*(dampfung*xAchse-leistungRadB);
	leistungRadC += lamda*(dampfung*xAchse-leistungRadC);

	leistungRadA += lamda*(-dampfung*xAchse-leistungRadA);//Vermutlich das gleiche wie oben schon mal geändert
	leistungRadD += lamda*(-dampfung*xAchse-leistungRadD);
}

void Lenkung::parken()
{
	leistungRadA += lamda*(0 - leistungRadA);
	leistungRadB += lamda*(0 - leistungRadB);
	leistungRadC += lamda*(0 - leistungRadC);
	leistungRadD += lamda*(0 - leistungRadD);
}
