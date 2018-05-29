#ifndef __COMMONKEYWORD_H
#define __COMMONKEYWORD_H

#include "CommonKeywordCode.h"

#define DATE_ROW 8   /*数组二维数值*/
#define DATE_CAL 20		/*数组一维数值*/

uint8 code sRecog[DATE_ROW][DATE_CAL] = {
  "xiao jie", \
  "kai fa ban yan zheng", \
  "dai ma ce shi", \
  "kai deng", \
  "guan deng", \
  "bei jing", \
  "shang hai", \
  "guang zhou"
};	/*添加关键词，用户修改*/

uint8 code pCode[DATE_ROW] = {
  CODE_CMD, \
  CODE_KFBYZ, \
  CODE_DMCS, \
  CODE_KD, \
  CODE_GD, \
  CODE_BJ, \
  CODE_SH, \
  CODE_GZ
};	/*添加识别码，用户修改*/

#endif