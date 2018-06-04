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
**  说明：口令模式+IO控制： 即每次识别时都需要说"小杰"这个口令 ，才能够进行下一级的识别
/***************************飞音云电子******************************/

/************************************************************************************/
//	nAsrStatus 用来在main主程序中表示程序运行的状态，不是LD3320芯片内部的状态寄存器
//	LD_ASR_NONE:		表示没有在作ASR识别
//	LD_ASR_RUNING：		表示LD3320正在作ASR识别中
//	LD_ASR_FOUNDOK:		表示一次识别流程结束后，有一个识别结果
//	LD_ASR_FOUNDZERO:	表示一次识别流程结束后，没有识别结果
//	LD_ASR_ERROR:		表示一次识别流程中LD3320芯片内部出现不正确的状态
/***********************************************************************************/
#include "config.h"
uint8 idata nAsrStatus = 0;

/***********************************************************
* 名    称： void  main(void)
* 功    能： 主函数	程序入口
* 入口参数：
* 出口参数：
* 说    明：
* 调用方法：
**********************************************************/
void  main(void)
{
	uint8 idata nAsrRes;
	uint8 i = 0;
	Led_test();
	MCU_init();
	LD_Reset();
	UartIni();                                                               /* 串口初始化 */
	nAsrStatus = LD_ASR_NONE;                                                // 初始状态：没有在作ASR

	// 初始化全局识别命令词队列
	commondQueue.queueLength = 0;

	MainMenu();

	while (1)
	{
		switch (nAsrStatus)
		{
		case LD_ASR_RUNING:
		case LD_ASR_ERROR:
			break;
		case LD_ASR_NONE:
		{
			nAsrStatus = LD_ASR_RUNING;
			if (RunASR() == 0)                                              /* 启动一次ASR识别流程：ASR初始化，ASR添加关键词语，启动ASR运算 */
			{
				nAsrStatus = LD_ASR_ERROR;
			}
			break;
		}
		case LD_ASR_FOUNDOK:                                                /* 一次ASR识别流程结束，去取ASR识别结果 */
		{
			nAsrRes = LD_GetResult();                                       /* 获取结果 */
			User_handle(nAsrRes);                                           // 用户执行函数
			nAsrStatus = LD_ASR_NONE;
			break;
		}
		case LD_ASR_FOUNDZERO:
		default:
		{
			nAsrStatus = LD_ASR_NONE;
			break;
		}
		}
	}
}
