#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <string.h>
#include <lcm1602.h>

LCM::LCM()
{
	fd = wiringPiI2CSetup(LCDAddr);

	send_command(0x33); // Must initialize to 8-line mode at first
	delay(5);
	send_command(0x32); // Then initialize to 4-line mode
	delay(5);
	send_command(0x28); // 2 Lines & 5*7 dots
	delay(5);
	send_command(0x0C); // Enable display without cursor
	delay(5);
	send_command(0x01); // Clear Screen
	wiringPiI2CWrite(fd, 0x08);
}

void LCM::write_word(int data) 
{
	int temp = data;
	if (BLEN == 1)
		temp |= 0x08;
	else
		temp &= 0xF7;
	wiringPiI2CWrite(fd, temp);
}

void LCM::send_command(int comm) 
{
	int buf;
	// Send bit7-4 firstly
	buf = comm & 0xF0;
	buf |= 0x04; // RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB; // Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (comm & 0x0F) << 4;
	buf |= 0x04; // RS = 0, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB; // Make EN = 0
	write_word(buf);
}

void LCM::send_data(int data) 
{
	int buf;
	// Send bit7-4 firstly
	buf = data & 0xF0;
	buf |= 0x05; // RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB; // Make EN = 0
	write_word(buf);

	// Send bit3-0 secondly
	buf = (data & 0x0F) << 4;
	buf |= 0x05; // RS = 1, RW = 0, EN = 1
	write_word(buf);
	delay(2);
	buf &= 0xFB; // Make EN = 0
	write_word(buf);
}

void LCM::clear() 
{
	send_command(0x01); //clear Screen
}

void LCM::write(int x, int y, const std::string &data) 
{
	int addr;

	if (x < 0) x = 0;
	if (x > 15) x = 15;
	if (y < 0) y = 0;
	if (y > 1) y = 1;

	// Move cursor
	addr = 0x80 + 0x40 * y + x;
	send_command(addr);

	const int len = data.length();
	for (int i = 0; i < len; i++) {
		send_data(data.c_str()[i]);
	}
}