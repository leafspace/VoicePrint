#ifndef __MAINCOMMON_H
#define __MAINCOMMON_H

#include "../config.h"

typedef struct CommondQueue
{
    uint8 commondQueue[COMMONDQUEUESIZE];
    uint8 queueLength;
}CommondQueue;

extern uint8_t G0_flag;                                                     // 运行标志，ENABLE:运行。DISABLE:禁止运行
extern CommondQueue commondQueue;                                           // 将要发送的识别词列表
/*
extern sbit LED;                                                            // 信号指示灯
extern sbit PA1;                                                            // 对应板上标号 P1.0
extern sbit PA2;                                                            // 对应板上标号 P1.1
extern sbit PA3;                                                            // .....
extern sbit PA4;                                                            // .....
extern sbit PA5;                                                            // .....
extern sbit PA6;                                                            // .....
extern sbit PA7;                                                            // 对应板上标号 P1.6
extern sbit PA8;                                                            // 对应板上标号 P1.7
*/

void MainMenu();
void MCU_init();
void ProcessInt0();                                                         // 识别处理函数
void delay(unsigned long uldata);
void User_handle(uint8 dat);                                                // 用户执行操作函数
void Led_test(void);                                                        // 单片机工作指示
void Delay200ms();

#endif