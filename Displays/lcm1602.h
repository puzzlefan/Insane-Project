#ifndef lcm1602_H
#define lcm1602_H

#include <string>

class LCM
{
private:
	int LCDAddr = 0x27;
	int BLEN = 1;
	int fd;

public:
	LCM();
	void write_word(int data);
	void send_command(int comm);
	void send_data(int data);
	void clear();
	void write(int x, int y, const std::string &data);
};

#endif // !lcm1602_H