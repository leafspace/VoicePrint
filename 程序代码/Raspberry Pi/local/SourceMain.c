#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include "AllCommon/Common.h"
#include "ComCommon/ComCommon.h"
#include "MainCommon/MainCommon.h"
#include "WebServer/ServerCommon/ServerCommon.h"

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
		int comFId = 0;
		if (usefulDriveNum == 0) {
			printf("ERROR : Have no com drive !\n");
			break;
		}
		else if (usefulDriveNum == 1) {
			printf("TIP : Only have one drive .\n");
			for (int i = 0; i < DRIVESIZE; ++i) {
				if (driveID[i] >= 0) {
					comFId = driveID[i];
					sprintf(dirveName, "/dev/ttyUSB%d", i);
					printf("TIP : You choose [%d] dirver (%s) .\n", i + 1, dirveName);
					break;
				}
			}
		}
		else {
			// 用户选择一个可用的设备
			comFId = chooseUsefulDrive(DRIVESIZE, driveID);
		}

		// 设置波特率参数
		bool isSuccess = setDriveParam(comFId, LDV7SPEED, 8, 1, 'N');
		if (isSuccess == false) {
			printf("ERROR : Can't set dirver[%d]'s parity !\n", comFId);
			continue;
		}

		// 读取消息
		char *infoBuffer = malloc(sizeof(char)* BUFFERSIZE);
		if (infoBuffer == NULL) {
			printf("ERROR : Not enough memory !\n");
		}

		// 不停监听来自单片机的消息并处理
		int readSize = -1;
		printf("TIP : [LDV7] Info list . Waiting ... \n");
		do {
			if ((readSize = read(comFId, infoBuffer, BUFFERSIZE)) > 0) {
				infoBuffer[readSize] = 0;
				printf("[LDV7] : %s", infoBuffer);
				if (strstr(infoBuffer, "<LDV7 REG>") && strstr(infoBuffer, "</LDV7 REG>")) {
					initWebAddress();
					isSuccess = doRequest(REQUEST_GET, CONTENT_TYPE_HTML, false);
					if (isSuccess == false) {
						printf("ERROR : Send <get> request failue !\n");
						break;
					}
					isSuccess = doResponse(true);
					if (isSuccess == false) {
						printf("ERROR : Response XML failue !\n");
						break;
					}
				}
			}
			else {
				break;
			}
		} while (true);
		printf("TIP : Finish link . \n");

		free(infoBuffer);
		closeUsefulDriveList(DRIVESIZE, driveID);
	} while (true);
	return 0;
}
