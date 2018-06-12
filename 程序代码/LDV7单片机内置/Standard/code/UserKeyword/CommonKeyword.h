#ifndef __COMMONKEYWORD_H
#define __COMMONKEYWORD_H

#include "../config.h"
#include "CommonKeywordCode.h"

#define DATE_ROW 22      /*关键词个数*/
#define DATE_CAL 20		 /*关键词最大长度*/

// 关键词和对应关键词的识别返回码
extern uint8 code sRecog[DATE_ROW][DATE_CAL];
extern uint8 code pCode[DATE_ROW];

#endif