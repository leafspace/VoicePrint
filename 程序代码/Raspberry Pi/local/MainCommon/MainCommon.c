#include "MainCommon.h"

/*
***********************************************************
*
*	函数名	: printUsefulDriveList
*	功能	: 打印范围内设备可用状态
*	参数	:
				【in】driveSize    : 设备号范围
				【in】driveID    : 设备号保存处
*	返回值	: 无
*
***********************************************************
*/
void printUsefulDriveList(int driveSize, int *driveID)
{
	printf("TIP : Com drive list :\n");
	int i = 0;
	char dirveName[15] = { 0 };
	for (i = 0; i < DRIVESIZE; ++i) {
		sprintf(dirveName, "/dev/ttyUSB%d", i);
		printf("    NO.%d\t%d\t%s\t", (i + 1), driveID[i], dirveName);
		if (driveID[i] < 0) {
			printf("NG\n");
		}
		else {
			printf("OK\n");
		}
	}
}

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
int chooseUsefulDrive(int driveSize, int *driveID)
{
	printf("TIP : Witch one drive you want select : ");
	do {
		int comFId = 0;
		char dirveName[15] = { 0 };
		scanf("%d", &comFId);
		if (comFId <= 0 || comFId > DRIVESIZE) {
			printf("ERROR : Wrong dirve number !\n");
			printf("TIP : Please enter a new drive number :");
		}
		else if (driveID[comFId - 1] < 0) {
			printf("ERROR : Driver can't use !\n");
			printf("TIP : Please enter a new drive number :");
		}
		else {
			sprintf(dirveName, "/dev/ttyUSB%d", comFId - 1);
			printf("TIP : You choose [%d] dirver (%s) .\n", comFId - 1, dirveName);
			return comFId - 1;
		}
	} while (true);
}

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
bool setDriveParam(int comID, int speed, int dataBits, int stopBits, int parity)
{
	bool isSuccess = false;
	printf("TIP : ComID = %d, Speed = %d . \n", comID, speed);
	isSuccess = set_speed(comID, speed);
	if (isSuccess == false) {
		printf("ERROR : Set speed failue ! \n");
		return false;
	}
	
	printf("TIP : ComID = %d, DataBits = %d, StopBits = %d, Parity = %c . \n", comID, dataBits, stopBits, parity);
	isSuccess = set_parity(comID, dataBits, stopBits, parity);
	if (isSuccess == false) {
		printf("ERROR : Set parity failue ! \n");
		return false;
	}
	return isSuccess;
}