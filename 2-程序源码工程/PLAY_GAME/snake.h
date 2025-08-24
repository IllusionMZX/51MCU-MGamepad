#include "STC15F2K60S2.H"
#include "OLED.h"
#include "OLED_Data.h"
#include "all.h"

extern bit moveflag;
extern bit foodflag;
extern bit giveup;
extern bit start;
extern bit fun;	
//giveup是食物被舍弃标志位，foodflag是食物刷新标志位，moveflag是移动标志位；
extern unsigned char  count;
extern unsigned char page;
extern unsigned char mode;
extern unsigned char snake_time;
extern unsigned char point;
//page用于显示不同的页面，比如游戏结束页面，开始页面等；mode用于识别蛇的运动状态；

struct snake  //结构体，用于储存蛇身的位置；
{
 unsigned char x;
 unsigned char y;
} ;


void SnakeGame(void);
void snake_modepros(void);
void OLED_SnakeBody(unsigned char x, unsigned char y);//打印身体
void OLED_SnakeBody_food(unsigned char x, unsigned char y);//打印食物
void OLED_CLR_Body(unsigned char x, unsigned char y);//清除身体
void keypros(void);//按键集合
void modepros(void);

void Snake_Init(void)	;	 //蛇初始化函数；
void Food_Init(void);		//食物初始化函数；
void Snake_Over(void); 	//蛇死亡函数，在死亡之后显示game over,同时不断检测复原键是否被按下;


void Game_Restart(void);
void choice(void);
void delay_snake(unsigned char i);
void page0(void);

