#ifndef __MAINCOMMON_H
#define __MAINCOMMON_H

#include "../config.h"

uint8_t G0_flag = DISABLE;                                                  // 运行标志，ENABLE:运行。DISABLE:禁止运行
sbit LED = P4 ^ 2;                                                          // 信号指示灯
//应用IO口定义 （模块标注 P2）
sbit PA1 = P1 ^ 0;                                                          // 对应板上标号 P1.0
sbit PA2 = P1 ^ 1;                                                          // 对应板上标号 P1.1
sbit PA3 = P1 ^ 2;                                                          // .....
sbit PA4 = P1 ^ 3;                                                          // .....
sbit PA5 = P1 ^ 4;                                                          // .....
sbit PA6 = P1 ^ 5;                                                          // .....
sbit PA7 = P1 ^ 6;                                                          // 对应板上标号 P1.6
sbit PA8 = P1 ^ 7;                                                          // 对应板上标号 P1.7

void MainMenu();
void MCU_init();
void ProcessInt0();                                                         // 识别处理函数
void delay(unsigned long uldata);
void User_handle(uint8 dat);                                                // 用户执行操作函数
void Led_test(void);                                                        // 单片机工作指示
void Delay200ms();

#endif