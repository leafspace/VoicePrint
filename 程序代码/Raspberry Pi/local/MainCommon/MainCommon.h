#pragma once

#define DRIVESIZE   20
#define LDV7SPEED   9600

#include "../ComCommon/ComCommon.h"

/*
***********************************************************
*
*	函数名	: printUsefulDriveList
*	功能	: 打印范围内设备可用状态
*	参数	: 
				【in】driveSize  : 设备号范围
				【in】driveID    : 设备号保存处
*	返回值	: 无
*
***********************************************************
*/
void printUsefulDriveList(int driveSize, int *driveID);

/*
***********************************************************
*
*	函数名	: chooseUsefulDrive
*	功能	: 用户选择一个可用的设备
*	参数	: 
				【in】driveSize  : 设备号范围
				【in】driveID    : 设备号保存处
*	返回值	: 【ret】comFId      : 可用设备号
*
***********************************************************
*/
int chooseUsefulDrive(int driveSize, int *driveID);

/*
***********************************************************
*
*	函数名	: setDriveParam
*	功能	: 设置设备的波特率等参数
*	参数	: 
				【in】comID  : 设备号
				【in】speed  : 设备波特率
				【in】dataBits : 设备一次发送的比特数
				【in】stopBits : 设备号保存处
				【in】parity : 设备号保存处
*	返回值	: 【ret】 isSuccess : 设置成功与否
*
***********************************************************
*/
bool setDriveParam(int comID, int speed, int dataBits, int stopBits, int parity);