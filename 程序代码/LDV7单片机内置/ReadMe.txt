开发者需要修改的函数列表：

%root%/user/usart.h     void PrintComReg(void);     函数定义
%root%/user/usart.c     void PrintComReg(void);     打印识别列表
%root%/ASRBasic/MainCommon.c     void User_handle(uint8 dat);     识别某词后的处理工作
%root%/UserKeyword/CommonKeyword.h     识别关键词定义和对应的返回码对应
%root%/UserKeyword/CommonKeyword.c     识别关键词数据个数定义
%root%/UserKeyword/CommonKeywordCode.h     识别关键词的返回码