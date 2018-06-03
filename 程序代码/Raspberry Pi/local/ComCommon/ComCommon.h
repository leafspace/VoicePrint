#pragma once

#include <stdint.h>
#include <unistd.h>
#include <termios.h>

#define bool int

#define true 1
#define false -1

extern const int32_t name_arr[];
extern const int32_t speed_arr[];

bool set_speed(int, int);
int set_Parity(int, int, int, int);