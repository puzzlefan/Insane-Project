#pragma once

class motor 
{
private:
	int zgeschwindigkeit(0); //Zielgeschwindigkeit
	int ageschwindigkeit(0); //aktuelle Geschwindigkeit
	float zuwachs(0);//soll den Wert angeben, um denen die aktuelle Geschwindigkeiit erhöht werden soll
	

public:
	void set_speed(int speed)
	{
		geschwindigkeit = speed; //Neigung des Joysticks nach vorne/hinten
		return = 0;
	}
	
	void geschwindigkeitsanpassung ()
	{
		int differenz(0);//Differenz zwischen Ziel und aktueller Geschwindigkeit

		differenz = zgeschwindigkeit - ageschwindigkeit;
		zuwachs = 0.1*differenz;
		ageschwindigkeit = ageschwindigkeit + zuwachs;
	}
};
