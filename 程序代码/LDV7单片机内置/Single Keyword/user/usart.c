/***************************飞音云电子****************************
**  工程名称：YS-V0.7语音识别模块驱动程序
**	CPU: STC11L08XE
**	晶振：22.1184MHZ
**	波特率：9600 bit/S
**	配套产品信息：YS-V0.7语音识别开发板
**                http://yuesheng001.taobao.com
**  作者：zdings
**  联系：751956552@qq.com
**  修改日期：2013.9.13
**  说明：口令模式： 即每次识别时都需要说“小杰”这个口令 ，才能够进行下一级的识别
/***************************飞音云电子******************************/
#include "config.h"
#define FOSC 22118400L                                                      // System frequency
uint32_t baud = 9600;                                                       // UART baudrate

/************************************************************************
函 数 名： 串口初始化
功能描述： STC10L08XE 单片机串口初始化函数
返回函数： none
其他说明： none
**************************************************************************/
void UartIni(void)
{
	SCON = 0x50;            //8-bit variable UART
	TMOD = 0x20;            //Set Timer1 as 8-bit auto reload mode
	TH1 = TL1 = -(FOSC / 12 / 32 / baud); //Set auto-reload vaule
	TR1 = 1;                //Timer1 start run
	ES = 1;                 //Enable UART interrupt
	EA = 1;                 //Open master interrupt switch
}

/***********************************************************
* 名    称： 
* 功    能： 
* 入口参数： 无 
* 出口参数：无
* 说    明： 					 
**********************************************************/
void Uart_Isr() interrupt 4 using 1
{
	if (RI)
	{

	}

}

/************************************************************************
功能描述： 	串口发送一字节数据
入口参数：	DAT:带发送的数据
返 回 值： 	none
其他说明：	none
**************************************************************************/
void UARTSendByte(uint8_t DAT)
{
	ES = 0;
	TI = 0;
	SBUF = DAT;
	while (TI == 0);
	TI = 0;
	ES = 1;
}

/************************************************************************
功能描述： 串口发送字符串数据
入口参数： 	*DAT：字符串指针
返 回 值： none
其他说明： API 供外部使用，直观！
**************************************************************************/
void PrintCom(uint8_t *DAT)
{
	while (*DAT)
	{
		UARTSendByte(*DAT++);
	}
}

/************************************************************************
功能描述： 打印积蓄的识别关键词列表
入口参数： 	
返 回 值： none
其他说明： 发送给树莓派的消息
			例：<LDV7 REG>4 6 20</LDV7 REG>
			代表意义：拷贝 1 张
**************************************************************************/
void PrintComReg(void)
{
	uint8_t i = 0;                                                          // 循环变量
	uint8_t temp[COMBUFFERSIZE] = { 0 };                                    // 临时保存的字符串
	uint8_t buffer[COMBUFFERSIZE] = { 0 };                                  // 发送给树莓派的内容
	strcat(buffer, "<LDV7 REG>");
	for (i = 0; i < commondQueue.queueLength; ++i) {                        // 遍历队列中的识别过的数据
		sprintf(temp, "%d", commondQueue.commondQueue[i]);                  // 将数据格式化
		strcat(buffer, temp);
		if ((i + 1) != commondQueue.queueLength) {
			strcat(buffer, " ");
		}
	}
	commondQueue.queueLength = 0;                                           // 清空识别队列
	strcat(buffer, "</LDV7 REG>\r\n");
	PrintCom(buffer);                                                       // 发送串口消息
}
