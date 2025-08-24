#include "STC15F2K60S2.H"
#include "OLED.h"
#include "OLED_Data.h"
#include "all.h"

extern bit moveflag;
extern bit foodflag;
extern bit giveup;
extern bit start;
extern bit fun;	
//giveup��ʳ�ﱻ������־λ��foodflag��ʳ��ˢ�±�־λ��moveflag���ƶ���־λ��
extern unsigned char  count;
extern unsigned char page;
extern unsigned char mode;
extern unsigned char snake_time;
extern unsigned char point;
//page������ʾ��ͬ��ҳ�棬������Ϸ����ҳ�棬��ʼҳ��ȣ�mode����ʶ���ߵ��˶�״̬��

struct snake  //�ṹ�壬���ڴ��������λ�ã�
{
 unsigned char x;
 unsigned char y;
} ;


void SnakeGame(void);
void snake_modepros(void);
void OLED_SnakeBody(unsigned char x, unsigned char y);//��ӡ����
void OLED_SnakeBody_food(unsigned char x, unsigned char y);//��ӡʳ��
void OLED_CLR_Body(unsigned char x, unsigned char y);//�������
void keypros(void);//��������
void modepros(void);

void Snake_Init(void)	;	 //�߳�ʼ��������
void Food_Init(void);		//ʳ���ʼ��������
void Snake_Over(void); 	//������������������֮����ʾgame over,ͬʱ���ϼ�⸴ԭ���Ƿ񱻰���;


void Game_Restart(void);
void choice(void);
void delay_snake(unsigned char i);
void page0(void);

