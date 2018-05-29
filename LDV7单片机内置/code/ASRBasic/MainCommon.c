#include "../config.h"

void MainMenu()
{
  uint8_t msgBuffer[COMBUFFERSIZE] = { 0 };
  PrintCom("========================================\r\n");
  PrintCom("========== LDV7 Voice Printr ===========\r\n");
  sprintf(msgBuffer, "First level password : %s\r\n", sRecog[0]);
  PrintCom(msgBuffer);
  PrintCom("Secondary password   : \r\n");
  for (uint8 i = 1; i < DATE_ROW; ++i) {
    sprintf(msgBuffer, "	%d. %s \r\n", i, sRecog[i]);
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

	P1M0 = 0XFF;	                                                        // P1端口设置为推挽输�?�功�?�?��即提高IO口驱动能力，从驱动继电器模块工�?
	P1M1 = 0X00;

	LD_MODE = 0;		                                                    // 设置MD管脚为低，并行模式读�?
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
	ProcessInt0();				                                            /* LD3320 送�?�中断信号?��包括ASR和播放MP3�?中断?��需要在中断�?�?函数中�?别�?�? */
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
	// UARTSendByte(dat);                                                   // 串口�?别�??��十六进制?�?
	if (0 == dat)
	{
		G0_flag = ENABLE;
		LED = 0;
	}
	else if (ENABLE == G0_flag)
	{
		G0_flag = DISABLE;
		LED = 1;
		PrintComReg(dat);
	else
	{
		PrintCom("ERROR : Can't recognized ! \r\n");
	}
}
