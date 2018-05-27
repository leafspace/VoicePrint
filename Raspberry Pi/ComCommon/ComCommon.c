#include "ComCommon.h"

bool set_speed(int comID, int speed)
{
	struct termios optTermios;
	tcgetattr(comID, &optTermios);
	for (int i = 0, status = 0; i < min(sizeof(speed_arr), sizeof(name_arr)) / sizeof(int); ++i) {
		if (speed == speed_arr[i]) {
			tcflush(comID, TCIOFLUSH);
			cfsetispeed(&optTermios, name_arr[i]);
			cfsetospeed(&optTermios, name_arr[i]);
			status = tcsetattr(comID, TCSANOW, &optTermios);
			if (status != 0) {
				return false;
			}
		}
		tcflush(comID, TCIOFLUSH);
	}
	return true;
}

int set_Parity(int comID, int dataBits, int stopBits, int parity)
{
	struct termios optTermios;
	if (tcgetattr(comID, &optTermios) != 0) {
		return false;
	}
	optTermios.c_cflag &= ~CSIZE;

	switch (dataBits)
	{
	case 7:
		optTermios.c_cflag |= CS7;
		break;
	case 8:
		optTermios.c_cflag |= CS8;
		break;
	default:
		return false;
	}

	switch (parity)
	{
	case 'n': case 'N':
		optTermios.c_cflag &= ~PARENB;
		optTermios.c_iflag &= ~INPCK;
		break;
	case 'o': case 'O':
		optTermios.c_cflag |= (PARODD | PARENB);
		optTermios.c_iflag |= INPCK;
		break;
	case 'e': case 'E':
		optTermios.c_cflag |= PARENB;
		optTermios.c_cflag &= ~PARODD;
		optTermios.c_iflag |= INPCK;
		break;
	case 'S': case 's':
		optTermios.c_cflag &= ~PARENB;
		optTermios.c_cflag &= ~CSTOPB; break;
	default:
		return false;
	}

	switch (stopBits)
	{
	case 1:
		optTermios.c_cflag &= ~CSTOPB;
		break;
	case 2:
		optTermios.c_cflag |= CSTOPB;
		break;
	default:
		return false;
	}

	if (parity != 'n') {
		optTermios.c_iflag |= INPCK;
	}
	tcflush(comID, TCIFLUSH);
	optTermios.c_cc[VTIME] = 150;
	optTermios.c_cc[VMIN] = 0;
	if (tcsetattr(comID, TCSANOW, &optTermios) != 0) {
		return false;
	}
	return true;
}