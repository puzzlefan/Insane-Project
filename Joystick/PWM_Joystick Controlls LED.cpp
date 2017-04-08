//this is a comment
#include "joystick.hh"
#include <unistd.h>
#include <wiringPi.h>
#include <stdio.h>
#include <iostream>
#include <softPwm.h>

int main(int argc, char** argv)
{
	// Create an instance of Joystick
	Joystick joystick("/dev/input/js1");

	// Ensure that it was found and that we can use it
	if (!joystick.isFound())
	{
		printf("open failed.\n");
		exit(1);
	}

	int pin = 25;//Definition des Pins um in allen Commandos gleichzeitig die pins zu ändern !Achtung schmeißt bei umgültigem Wert keine Fehlermeldung
//	int pause = 100;//Länge der Pause (Vermutlich in ms)
	std::cout << pin << std::endl; //gibt zum überprüfen an welcher Pin gerade ausgewählt ist

	if (wiringPiSetup() == -1)  // Starte die WiringPi-Api (wichtig)
	{
		return 1;
	}

	softPwmCreate (pin, 100, 100) ;

	while (true)
	{
		// Restrict rate
		usleep(1000);

		// Attempt to sample an event from the joystick
		JoystickEvent event;
		if (joystick.sample(&event))
		{
			if (event.isButton())
			{
//				printf("Button %u is %s\n",
//					event.number,
					if(event.value == 0)
					{
						softPwmWrite(pin,100);
					}
					if(event.value != 0)
					{
						 softPwmWrite(pin, 0);
					}
			}
			else if (event.isAxis())
			{
				//printf("Axis %u is at position %d\n", event.number, event.value);
					int valueEvent = int(event.value);
					int value = valueEvent/327;
					std::cout << value << std::endl;
					std::cout << valueEvent << std::endl;
				if(value <= 0)
				{
					value = value * (-1);
				}
				if (event.number == 1)
				{
					softPwmWrite(pin, value);
					std::cout << value << std::endl;

				}
			}
		}
	}
}




/*
// WiringPi-Api einbinden


// C-Standardbibliothek einbinden


//Output-Bibliothek einbinden


int main() {
	int pin = 25;//Definition des Pins um in allen Commandos gleichzeitig die pins zu ändern !Achtung schmeißt bei umgültigem Wert keine Fehlermeldung
	int pause = 100;//Länge der Pause (Vermutlich in ms)
	std::cout << pin << std::endl; //gibt zum überprüfen an welcher Pin gerade ausgewählt ist


	// Schalte GPIO Pin auf Ausgang
	// Wichtig: Hier wird das WiringPi Layout verwendet (Tabelle oben) [stimmt nicht aber auch egal]


	// Dauerschleife
	while (1) {
		// LED an
		digitalWrite(pin, 1);//Definierten Pin einschalten
		std::cout << "ON " << std::endl;//On ausgeben
		std::cout << digitalRead(pin) << std::endl;//Status des Pins überprüfen
												   // Warte pause
		delay(pause);

		// LED aus
		digitalWrite(pin, 0);//Definierten Pin ausschalten
		std::cout << "OFF " << std::endl;//Off Ausgeben
		std::cout << digitalRead(pin) << std::endl;//status des Pins überprüfen
												   // Warte pause
		delay(pause);
	}
}

*/
