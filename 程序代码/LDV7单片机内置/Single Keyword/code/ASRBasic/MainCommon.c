#include "MainCommon.h"

uint8_t G0_flag = DISABLE;                                                  // 运行标志，ENABLE:运行 DISABLE:未运行
sbit LED = P4 ^ 2;                                                          // 信号指示灯
CommondQueue commondQueue;                                                  // 将要发送的识别词列表

/*
sbit PA1 = P1 ^ 0;                                                          // 对应板上标号 P1.0
sbit PA2 = P1 ^ 1;                                                          // 对应板上标号 P1.1
sbit PA3 = P1 ^ 2;                                                          // .....
sbit PA4 = P1 ^ 3;                                                          // .....
sbit PA5 = P1 ^ 4;                                                          // .....
sbit PA6 = P1 ^ 5;                                                          // .....
sbit PA7 = P1 ^ 6;                                                          // 对应板上标号 P1.6
sbit PA8 = P1 ^ 7;                                                          // 对应板上标号 P1.7
*/

void MainMenu()
{
	uint8 i = 0;
	uint8_t msgBuffer[COMBUFFERSIZE] = { 0 };
	// 打印可操作菜单
	PrintCom("========================================\r\n");
	PrintCom("========== LDV7 Voice Printr ===========\r\n");
	sprintf(msgBuffer, "First level password : %s\r\n", sRecog[0]);
	PrintCom(msgBuffer);
	PrintCom("Secondary password   : \r\n");
	for (i = 1; i < DATE_ROW; ++i) {
		sprintf(msgBuffer, "    %d. ", (unsigned int)i);
		PrintCom(msgBuffer);
		sprintf(msgBuffer, "%s \r\n", sRecog[i]);
		PrintCom(msgBuffer);
	}
}

/***********************************************************
* 名    称： 	 LED灯测试
* 功    能： 单片机是否工作指示
* 入口参数： 无
* 出口参数：无
* 说    明：
**********************************************************/
void Led_test(void)
{
	LED = ~LED;
	Delay200ms();
	LED = ~LED;
	Delay200ms();
	LED = ~LED;
	Delay200ms();
	LED = ~LED;
	Delay200ms();
	LED = ~LED;
	Delay200ms();
	LED = ~LED;
}

/***********************************************************
* 名    称： void MCU_init()
* 功    能： 单片机初始化
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void MCU_init()
{
	P0 = 0xff;
	P1 = 0x00;
	P2 = 0xff;
	P3 = 0xff;
	P4 = 0xff;

	P1M0 = 0XFF;
	P1M1 = 0X00;

	LD_MODE = 0;		                                                    // 设置MD管脚为低，并行模式读取
	IE0 = 1;
	EX0 = 1;
	EA = 1;
}
/***********************************************************
* 名    称：	延时函数
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void Delay200us()		                                                    // @22.1184MHz
{
	unsigned char i, j;
	_nop_();
	_nop_();
	i = 5;
	j = 73;
	do
	{
		while (--j);
	} while (--i);
}

void  delay(unsigned long uldata)
{
	unsigned int j = 0;
	unsigned int g = 0;
	while (uldata--)
		Delay200us();
}

void Delay200ms()			                                                // @22.1184MHz
{
	unsigned char i, j, k;

	i = 17;
	j = 208;
	k = 27;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

/***********************************************************
* 名    称： 中断处理函数
* 功    能：
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void ExtInt0Handler(void) interrupt 0
{
	ProcessInt0();
}

/***********************************************************
* 名    称：用户执行函数
* 功    能：识别成功后，执行动作可在此进行修改
* 入口参数： 无
* 出口参数：无
* 说    明： 通过控制PAx端口的高低电平，从而控制外部继电器的通断
**********************************************************/
void User_handle(uint8 dat)
{
	uint8_t tempBuffer[COMBUFFERSIZE] = { 0 };
	PrintCom("TIP : Recognized code ：\r\n");
	sprintf(tempBuffer, "%d\r\n", dat);
	PrintCom(tempBuffer);

	G0_flag = ENABLE;

	if (dat < CODE_ZHANG) {
		commondQueue.commondQueue[commondQueue.queueLength] = dat;      // 将识别到的关键词识别码放入队列
		commondQueue.queueLength++;
		PrintComReg();
	} else
	{
		PrintCom("ERROR : Can't recognized ! \r\n");
	}
}