#include "bluetooth.h"



void Uart2Init(void)		//9600bps@27.000MHz
{
	S2CON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x04;		//定时器2时钟为Fosc,即1T
	T2L = 0x41;		//设定定时初值
	T2H = 0xFD;		//设定定时初值
	AUXR |= 0x10;		//启动定时器2
	IE2 |= 0x01;
	EA = 1;

}