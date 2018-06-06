#pragma once

#include <time.h>
#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

/*
***********************************************************
*
*	函数名	: getRequest
*	功能	: 向定义的目标主机发送get请求
*	参数	: 无
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
int getRequest(void);
/*
***********************************************************
*
*	函数名	: postRequest
*	功能	: 向定义的目标主机发送post请求
*	参数	: 无
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
int postRequest(void);

/*
***********************************************************
*
*	函数名	: ResolveProtocol
*	功能	: 用户选择一个可用的设备
*	参数	:
				【in】address   : 用户设置的ip地址
				【out】protocol : 目标使用的协议
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
int ResolveProtocol(char* address, char* protocol);
/*
***********************************************************
*
*	函数名	: ResolveIP
*	功能	: 用户选择一个可用的设备
*	参数	:
				【in】address   : 用户设置的ip地址
				【out】ip       : 目标使用的ip
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
int ResolveIP(char* address, char* ip);
/*
***********************************************************
*
*	函数名	: ResolvePath
*	功能	: 用户选择一个可用的设备
*	参数	:
				【in】address   : 用户设置的ip地址
				【out】path     : 目标所要访问的路径
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
int ResolvePath(char* address, char* path);
/*
***********************************************************
*
*	函数名	: ResolveParameter
*	功能	: 用户选择一个可用的设备
*	参数	:
				【in】address   : 用户设置的ip地址
				【out】parameter: 目标所附带的参数
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
int ResolveParameter(char* address, char* parameter);