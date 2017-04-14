include Makefile.rules

DIRS = Schnittstelle Lenkung Ultrasonic... Joystick engine Displays switchig manualControl

all:
	for i in $(DIRS); do make -C $$i all; done
	$(CXX) $(CXXFLAGS) -ILenkung -IUltrasonic... -ISchnittstelle -IJoystick -IDisplays -Iengine -o main main.cpp \
	Lenkung/*.o \
	Schnittstelle/*.o \
	Joystick/*.o \
	engine/*.o \
	Ultrasonic.../*.o \
	Displays/*.o \
	manualControl/*.o \
	switchig/*.o \
	-lwiringPi

clean:
	for i in $(DIRS); do make -C $$i clean; done
