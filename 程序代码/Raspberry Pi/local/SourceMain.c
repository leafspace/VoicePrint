#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "ComCommon/ComCommon.h"
#include "MainCommon/MainCommon.h"
#include "WebServer/ServerCommon.h"

#define BUFFERSIZE  1024

int main()
{
	do {
		// 查找可用设备
		int usefulDriveNum = 0;
		char dirveName[15] = { 0 };
		int driveID[DRIVESIZE] = { -1 };

		usefulDriveNum = findUsefulDriveList(DRIVESIZE, driveID);

		// 打印设备可用状态
		printUsefulDriveList(DRIVESIZE, driveID);

		// 没有可以使用的设备
		if (usefulDriveNum == 0) {
			printf("ERROR : Have no com drive !\n");
			break;
		}

		// 用户选择一个可用的设备
		int comFId = chooseUsefulDrive(DRIVESIZE, driveID);


		// 设置波特率参数
		bool isSuccess = setDriveParam(comFId, LDV7SPEED, 8, 1, 'N');
		if (isSuccess == false) {
			printf("ERROR : Can't set dirver[%d]'s parity !\n", comFId);
			continue;
		}

		// 发送消息
		// write(comFId, "information", sizeof("information"));

		// 读取消息
		char *infoBuffer = malloc(sizeof(char)* BUFFERSIZE);
		if (infoBuffer == NULL) {
			printf("ERROR : Not enough memory !\n");
		}

		int readSize = -1;
		if ((readSize = read(comFId, infoBuffer, BUFFERSIZE)) > 0) {
			infoBuffer[readSize + 1] = 0;
			printf("TIP[LDV7] : %s\n", infoBuffer);
			if (strstr(infoBuffer, "<LDV7 REG>") && strstr(infoBuffer, "</LDV7 REG>")) {
				isSuccess = getRequest();
				if (isSuccess == false) {
					printf("ERROR : Send <get> request failue !\n");
				}
			}
		}

		free(infoBuffer);
		closeUsefulDriveList(DRIVESIZE, driveID);
	} while (true);
	return 0;
}
