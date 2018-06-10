#pragma once
#define SIGNALVALUE 5

#include "../ServerCommon/ServerCommon.h"

/*
***********************************************************
*
*	函数名	: resolveMessage
*	功能	: 解析对象请求的报文
*	参数	: 
				【in】message   : 做成的报文
				【out】contentType   : 用户要请求的类型：例如text/html
				【out】requestPath   : 用户要请求的文件路径
*	返回值	: 无
*
***********************************************************
*/
void resolveMessage(char* message, char* contentType, char* requetPath);

/*
***********************************************************
*
*	函数名	: makeMessageHead
*	功能	: 制作要发送给mfc的报文
*	参数	: 
				【in】contentType   : 用户要请求的类型：例如text/html
				【out】message   : 做成的报文
*	返回值	: 无
*
***********************************************************
*/
void makeMessageHead(char* contentType, char* message);