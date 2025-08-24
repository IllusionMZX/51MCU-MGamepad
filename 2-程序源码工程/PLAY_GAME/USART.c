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
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR &= 0xBF;		//��ʱ��1ʱ��ΪFosc/12,��12T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//�趨��ʱ��1Ϊ16λ�Զ���װ��ʽ
	TL1 = 0xFB;		//�趨��ʱ��ֵ
	TH1 = 0xFF;		//�趨��ʱ��ֵ
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
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


//����vofa+����ʾ������JustFloat��ʽ ����Ϊ��� 
void SendFloat(unsigned char *Data) //����һ���ַ�
{
	char i;
	for(i=0;i<4;++i)
		SendData(Data[3-i]);
}
