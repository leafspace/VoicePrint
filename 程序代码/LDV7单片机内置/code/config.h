#ifndef __CONFIG_H
#define __CONFIG_H

/*****相关宏宏定义***/
/* exact-width signed integer types */
typedef   signed          char int8_t;
typedef   signed short     int int16_t;
typedef   signed           int int32_t;
typedef   signed       long int int64_t;

/* exact-width unsigned integer types */
typedef unsigned          char uint8_t;
typedef unsigned short     int uint16_t;
typedef unsigned           int uint32_t;
typedef unsigned       long int uint64_t;

#define ENABLE 1
#define DISABLE 0

#define COMBUFFERSIZE 50
#define COMMONDQUEUESIZE 10

/****头文件包含*****/
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include <intrins.h>
#include "ASRBasic/LDChip.h"
#include "ASRBasic/Reg_RW.h"
#include "ASRBasic/STC11XX.H"
#include "ASRBasic/MainCommon.h"

#include "UserKeyword/CommonKeyword.h"
#include "UserKeyword/CommonKeywordCode.h"

/****条件编译定义*******/

#endif
