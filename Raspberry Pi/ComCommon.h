#pragma once
#include <unistd.h>

const int32_t name_arr[] = { B0, B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400, B9600, B38400, B57600, B115200 };
const int32_t speed_arr[] = { 0, 50, 75, 110, 134, 150, 200, 300, 600, 1200, 1800, 2400, 9600, 38400, 57600, 115200 };

bool set_speed(int, int);
int set_Parity(int, int, int, int);