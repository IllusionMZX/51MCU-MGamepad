#include "USART.h"

char RxBuffer[RxBuffer_Len] = {0};
bit USART_Busy;

void String_Analysis()
{

}


/*----------------------------
Send a string to UART
Input: s (address of string)
Output:None
----------------------------*/
void SendString(char *s)
{
    while (*s)              //Check the end of the string
    {
        SendData(*s++);     //Send current char and increment string ptr
    }
}

void Uart1Init(void)		//115200bps@27.000MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR &= 0xBF;		//定时器1时钟为Fosc/12,即12T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设定定时器1为16位自动重装方式
	TL1 = 0xFB;		//设定定时初值
	TH1 = 0xFF;		//设定定时初值
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	ES = 1;	
}

/*----------------------------
UART interrupt service routine
----------------------------*/
void Usart_Isr() interrupt 4
{
	static unsigned short Str_Count = 0;
    if (RI)
    {
        RI = 0;             //Clear receive interrupt flag

		RxBuffer[Str_Count] = SBUF; 
		if(RxBuffer[Str_Count] == '\n')
		{
			for(++Str_Count; Str_Count < RxBuffer_Len; ++Str_Count)
				RxBuffer[Str_Count] = 0;
			Str_Count = 0;
			String_Analysis();
		}
		else
			++Str_Count;
		
    }
    if (TI)
    {
        TI = 0;             //Clear transmit interrupt flag
        USART_Busy = 0;		//Clear transmit USART_Busy flag
    }
}

/*----------------------------
Send a byte data to UART
Input: dat (data to be sent)
Output:None
----------------------------*/
void SendData(char dat)
{
    while (USART_Busy);		//Wait for the completion of the previous data is sent
    ACC = dat;              //Calculate the even parity bit P (PSW.0)
    if (P)                  //Set the parity bit according to P
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 0;            //Set parity bit to 0
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 1;            //Set parity bit to 1
#endif
    }
    else
    {
#if (PARITYBIT == ODD_PARITY)
        TB8 = 1;            //Set parity bit to 1
#elif (PARITYBIT == EVEN_PARITY)
        TB8 = 0;            //Set parity bit to 0
#endif
    }
    USART_Busy = 1;
    SBUF = ACC;             //Send data to UART buffer
}


//适配vofa+串口示波器的JustFloat格式 浮点为大端 
void SendFloat(unsigned char *Data) //发送一个字符
{
	char i;
	for(i=0;i<4;++i)
		SendData(Data[3-i]);
}
