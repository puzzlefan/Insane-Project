include Makefile.rules

DIRS = Schnittstelle Lenkung Ultrasonic Joystick engine Displays switchig manualControl C rotaryencoder

all:
	for i in $(DIRS); do make -C $$i all; done
	$(CXX) $(CXXFLAGS) -ILenkung -IUltrasonic -ISchnittstelle -IJoystick -IDisplays -Iengine -ImanualControl -Iswitchig -IC -Irotaryencoder -o main main.cpp \
	Lenkung/*.o \
	Schnittstelle/*.o \
	Joystick/*.o \
	engine/*.o \
	Ultrasonic/*.o \
	Displays/*.o \
	manualControl/*.o \
	switchig/*.o \
	C/*.o \
	rotaryencoder/*.o \
	-lwiringPi

clean:
	for i in $(DIRS); do make -C $$i clean; done
