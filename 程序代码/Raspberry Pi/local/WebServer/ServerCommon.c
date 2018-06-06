#include "ServerCommon.h"

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
int ResolveProtocol(char* address, char* protocol)
{
    int i = 0;
    char *position = NULL;
    if ((position = strstr(address, "://")) != NULL) {
        for (i = 0; (address + i) != position; ++i) {
            protocol[i] = *(address + i);
        }
        return 0;
    } else {
        return -1;
    }
}

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
int ResolveIP(char* address, char* ip)
{
    char *position = NULL;
    position = strstr(address, "://");
    if (position == NULL) {
        position = address;
    }

    // Todo 未完待续

}

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
int ResolvePath(char* address, char* path)
{

}

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
int ResolveParameter(char* address, char* parameter)
{

}
