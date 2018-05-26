#ifndef __USART_H
#define __USART_H

void UartIni(void);                                                         // 串口初始化
void UARTSendByte(uint8_t DAT);                                             // 串口发送一字节数据
void PrintCom(uint8_t *DAT);                                                // 打印串口字符串数据
void PrintComReg(uint8 code);                                               // 打印识别的串口字符串数据

#endif
