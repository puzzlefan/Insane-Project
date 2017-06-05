#pragma once
#ifndef Lenkung_H
#define Lenkung_H

#include "../Schnittstelle/InterfaceI2C.h"
#include <math.h>

class Lenkung
{
private:
	//feste Werte
	double dampfung = 0.75;//Damit beim drehen keine 100% Motorauslastung
	double lamda  = 0.5; //Faktor um faktorBremsen zu reduzieren

	//zu berechnende Werte
	double langeLeistung;//aktuelle Gesamtleistung
	double Vektor1;// l�ngeLeistung aufgeteit auf jeweise 2 R�der
	double Vektor2;

	// Ergebnisse
	double leistungRadA;//Rad links vorne
	double leistungRadB;//Rad rechts vorne
	double leistungRadC;//Rad rechts hinten
	double leistungRadD;//Rad links hinten

public:
	//Berechnungen der einzelnen L�ngen etc. nur Klassen intern ben�tigt
	void berechnungLange(int xAchse, int yAchse);

	//verschiedene Aufteilungen der Lestungen je nach Modi
	void normaleLenkung(int xAchse, int yAchse);
	void driften(int xAchse, int yAchse);
	void drehen(int xAchse);
	void parken();

	//Ausgabe der verschiedenen Leistungen
	double get_leistungRadA() { return leistungRadA; }
	double get_leistungRadB() { return leistungRadB; }
	double get_leistungRadC() { return leistungRadC; }
	double get_leistungRadD() { return leistungRadD; }
	double get_langeLeistung() { return langeLeistung; }
	double get_vektor1() { return Vektor1; }
	double get_vektor2() { return Vektor2; }
};
#endif
