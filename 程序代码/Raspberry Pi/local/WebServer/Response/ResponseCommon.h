#pragma once
#include "../ServerCommon/ServerCommon.h"


/*
***********************************************************
*
*	函数名	: makeMessage
*	功能	: 制作要发送给mfc的报文
*	参数	: 
				【in】contentType   : 用户要请求的类型：例如text/html
				【out】message   : 做成的报文
*	返回值	: 无
*
***********************************************************
*/
void makeMessage(char* contentType, char* message);