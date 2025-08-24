#ifndef __OLED_H
#define __OLED_H

#include <STC15F2K60S2.h>
#include "OLED_Data.h"
#include "stdio.h"
#include "stdlib.h"

/*参数宏定义*********************/

/*FontSize参数取值*/
/*此参数值不仅用于判断，而且用于计算横向字符偏移，默认值为字体像素宽度*/
#define OLED_8X16				8
#define OLED_6X8				6

/*IsFilled参数数值*/
#define OLED_UNFILLED			0
#define OLED_FILLED				1

/*********************参数宏定义*/


/*函数声明*********************/

/*初始化函数*/
void OLED_Init(void);
void OLED_W_SCL(uint8_t BitValue);
void OLED_W_SDA(uint8_t BitValue);
void OLED_GPIO_Init(void);
void OLED_I2C_Start(void);
void OLED_I2C_Stop(void);
void OLED_I2C_SendByte(uint8_t Byte);
void OLED_WriteCommand(uint8_t Command);
void OLED_WriteData(uint8_t *Data, uint8_t Count);

/*更新函数*/
void OLED_Update(void);
void OLED_UpdateArea(int X, int Y, uint8_t Width, uint8_t Height);

/*显存控制函数*/
void OLED_SetCursor(uint8_t Page, uint8_t X);
void OLED_Clear(void);
void OLED_ClearArea(int X, int Y, uint8_t Width, uint8_t Height);
void OLED_Reverse(void);
void OLED_ReverseArea(int X, int Y, uint8_t Width, uint8_t Height);
void oled_set_pos(unsigned char x, unsigned char y);
/*显示函数*/
void OLED_ShowChar(int X, int Y, char Char, uint8_t FontSize);
void OLED_ShowString(int X, int Y, char *String, uint8_t FontSize);
void OLED_ShowNum(int X, int Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowSignedNum(int X, int Y, int32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowHexNum(int X, int Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowBinNum(int X, int Y, uint32_t Number, uint8_t Length, uint8_t FontSize);
void OLED_ShowFloatNum(int X, int Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize);
void OLED_ShowChinese(int X, int Y, char *Chinese);
void OLED_ShowImage(int X, int Y, uint8_t Width, uint8_t Height, const uint8_t *Image);
// void OLED_Printf(int X, int Y, uint8_t FontSize, char *format, ...);

/*绘图函数*/
void OLED_DrawPoint(int X, int Y);
uint8_t OLED_GetPoint(int X, int Y);
void OLED_DrawLine(int X0, int Y0, int X1, int Y1);
void OLED_DrawRectangle(int X, int Y, uint8_t Width, uint8_t Height, uint8_t IsFilled);
void OLED_DrawTriangle(int X0, int Y0, int X1, int Y1, int X2, int Y2, uint8_t IsFilled);
void OLED_DrawCircle(int X, int Y, uint8_t Radius, uint8_t IsFilled);
void OLED_DrawEllipse(int X, int Y, uint8_t A, uint8_t B, uint8_t IsFilled);
void OLED_DrawArc(int X, int Y, uint8_t Radius, int StartAngle, int EndAngle, uint8_t IsFilled);

//小恐龙部分
void delay_ms(unsigned int time);
void OLED_DrawRestart();
int OLED_DrawDinoJump(char reset);
int OLED_DrawCactusRandom(unsigned char ver, unsigned char reset);
void OLED_DrawCactus();
void OLED_DrawDino();
void OLED_DrawCloud();
void OLED_DrawGround();


	

/*********************函数声明*/

#endif
