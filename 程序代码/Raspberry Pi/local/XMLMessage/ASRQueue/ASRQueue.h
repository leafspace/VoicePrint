#pragma once
#include "../../AllCommon/Common.h"

#define QUEUESIZE 100

typedef struct ASRQueue
{
    int asrQueue[QUEUESIZE];
    int head, tail;
    int asrQueueLen;
} ASRQueue;

/*
***********************************************************
*
*	函数名	: initASRQueue
*	功能	: 初始化队列
*	参数	:
				【in】queue   : 识别关键词队列
*	返回值	: 无
*
***********************************************************
*/
void initASRQueue(ASRQueue *queue);

/*
***********************************************************
*
*	函数名	: pushASRQueue
*	功能	: 将数据存入识别关键词队列
*	参数	:
				【in】queue   : 识别关键词队列
				【in】value : 将要保存到队列中的数值
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
bool pushASRQueue(ASRQueue *queue, int value);

/*
***********************************************************
*
*	函数名	: popASRQueue
*	功能	: 获取识别关键词队列中的第一个数据
*	参数	:
				【in】queue   : 识别关键词队列
				【out】retValue : 队列中第一个数值
*	返回值	: 【ret】isSuccess : 是否成功
*
***********************************************************
*/
bool popASRQueue(ASRQueue *queue, int *retValue);