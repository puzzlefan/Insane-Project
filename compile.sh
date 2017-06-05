
#!/bin/bash
sudo g++ -std=c++14 -Wall -pedantic -g main.cpp C/C.cpp rotaryencoder/RotationssensorArduino.cpp engine/engine.cpp Lenkung/Lenkung.cpp manualControl/manuelControl.cpp switching/switching.cpp Ultrasonic/libSonar.cpp Displays/lcm1602.cpp Joystick/joystick.cc Schnittstelle/InterfaceI2C.cpp  -o TEST  -lwiringPiDev -lwiringPi
echo finish
