#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ComCommon.h"

#define false   -1
#define true    1

#define DRIVESIZE   20
#define LDV7SPEED   9600
#define BUFFERSIZE  1024


int main()
{
    do {
        // 查找可用设备
        int usefulDriveNum = 0;
        char dirveName[15] = { 0 };
        int driverID[DRIVESIZE] = { -1 };
        for (int i = 0; i < DRIVESIZE; ++i) {
            sprintf(dirveName, "/dev/ttyS%d", i);
            int comFId = open(driveName, O_RDWR);
            driveID[i] = comFId;
        }

        // 打印设备可用状态
        printf("TIP : Com drive list :\n");
        for (int i = 0; i < DRIVESIZE; ++i) {
            sprintf(dirveName, "/dev/ttyS%d", i);
            printf("    NO.%d\t%s\t", (i + 1), driveName);
            if (driveID[i] < 0) {
                printf("NG\n");
            } else {
                printf("OK\n");
                usefulDriveNum++;
            }
        }

        // 没有可以使用的设备
        if (usefulDriveNum == 0) {
            printf("ERROR : Have no com drive !\n");
            break;
        }

        // 用户选择一个可用的设备
        int comFId = 0;
        printf("TIP : Witch one drive you want select : ");
        do {
            scanf_s("%d", &comFId);
            if (comFId <= 0 || comFId > DRIVESIZE) {
                printf("ERROR : Wrong dirve number !\n");
                printf("TIP : Please enter a new drive number :");
            } else if (driveID[comFId] < 0) {
                printf("ERROR : Driver can't use !\n");
                printf("TIP : Please enter a new drive number :");
            } else {
                sprintf(dirveName, "/dev/ttyS%d", comFId);
                printf("TIP : You choose [%d] dirver (%s) .\n", comFId, driverName);
                break;
            }
        } while (true);

        set_speed(comFId, LDV7SPEED);

        bool isSuccess = set_Parity(comFId, 8, 1, 'N');
        if (isSuccess == false) {
            printf("ERROR : Can't set dirver[%d]'s parity !\n", comFId);
            continue;
        }

        // 发送消息
        // write(comFId, "information", sizeof("information"));

        // 读取消息
        char *infoBuffer = malloc(sizeof(char) * BUFFERSIZE);
        assert(infoBudder != NULL);

        int readSize = -1;
        if ((readSize = read(comFId, infoBuffer, BUFFERSIZE)) > 0) {
            infoBudder[readSize + 1] = 0;
            printf("%s\n", infoBuffer);
        }

        free(infoBuffer);
        close(comFId);
    } while(true);
}