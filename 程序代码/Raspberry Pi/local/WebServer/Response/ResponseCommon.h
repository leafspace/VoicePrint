#pragma once
#define SIGNALVALUE 1
#define STACKSIZE 20

#include "../ServerCommon/ServerCommon.h"

typedef struct ParameterStack
{
	char *parameterKey[STACKSIZE];
	char *parameterValue[STACKSIZE];
	int parameterLen;
} ParameterStack;


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
*	函数名	: resolveParameter
*	功能	: 解析对象请求的报文
*	参数	: 
				【in】message   : 做成的报文
				【out】parameterStack   : 用户报文的参数队列
*	返回值	: 无
*
***********************************************************
*/
void resolveParameter(char* message, ParameterStack *parameterStack);

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

/*
***********************************************************
*
*	函数名	: setWebAddressParameter
*	功能	: 设置全局的向MFC发送请求的网址
*	参数	: 
				【in】parameterStack   : 用户报文的参数队列
*	返回值	: 【ret】 : 返回是否成功
*
***********************************************************
*/
bool setWebAddressParameter(ParameterStack *parameterStack);

/*
***********************************************************
*
*	函数名	: freeWebAddressParameter
*	功能	: 清除参数内存
*	参数	: 
				【in】parameterStack   : 用户报文的参数队列
*	返回值	: 无
*
***********************************************************
*/
void freeWebAddressParameter(ParameterStack *parameterStack);