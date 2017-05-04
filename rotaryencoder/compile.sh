#!/bin/bash
sudo g++ -std=c++14 -Wall -pedantic main.cpp Rotationssensor.cpp Rotationssensor.h -o RUN  -lwiringPiDev -lwiringPi
echo finish
echo go!
sudo ./RUN
