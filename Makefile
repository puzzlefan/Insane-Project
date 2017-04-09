include Makefile.rules

DIRS = Schnittstelle Lenkung Ultrasonic... Joystick engine

all:
	for i in $(DIRS); do make -C $$i all; done
	$(CXX) $(CXXFLAGS) -ILenkung -IUltrasonic... -ISchnittstelle -IJoystick -Iengine -o main main.cpp \
	Lenkung/*.o \
	Schnittstelle/*.o \
	Joystick/*.o \
	engine/*.o \
	Ultrasonic.../*.o \
	-lwiringPi

clean:
	for i in $(DIRS); do make -C $$i clean; done